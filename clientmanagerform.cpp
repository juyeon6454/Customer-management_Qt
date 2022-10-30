#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"
#include "clientitem.h"

#include <QFile>
#include <QMenu>
#include <QMessageBox>

ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{
    ui->setupUi(this);      // ui 파일이 만들어짐 (this) 현재 class에 ui 파일 올림

    QList<int> sizes;
    sizes << 300 << 400;
    ui->splitter->setSizes(sizes);        /*splitter 사이즈 조절*/

    QAction* removeAction = new QAction(tr("&Remove"));                  //삭제 액션 생성
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));      //액션 신호를 보낼 때 아이템 삭제

    menu = new QMenu;                                               //메뉴 생성
    menu->addAction(removeAction);                                  //메뉴에 remove 액션 추가
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);    //(우클릭 메뉴)
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

}

void ClientManagerForm::loadData()                              //저장된 파일 로드
{
    QFile file("clientlist.txt");                               //지정된 이름 파일을 열 때 오류 검사
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))      //오류 발생시 return;
        return;

    QTextStream in(&file);                                      //오류 발생하지 않으면 clientlist.txt 불러옴
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");                  // , 을 기준으로 나눠서 row 0~7에 item 저장
        if(row.size()) {
            int clientId = row[0].toInt();
            ClientItem* c = new ClientItem(clientId, row[1], row[2], row[3],row[4]);
            ui->treeWidget->addTopLevelItem(c);
            clientList.insert(clientId, c);                     //저장한 순서로 treewidget에 나타내줌

            emit clientAdded(clientId,row[1]);                  //server에 clientname을 보냄
        }
    }
    file.close( );                                              //파일 열었으니 닫음
}

ClientManagerForm::~ClientManagerForm()
{
    delete ui;

    QFile file("clientlist.txt");                                   //데이터 파일을 만들어서 내보냄
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : clientList) {                              //이 형식으로 저장됨
        ClientItem* c = v;
        out << c->ClientId() << ", " << c->getClientName() << ", ";
        out << c->getPhoneNumber() << ", ";
        out << c->getAddress() << ", ";
        out << c->getEmail() << "\n";
    }
    file.close( );
}


int ClientManagerForm::makeId( )                  //아이디 자동부여
{
    if(clientList.size( ) == 0) {                 //list에 아무것도 없으면
        return 100;                               //100부터 반환
    } else {
        auto ClientId = clientList.lastKey();     //list에 목록이 있으면 마지막 키를 기준으로
        return ++ClientId;                        //그 뒷번호부터 반환
    }
}

void ClientManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();                          //클라이언트 정보 아이템 삭제
    int rmindex = ui->treeWidget->indexOfTopLevelItem(item);                        //고객조회treewidget에서 현재 지정된 아이템
    if(item != nullptr) {                                                           //아이템이 없으면
        clientList.remove(item->text(0).toInt());                                   //0번째 (id)를 int 값으로 변환해서
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
        ui->treeWidget->update();

        emit clientRemoved (item->text(0).toInt(), QString::number(rmindex));       //treewidget에서 빼줌
    }

    c_clearLineEdit();    //lineEdit에 남은 기록을 지움

}

void ClientManagerForm::showContextMenu(const QPoint &pos)      //마우스 우클릭 위치 알림
{
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ClientManagerForm::on_searchPushButton_clicked()           //고객 조회 버튼 클릭했을 때
{
    ui->searchTreeWidget->clear();                              //lineEdit에 남아있을 정보를 지움

    int i = ui->searchComboBox->currentIndex();                 //콤보박스 아이템을 인덱스로 받음
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), flag, i);
        //고객조회입력칸에 있는 텍스트를 뽑아 treewidget에서 아이템을 찾음

        foreach(auto i, items) {                              //해당 인덱스에 있는 item으로 foreach 돌아서
            ClientItem* c = static_cast<ClientItem*>(i);
            int clientId = c->ClientId();
            QString clientName = c->getClientName();
            QString phoneNumber = c->getPhoneNumber();
            QString address = c->getAddress();
            QString email = c->getEmail();
            ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);
            ui->searchTreeWidget->addTopLevelItem(item);      //해당 정보들을 뽑아서 treewidget에 보여줌
        }
    }
}


void ClientManagerForm::on_modifyPushButton_clicked()                //수정 버튼 눌렀을 때
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();           //treewidget에서 현재 아이템
    if(item != nullptr) {                                            //선택한 아이템이 있을 때
        int index = ui->treeWidget->indexOfTopLevelItem(item);
        int key = item->text(0).toInt();                             //item의 0번쨰 텍스트를 int형 key값으로 뽑아옴
        ClientItem* c = clientList[key];
        QString clientName, phoneNumber, address, email;
        clientName = ui->clientNameLineEdit->text();
        phoneNumber = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        email = ui->emailLineEdit->text();                          /*key 값을 통해 아이템의 정보들을 해당칸에 나타냄*/
        c->setClientName(clientName);
        c->setPhoneNumber(phoneNumber);
        c->setAddress(address);
        c->setEmail(email);
        clientList[key] = c;                                        /*해당 정보들을 clientList에 담음*/

        emit clientModified (key, index, clientName);               //고객 정보 수정시 sever client리스트도 같이 수정

    }

}


void ClientManagerForm::on_addPushButton_clicked()                                       //고객정보 입력 버튼을 누를 때
{
    QString clientName, phoneNumber, address,email;
    int clientId = makeId( );                                                            //id 자동입력값 반환
    clientName = ui->clientNameLineEdit->text();
    phoneNumber = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();
    email = ui->emailLineEdit->text();                                                   /*lineEdit에 입력된 텍스트*/
    if(clientName.length()&&phoneNumber.length()&&address.length()&&email.length()) {    //비어있는 값이 있으면
        ClientItem* c = new ClientItem(clientId, clientName, phoneNumber, address, email);
        clientList.insert(clientId, c);
        ui->treeWidget->addTopLevelItem(c);

        emit clientAdded(clientId,clientName);
    }
    else
    {
        QMessageBox::critical(this, tr("Client Info"),                                   //메세지 박스로 다시 입력하게 함
                              tr("There is information that has not been entered."));
    }
    c_clearLineEdit();      //사용한 lineEdit 기록을 지움

}


void ClientManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->clientIdLineEdit->setText(item->text(0));
    ui->clientNameLineEdit->setText(item->text(1));
    ui->phoneNumberLineEdit->setText(item->text(2));
    ui->addressLineEdit->setText(item->text(3));
    ui->emailLineEdit->setText(item->text(4));
    ui->toolBox->setCurrentIndex(0);                 /*treeWidget 아이템 클릭시 각 해당칸에 정보 나타남*/

}

void ClientManagerForm::c_findIdClient(int c_id)
{
    auto items = ui->treeWidget->findItems(QString::number(c_id), Qt::MatchContains|Qt::MatchCaseSensitive,0);

    foreach(auto i, items) {
        ClientItem* c = static_cast<ClientItem*>(i);
        int clientId = c->ClientId();
        QString clientName = c->getClientName();
        QString phoneNumber = c->getPhoneNumber();
        QString address = c->getAddress();
        QString email = c->getEmail();
        ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);

        emit c_sendIdClient(c_id, item);    //order에서 정보를 찾아달라는 signal을 보내면 client 정보를 찾아서 찾았다는 signal을 보내준다 (id값)
    }
}

void ClientManagerForm::c_findNameClient(QString c_name)
{
    auto items = ui->treeWidget->findItems(c_name, Qt::MatchContains|Qt::MatchCaseSensitive, 1);

    foreach(auto i, items) {
        ClientItem* c = static_cast<ClientItem*>(i);
        int clientId = c->ClientId();
        QString clientName = c->getClientName();
        QString phoneNumber = c->getPhoneNumber();
        QString address = c->getAddress();
        QString email = c->getEmail();
        ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);

        emit c_sendNameClient(c_name, item);  //order에서 정보를 찾아달라는 signal을 보내면 client 정보를 찾아서 찾았다는 signal을 보내준다 (name 값)
    }

}

void ClientManagerForm::c_findNumberClient(QString c_number)
{
    auto items = ui->treeWidget->findItems(c_number, Qt::MatchContains|Qt::MatchCaseSensitive, 2);

    foreach(auto i, items) {
        ClientItem* c = static_cast<ClientItem*>(i);
        int clientId = c->ClientId();
        QString clientName = c->getClientName();
        QString phoneNumber = c->getPhoneNumber();
        QString address = c->getAddress();
        QString email = c->getEmail();
        ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);

        emit c_sendNumberClient(c_number, item); //order에서 정보를 찾아달라는 signal을 보내면 client 정보를 찾아서 찾았다는 signal을 보내준다 (phonenumber 값)
    }

}

void ClientManagerForm::c_findAddressClient(QString c_address)
{
    auto items = ui->treeWidget->findItems(c_address, Qt::MatchContains|Qt::MatchCaseSensitive, 3);

    foreach(auto i, items) {
        ClientItem* c = static_cast<ClientItem*>(i);
        int clientId = c->ClientId();
        QString clientName = c->getClientName();
        QString phoneNumber = c->getPhoneNumber();
        QString address = c->getAddress();
        QString email = c->getEmail();
        ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);

        emit c_sendAddressClient(c_address, item); //order에서 정보를 찾아달라는 signal을 보내면 client 정보를 찾아서 찾았다는 signal을 보내준다 (address 값)
    }

}

void ClientManagerForm::c_findEmailClient(QString c_email)
{
    auto items = ui->treeWidget->findItems(c_email, Qt::MatchContains|Qt::MatchCaseSensitive, 4);

    foreach(auto i, items) {
        ClientItem* c = static_cast<ClientItem*>(i);
        int clientId = c->ClientId();
        QString clientName = c->getClientName();
        QString phoneNumber = c->getPhoneNumber();
        QString address = c->getAddress();
        QString email = c->getEmail();
        ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);

        emit c_sendEmailClient(c_email, item); //order에서 정보를 찾아달라는 signal을 보내면 client 정보를 찾아서 찾았다는 signal을 보내준다 (email 값)
    }

}


void ClientManagerForm::on_clearPushButton_clicked()
{
    c_clearLineEdit();              //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록
}


void ClientManagerForm::c_clearLineEdit()
{
    ui->clientIdLineEdit->clear();
    ui->clientNameLineEdit->clear();
    ui->phoneNumberLineEdit->clear();
    ui->addressLineEdit->clear();
    ui->emailLineEdit->clear();     //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록 하는 함수 구현
}
