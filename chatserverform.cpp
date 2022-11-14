#include "chatserverform.h"
#include "ui_chatserverform.h"
#include "logthread.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QTcpServer>
#include <QTcpSocket>
#include <QApplication>
#include <QMessageBox>
#include <QScrollBar>
#include <QDateTime>
#include <QDebug>
#include <QMenu>
#include <QFile>
#include <QFileInfo>
#include <QProgressDialog>

ChatServerForm::ChatServerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatServerForm), totalSize(0), byteReceived(0)               // 초기화
{
    ui->setupUi(this);                                                      // ui 파일이 만들어짐 (this) 현재 class에 ui 파일 올림
    QList<int> sizes;
    sizes << 120 << 500;
    ui->splitter->setSizes(sizes);                                          // splitter size 조절

    chatServer = new QTcpServer(this);                                      // chatServer 서버 만들어줌
    connect(chatServer, SIGNAL(newConnection( )), SLOT(clientConnect( )));  // 클라이언트 연결
    if (!chatServer->listen(QHostAddress::Any, PORT_NUMBER)) {              // 포트 번호 8000으로 바인딩 된 소켓은 인터페이스 모두에서 수신 기다림
        QMessageBox::critical(this, tr("Chatting Server"),                  // 포트 번호가 8000이 아닐 때
                              tr("Unable to start the server: %1.") \
                              .arg(chatServer->errorString( )));
        return;
    }

    fileServer = new QTcpServer(this);                                          //fileServer 서버 만들어줌
    connect(fileServer, SIGNAL(newConnection()), SLOT(acceptConnection()));     //file 연결
    if (!fileServer->listen(QHostAddress::Any, PORT_NUMBER+1)) {                //포트 번호 8000으로 바인딩 된 소켓은 인터페이스 모두에서 수신 기다림
        QMessageBox::critical(this, tr("Chatting Server"),                      // 포트 번호가 8000이 아닐 때
                              tr("Unable to start the server: %1.") \
                              .arg(fileServer->errorString( )));                //오류가 발생하면 serverError()가 오류 유형을 반환하고, errorString()을 호출하여 발생한 일에 대한 설명을 제공
        return;
    }

    qDebug("Start listening ...");

    QAction* inviteAction = new QAction(tr("&Invite"));                 // 액션을 생성
    inviteAction->setObjectName("Invite");                              // 액션 이름을 Invite로 설정
    connect(inviteAction, SIGNAL(triggered()), SLOT(inviteClient()));   // inviteAction이 triggered 되었을 때 초대

    QAction* removeAction = new QAction(tr("&Kick out"));               //액션 생성
    connect(removeAction, SIGNAL(triggered()), SLOT(kickOut()));        //removeAction이 triggered 되었을 때 강퇴

    menu = new QMenu;                                                   //메뉴 생성
    menu->addAction(inviteAction);                                      //메뉴에 inviteAction 추가
    menu->addAction(removeAction);                                      //메뉴에 removeAction 추가
    ui->clientTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);  //clientTreeWdiget에 우클릭시 메뉴 보임

    progressDialog = new QProgressDialog(0);    //프로그레서 다이얼로그 생성
    progressDialog->setAutoClose(true);         //reset시 자동으로 닫힘
    progressDialog->reset();                    //reset

    logThread = new LogThread(this);            //스레드 기반으로 로그 생성
    logThread->start();                         //스레드가 생성되면서 run() 시작

    connect(ui->savePushButton, SIGNAL(clicked()), logThread, SLOT(saveData()));    //save 버튼 눌렀을 때 로그 저장

    qDebug() << tr("The server is running on port %1.").arg(chatServer->serverPort( ));

    ui->clientTreeWidget->hideColumn(2);    //treewidget 두번째 칼럼을 숨김
}

ChatServerForm::~ChatServerForm()//소멸자
{
    delete ui;                   //ui delete

    logThread->terminate();      //실행중인 스레드를 강제로 종료
    chatServer->close( );        //채팅 서버 닫아줌
    fileServer->close( );        //파일 서버 닫아줌
}

void ChatServerForm::clientConnect( )
{
    QTcpSocket *clientConnection = chatServer->nextPendingConnection( );      //보류 중인 연결을 연결된 QTcpSocket으로 승인하려면 nextPendingConnection()을 호출
    connect(clientConnection, SIGNAL(readyRead( )), SLOT(receiveData( )));    //데이터가 오면 데이터를 받음
    connect(clientConnection, SIGNAL(disconnected( )), SLOT(removeClient())); //연결이 끊겼을 때 퇴장한 상태가 되도록
    qDebug("new connection is established...");
}

void ChatServerForm::receiveData( )                                             //데이터를 받음
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));       //sender가 연결해주는 socket 자체
    QByteArray bytearray = clientConnection->read(BLOCK_SIZE);                  //clientConnection에서 1024byte 만큼의 데이터를 읽어옴

    Chat_Status type;            // 채팅의 목적 (프로토콜)
    char data[1020];             // 전송되는 메시지/데이터
    memset(data, 0, 1020);       // 데이터양에 상관없이 쓰레기값을 0으로 초기화해줌 (크기 초기화 x)

    QDataStream in(&bytearray, QIODevice::ReadOnly);
    in.device()->seek(0);                               //처음부터 읽는다 (0번으로 이동)
    in >> type;                                         //type은 enum으로 4byte
    in.readRawData(data, 1020);                         //1020만큼 메세지 읽음

    QString ip = clientConnection->peerAddress().toString();    //연결 되면 현재 주소를 ip에 대입
    quint16 port = clientConnection->peerPort();                //연결 되면 현재 port를 port에 대입
    QString name = QString::fromStdString(data);                //연결 되면 현재 data를 name에 대입
    qDebug() << ip << " : " << type;


    switch(type) {
    case Chat_Login:                                                                            //type이 Login인 경우
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {    //foreach를 돌아서  client에 등록된 name을 소켓에 연결
            if(item->text(2) != "-") {                                                          //treewidget 두 번째 칼럼에 있는 부호가 -(대기방)이 아닐 때
                item->setText(2, "-");                                                          //로그인 되지 않은 상태'x"에서 로그인상태인 '-'로 바꿔줌
                item->setIcon(0, QIcon(":/images/login.png"));                                  //상태에 따라 treewidget 두 번째 칼럼에 아이콘 등록
                clientList.append(clientConnection);                                            // QList<QTcpSocket*> clientList; 리스트에 반환
                clientSocketHash[name] = clientConnection;                                      //hash 키를 통해 name을 검색
                                                                                                //clientSocket을 연결해놓아 이름으로 소켓을 찾을 수 있음
            }
        }

        if(ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1).count() == 0){    //clientList에 찾는 이름이 없을 때(고객에 등록된 이름 외 로그인을 막기 위함)

            QByteArray sendArray;                                                           //sendArray 바이트
            QDataStream out(&sendArray, QIODevice::WriteOnly);
            out << Chat_LogInCheck;                                                         //구조체 enum type (4byte)
            out.writeRawData("", 1020);                                                     //4byte를 제외한 1020byte를 없는 문자로 반환
            clientConnection->write(sendArray);                                             //서버로 전송
            clientConnection->flush();
            while(clientConnection->waitForBytesWritten());                                 //연결 바로 x 접속될떄까지 기다림
        }

        break;
    case Chat_In:                                                                               //채팅방 입장
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {    //treewidget에서 해당 이름을 찾음
            if(item->text(2) != "O") {                                                          //채팅방 입장한 상태가 아니라면
                item->setText(2, "O");                                                          //채팅방 입장 'o'로 바꿔줌
                item->setIcon(0, QIcon(":/images/chatting.png"));                               //해당 아이콘 지정
            }
            clientNameHash[port] = name;                                                        //채팅방에 들어간 이름을 hash로 관리
        }
        break;
    case Chat_Talk: {                                                                       /*나를 제외한 모든 사람에게 메세지를 보냄(peerport)*/
        foreach(QTcpSocket *sock, clientList) {                                             //메세지를 보내면 소켓을 가져옴
            if(clientNameHash.contains(sock->peerPort()) && sock != clientConnection) {     //나를 제외시킴 (peerport)
                QByteArray sendArray;                                                       //바이트 단위의 배열을 지원하기 위한 클래스
                sendArray.clear();                                                          //바이트 배열의 내용을 지우고 null로 만듭니다.
                QDataStream out(&sendArray, QIODevice::WriteOnly);                          //Binary 기반 write/read를 위한 stream 기능 제공
                out << Chat_Talk;
                sendArray.append("<font color=lightsteelblue>");                            //같은 port에 접속해있는 다른 사람의 이름을 나타내는 색 지정
                sendArray.append(clientNameHash[port].toStdString().data());                //이름
                sendArray.append("</font> : ");                                             //이름 : message
                sendArray.append(name.toStdString().data());                                //message
                sock->write(sendArray);                                                     //문자열을 write 함수를 통해 client로 전달
            }
        }
/*
        QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);         //서버에 찍히는 로그 treewidget으로 아이템 관리
        item->setText(0, ip);                                                       //ip
        item->setText(1, QString::number(port));                                    //port
        item->setText(2, QString::number(clientIDHash[clientNameHash[port]]));      //고객 ID
        item->setText(3, clientNameHash[port]);                                     //고객이름
        item->setText(4, QString(data));                                            //보낸 메세지 내용
        item->setText(5, QDateTime::currentDateTime().toString());                  //보낸 시간
        item->setToolTip(4, QString(data));                                         //메세지가 길어질 경우 tooltip으로 메세지 내용 보여줌

        ui->messageTreeWidget->addTopLevelItem(item);                               //로그를 위부터 순서대로 보여줌

        logThread->appendData(item);      */                                          //log 스레드로 item을 append (뒤에 문자열 추가)
    }
        break;
    case Chat_Out:                                                                              /*채팅에서 나가는 프로토콜*/
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {    //server clientList에 있는 이름이면
            if(item->text(2) != "-") {                                                          //로그인만 된 상태 '-'가 아니면 (채팅방에 입장되어있는 상태면)
                item->setText(2, "-");                                                          //상태를 '-'으로 바꿔줌
                item->setIcon(0, QIcon(":/images/login.png"));                                  //아이콘 지정
            }
            clientNameHash.remove(port);                                                        //채팅방에 들어간 name을 지움
        }
        break;
    case Chat_LogOut:                                                                           /*대기방에서 나가는 프로토콜*/
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {    //server clientList에 있는 이름이면
            if(item->text(2) != "X") {                                                          //로그아웃된 상태 'x'가 아니라면 (대기방에 있거나 채팅방에 있는 상태면)
                item->setText(2, "X");                                                          //상태를 'x'로 바꿔줌
                item->setIcon(0, QIcon(":/images/logout.png"));                                 //아이콘 지정
                clientList.removeOne(clientConnection);                                         // QList<QTcpSocket*> clientList; clietConenction된 list를 지움
                clientSocketHash.remove(name);                                                  //채팅방에 들어갈 때 추가된 name 제거
            }
        }
        break;
    }
}


void ChatServerForm::removeClient()                                                         //server가 종료되면 불림
{
    QTcpSocket *clientConnection = dynamic_cast<QTcpSocket *>(sender( ));
    if(clientConnection != nullptr) {                                                       //연결되었을 때
        QString name = clientNameHash[clientConnection->peerPort()];                        //현재 연결된 포트번호를 hash에서 검색
        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchContains, 1)) {   //treewidget에서 해당 이름이 잇는지 찾음
            item->setText(2, "X");                                                          //로그아웃 상태라면
            item->setIcon(0, QIcon(":/images/logout.png"));                                 //해당 아이콘을 보여줌
        }
        clientSocketHash.remove(name);                                                      //hash에서 해당 이름을 지움
        clientConnection->deleteLater();                                                    //server에서 올 데이터가 남아있기 때문에 deleteLater 사용
    }
}

void ChatServerForm::addClient(int id, QString name)                        //등록된 고객 정보를 가져와 clientTreeWidget에 추가
{
    clientIDList << id;
    QTreeWidgetItem* item = new QTreeWidgetItem(ui->clientTreeWidget);
    item->setText(2, "X");                                                  //처음에는 로그인도, 채팅방 입장도 되어있지 않기 때문에 'x'로 표현
    item->setIcon(0, QIcon(":/images/logout.png"));
    item->setText(1, name);                                                 //트리위젯 첫 번째 칼럼에는 이름
    ui->clientTreeWidget->addTopLevelItem(item);
    clientIDHash[name] = id;                                                //이름으로 id를 받아옴
    ui->clientTreeWidget->resizeColumnToContents(0);
}

void ChatServerForm::on_clientTreeWidget_customContextMenuRequested(const QPoint &pos)
{

    foreach(QAction *action, menu->actions()) {                                         //초대 액션이 실행되면
        if(action->objectName() == "Invite")
            action->setEnabled(ui->clientTreeWidget->currentItem()->text(2) != "O");    //채팅방 입장 상태가 아닐 때 초대 액션 메뉴를 사용 가능하게
        else
            action->setEnabled(ui->clientTreeWidget->currentItem()->text(2) == "O");    //아닐 때 강퇴 액션 메뉴 활성화
    }
    QPoint globalPos = ui->clientTreeWidget->mapToGlobal(pos);                          //마우스 위치 설정
    menu->exec(globalPos);
}

void ChatServerForm::kickOut()                                              /* 클라이언트 강퇴하기 */
{
    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << Chat_KickOut;                                                            //구조체 enum type (4byte)
    out.writeRawData("", 1020);                                                     //4byte를 제외한 1020byte를 없는 문자로 반환

    QString name = ui->clientTreeWidget->currentItem()->text(1);                    //widget에서 지정된 위젯의 이름
    QTcpSocket* sock = clientSocketHash[name];                                      //소켓에 이름을 hash로 관리
    sock->write(sendArray);                                                         //데이터를 보내면
    ui->clientTreeWidget->currentItem()->setText(2, "-");                           //채팅방에 입장하지 않은 상태가 됨
    ui->clientTreeWidget->currentItem()->setIcon(0, QIcon(":/images/login.png"));
}

void ChatServerForm::inviteClient()                                 /*서버로 클라이언트 초대*/
{

    QByteArray sendArray;
    QDataStream out(&sendArray, QIODevice::WriteOnly);
    out << Chat_Invite;                                             //구조체 enum type (4byte)
    out.writeRawData("", 1020);                                     //4byte를 제외한 1020byte를 없는 문자로 반환

    if(ui->clientTreeWidget->topLevelItemCount()) {

       QString name = ui->clientTreeWidget->currentItem()->text(1);   //소켓은 현재 선택된 아이템에 표시된 이름과 해쉬로 부터 가져온다. */
       QTcpSocket* sock = clientSocketHash[name];                     //채팅방에 들어가있는 name hash에 추가
        if(sock == nullptr)                                           //소켓이 없으면 return 프로그램이 죽는 것을 방지
             {
                 return ;
             }

        sock->write(sendArray);

        foreach(auto item, ui->clientTreeWidget->findItems(name, Qt::MatchFixedString, 1)) {    //treewidget에 해당 이름을 찾음
            if(item->text(2) != "O") {                                                          //chat in 상태가 아니면 초대
                item->setText(2, "O");                                                          //'o' 상태로 표현
                item->setIcon(0, QIcon(":/images/chatting.png"));                               //chat in 상태 아이콘 지정
                quint16 port = sock->peerPort();
                 clientNameHash[port] = name;                                                   //채팅방에 들어온 namehash에 추가
            }
        }
    }
}

void ChatServerForm::acceptConnection()                                     /* 파일 전송을 위한 소켓 생성 */
{
    qDebug("Connected, preparing to receive files!");

    QTcpSocket* receivedSocket = fileServer->nextPendingConnection();
    connect(receivedSocket, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void ChatServerForm::readClient()
{
    qDebug("Receiving file ...");
    QTcpSocket* receivedSocket = dynamic_cast<QTcpSocket *>(sender( ));
    QString filename;
    QString name;

    if (byteReceived == 0) {            // 파일 전송 시작 : 파일에 대한 정보를 이용해서 QFile 객체 생성
        progressDialog->reset();        // 파일 전송을 나타내는 프로그레스 다이얼로그 리셋
        progressDialog->show();         // 다이얼로그 보여줌

        QString ip = receivedSocket->peerAddress().toString();  //현재 주소 ip
        quint16 port = receivedSocket->peerPort();              //(quit : 2byte) 현재 port

        QDataStream in(receivedSocket);
          in >> totalSize >> byteReceived >> filename >> name;
          progressDialog->setMaximum(totalSize);                  //send를 받아서 메세지를 보낼 때 totalsize를 사용해서 progressDialog bar 설정

          QTreeWidgetItem* item = new QTreeWidgetItem(ui->messageTreeWidget);       /* 파일을 받았을 때 로그 추가가 되어야 하니까 로그 추가*/
          item->setText(0, ip);                                                     // ip
          item->setText(1, QString::number(port));                                  // port
          item->setText(2, QString::number(clientIDHash[name]));                    // 고객 ID
          item->setText(3, name);                                                   // 고객이름
          item->setText(4, filename);                                               // 보낸메세지 내용
          item->setText(5, QDateTime::currentDateTime().toString());                // 보낸 시간
          item->setToolTip(4, filename);                                            // 메세지가 길어질 경우 tooltip으로 메세지 내용 보여줌

        ui->messageTreeWidget->addTopLevelItem(item);                               // treewidget에 item에 담긴 로그를 나타냄

        logThread->appendData(item);                                                // 로그에 아이템 data를 보내줌

        QFileInfo info(filename);                       // 파일을 열 수 있는지 확인
        QString currentFileName = info.fileName();      // 전체 경로에서 이름만 뽑아옴
        file = new QFile(currentFileName);              // 파일을 가져와서
        file->open(QFile::WriteOnly);                   // 읽을 수 있으면 파일을 연다
    } else {                                            // 파일 데이터를 읽어서 저장
        inBlock = receivedSocket->readAll();            // 데이터를 읽고 난 후

        byteReceived += inBlock.size();                 // inblock 사이즈를 추가한다
        file->write(inBlock);                           // inblock을 파일에 쓰고
        file->flush();                                  // 파일을 비움현재 버퍼에 저장되어 있는 내용을 클라이언트로 전송하고 버퍼를 비운다.
    }

    progressDialog->setValue(byteReceived);             //프로그레스다이얼을 byteReceived 만큼설정


    if (byteReceived == totalSize) {
        qDebug() << QString("%1 receive completed").arg(filename);

        inBlock.clear();
        byteReceived = 0;
        totalSize = 0;
        progressDialog->reset();
        progressDialog->hide();
        file->close();
        delete file;                                                 /* 파일의 다 읽으면 QFile 객체를 닫고 삭제 */
    }
}

void ChatServerForm::removeServerClient(int c_id, QString rmindex)  //client에서 정보를 삭제하면 serverWidget에서도 삭제
{
    Q_UNUSED(c_id);
    ui->clientTreeWidget->takeTopLevelItem(rmindex.toInt());
}


void ChatServerForm::on_clearPushButton_clicked()       //clear버튼을 누르면 treewidget에 로그를 지워줌
{
    ui->messageTreeWidget->clear();
}

void ChatServerForm::modifyServerClient(int key, int row, QString clientname)     //client 정보를 수정하면 serverwidget에서도 수정
{
    ui->clientTreeWidget->topLevelItem(row)->setText(1,clientname);
    clientIDHash[clientname] = key;

}

