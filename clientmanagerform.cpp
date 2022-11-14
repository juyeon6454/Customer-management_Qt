#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"

#include <QFile>
#include <QMenu>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTreeView>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QStandardItemModel>

ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{
    ui->setupUi(this);                                                    // ui 파일이 만들어짐 (this) 현재 class에 ui 파일 올림

    QList<int> sizes;
    sizes << 300 << 400;
    ui->splitter->setSizes(sizes);                                        /*splitter 사이즈 조절*/

    QAction* removeAction = new QAction(tr("&Remove"));                   //삭제 액션 생성
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));       //액션 신호를 보낼 때 아이템 삭제

    menu = new QMenu;                                                    //메뉴 생성
    menu->addAction(removeAction);                                       //메뉴에 remove 액션 추가
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);           //(우클릭 메뉴)

    connect(ui->treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint))); //우클릭시 알림
    connect(ui->searchLineEdit, SIGNAL(returnPressed()), this, SLOT(on_searchPushButton_clicked()));        //search enter 누를 시 pushbutton 클릭

    s_clientModel = new QStandardItemModel(0,5);                            //search view를 위한 model 생성
    s_clientModel->setHeaderData(0, Qt::Horizontal, tr("ID"));              //id, name, phonenumber, address, email 칼럼 생성
    s_clientModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    s_clientModel->setHeaderData(2, Qt::Horizontal, tr("PhoneNumber"));
    s_clientModel->setHeaderData(3, Qt::Horizontal, tr("Address"));
    s_clientModel->setHeaderData(4, Qt::Horizontal, tr("Email"));
    ui->searchTreeView->setModel(s_clientModel);                            //treeview에 model set


}

void ClientManagerForm::loadData()                              //저장된 파일 로드
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "clientConnection");     //SQLITE를 이용한 database 생성
    db.setDatabaseName("clientlist.db");                                            //database 이름 clientList.db
    if (db.open( )) {                                                               //예외처리
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS client(id INTEGER Primary Key, name VARCHAR(30) NOT NULL, phoneNumber VARCHAR(20) NOT NULL, address VARCHAR(50), email VARCHAR(50));");
        clientModel = new QSqlTableModel(this, db);
        clientModel->setTable("client");                                    //query문을 이용해 table 생성
        clientModel->select();
        clientModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        clientModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        clientModel->setHeaderData(2, Qt::Horizontal, tr("PhoneNumber"));
        clientModel->setHeaderData(3, Qt::Horizontal, tr("Address"));
        clientModel->setHeaderData(4, Qt::Horizontal, tr("Email"));
        ui->treeView->setModel(clientModel);
    }
    for(int i = 0; i < clientModel->rowCount(); i++) {                                  //model의 row를 count해서 해당 index에서 원하는 정보를 뽑아냄
        int clientId = clientModel->data(clientModel->index(i, 0)).toInt();
        QString clientName = clientModel->data(clientModel->index(i, 1)).toString();

       emit clientAdded(clientId, clientName);                                          //id와 이름을 찾아서 server clientList로 signal 보냄
    }

}

ClientManagerForm::~ClientManagerForm()
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("clientConnection");        //db를 닫아줌
    if(db.isOpen()) {
        clientModel->submitAll();
        delete clientModel;
        db.commit();
        db.close();
    }
}

int ClientManagerForm::makeId( )                     //아이디 자동부여
{
    if(clientModel->rowCount() == 0) {               //model에 아무것도 없으면
        return 100;                                  //100부터 반환
    } else {
        auto clientId = clientModel->data(clientModel->index(clientModel->rowCount()-1, 0)).toInt();
        return ++clientId;                           //client모델의 rowcount로 마지막 id 뒷번호부터 부여
    }
}

void ClientManagerForm::removeItem()                            //clinet remove
{
    QModelIndex index = ui->treeView->currentIndex();
    int delid = index.sibling(index.row(), 0).data().toInt();   //treewidget에서 현재  item을 인덱스와 row로 뽑아냄
    int row = index.row();                                      //sever clientlist에 보내기 위한 signal 인자
    if(index.isValid()) {
        clientModel->removeRow(index.row());                    //model에서 열을 지움
        clientModel->select();
    }
    else
    {
        QMessageBox::critical(this, tr("Client Info"),                                   //메세지 박스로 client가 선택되지 않음을 알림
                              tr("There is information that has not been entered."));
    }
    emit clientRemoved (delid, QString::number(row));            //sever clientlist로 signal 보냄
    c_clearLineEdit();                                           //lineEdit에 남은 기록을 지움
}

void ClientManagerForm::showContextMenu(const QPoint &pos)       //마우스 우클릭 위치 알림
{
    QPoint globalPos = ui->treeView->mapToGlobal(pos);
    if(ui->treeView->indexAt(pos).isValid())
    menu->exec(globalPos);
}


void ClientManagerForm::on_addPushButton_clicked()                                      //고객정보 입력 버튼을 누를 때
{
    QString clientName, phoneNumber, address, email;
    int clientId = makeId( );
    ui->clientIdLineEdit->setText(QString::number(clientId));
    clientName = ui->clientNameLineEdit->text();
    phoneNumber = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();
    email = ui->emailLineEdit->text();                                                  //lineEdit에 존재하는 text들이

    QSqlDatabase db = QSqlDatabase::database("clientConnection");
    if(db.isOpen() && clientName.length() && phoneNumber.length() && address.length()) {//lineEdit이 비어있을 경우를 위한 예외처리
        QSqlQuery query(clientModel->database());
        query.prepare("INSERT INTO client VALUES (?, ?, ?, ?, ?)");
        query.bindValue(0, clientId);
        query.bindValue(1, clientName);
        query.bindValue(2, phoneNumber);
        query.bindValue(3, address);
        query.bindValue(4, email);                                                       //client table에 입력됨
        query.exec();
        clientModel->select();
        emit clientAdded(clientId, clientName);                                          //server로 clientlist 보내기 위한 signal
    }
    else
    {
        QMessageBox::critical(this, tr("Client Info"),                                   //메세지 박스로 다시 입력하게 함
                              tr("There is information that has not been entered."));
    }

    c_clearLineEdit();                                                                   //사용한 lineEdit 기록을 지움

}

void ClientManagerForm::on_modifyPushButton_clicked()                //수정 버튼 눌렀을 때
{
    QModelIndex index = ui->treeView->currentIndex();
    int molid = index.sibling(index.row(), 0).data().toInt();       //수정되었을 때 server의 clientList가 같이 수정되도록
    int row = index.row();

    QString clientName, phoneNumber, address, email;
    clientName = ui->clientNameLineEdit->text();
    phoneNumber = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();
    email = ui->emailLineEdit->text();                             //lineEdit에 있는text들을

    if(index.isValid() && clientName.length() && phoneNumber.length() && address.length() &&email.length()) {
        clientModel->setData(index.siblingAtColumn(1), clientName);
        clientModel->setData(index.siblingAtColumn(2), phoneNumber);
        clientModel->setData(index.siblingAtColumn(3), address);
        clientModel->setData(index.siblingAtColumn(4), email);       //clientModel에 데이터가 입력되도록
        clientModel->submit();
        clientModel->select();
        emit clientModified (molid, row, clientName);               //고객 정보 수정시 sever client리스트도 같이 수정
    }
    else
    {
        QMessageBox::critical(this, tr("Client Info"),                                   //메세지 박스로 다시 입력하게 함
                              tr("There is information that has not been entered."));
    }


}

void ClientManagerForm::on_searchPushButton_clicked()           //고객 조회 버튼 클릭했을 때
{
    s_clientModel->clear();                                     //lineEdit에 남아있을 정보를 지움
    int i = ui->searchComboBox->currentIndex();                 //콤보박스 아이템을 인덱스로 받음
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;                    //데이터를 찾을 때 해당 단어가 있으면 찾아주도록 하는 속성

        QModelIndexList indexes = clientModel->match(clientModel->index(0, i), Qt::EditRole, ui->searchLineEdit->text(), -1, flag);
        foreach(auto ix, indexes) {
            int id = clientModel->data(ix.siblingAtColumn(0)).toInt(); //c->id();
            QString name = clientModel->data(ix.siblingAtColumn(1)).toString();
            QString number = clientModel->data(ix.siblingAtColumn(2)).toString();
            QString address = clientModel->data(ix.siblingAtColumn(3)).toString();
            QString email = clientModel->data(ix.siblingAtColumn(4)).toString();            //model에 있는 data에서 해당 칼럼의 있는 값들을 가져옴
            QStringList strings;
            strings << QString::number(id) << name << number << address <<email;            //string에 해당 값들을 넣어줌

            QList<QStandardItem *> items;
            for (int i = 0; i < 5; ++i) {
                items.append(new QStandardItem(strings.at(i)));
            }                                                                               //for문을 돌면서 standardItem에 item을 append 해줌
            s_clientModel->appendRow(items);

            s_clientModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
            s_clientModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
            s_clientModel->setHeaderData(2, Qt::Horizontal, tr("PhoneNumber"));
            s_clientModel->setHeaderData(3, Qt::Horizontal, tr("Address"));
            s_clientModel->setHeaderData(4, Qt::Horizontal, tr("Email"));                   //생성된 모델에 대한 header 명을 입력

        }

}


void ClientManagerForm::on_clearPushButton_clicked()
{
    c_clearLineEdit();              //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록
}


void ClientManagerForm::on_treeView_clicked(const QModelIndex &index)
{
    QString clientId = clientModel->data(index.siblingAtColumn(0)).toString();
    QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
    QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
    QString address = clientModel->data(index.siblingAtColumn(3)).toString();
    QString email = clientModel->data(index.siblingAtColumn(4)).toString();             //treeView item을 클릭했을때 해당 lineEdit에 정보가 들어감

    ui->clientIdLineEdit->setText(clientId);
    ui->clientNameLineEdit->setText(clientName);
    ui->phoneNumberLineEdit->setText(phoneNumber);
    ui->addressLineEdit->setText(address);
    ui->emailLineEdit->setText(email);
    ui->toolBox->setCurrentIndex(0);
}

void ClientManagerForm::findClient(int index, int c_id)                 //order의 clientTreewidget combobox의 index가 id일 때 (int)
{
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 0), Qt::EditRole, c_id, -1, Qt::MatchContains);  //client 정보를 비교해줌 내용이 해당될때 찾아주는 속성

    foreach(auto index, indexes) {
        int c_id = clientModel->data(index.siblingAtColumn(0)).toInt();
        QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
        QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
        QString address = clientModel->data(index.siblingAtColumn(3)).toString();
        QString email = clientModel->data(index.siblingAtColumn(4)).toString();         //sibling을 이용해 client 정보를 찾아냄
        emit sendClient(c_id, clientName, phoneNumber, address, email);
        }
}

void ClientManagerForm::findClient(int index, QString text)          //order의 clientTreewidget combobox의 index가 id 외 name, number, address, email일 때 (string)
{
//    auto flag = (index)? Qt::MatchCaseSensitive|Qt::MatchContains
//                       : Qt::MatchContains;
    if(index == 1)                                                                                                      //combobox 해당 index가 이름일 때
    {
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 1), Qt::EditRole, text, -1, Qt::MatchContains);  //해당 index에서 정보를 비교

        foreach(auto index, indexes) {
            int c_id = clientModel->data(index.siblingAtColumn(0)).toInt();
            QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
            QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
            QString address = clientModel->data(index.siblingAtColumn(3)).toString();
            QString email = clientModel->data(index.siblingAtColumn(4)).toString();
            emit sendClient(c_id, clientName, phoneNumber, address, email);                                             //찾은 정보를 order의 clientTreeWidget으로 보내줌
            }
    }

    else if(index == 2)                                                                                                 //해당 index에서 정보를 비교
    {

    QModelIndexList indexes = clientModel->match(clientModel->index(0, 2), Qt::EditRole, text, -1, Qt::MatchContains);

        foreach(auto index, indexes) {
            int c_id = clientModel->data(index.siblingAtColumn(0)).toInt();
            QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
            QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
            QString address = clientModel->data(index.siblingAtColumn(3)).toString();
            QString email = clientModel->data(index.siblingAtColumn(4)).toString();
            emit sendClient(c_id, clientName, phoneNumber, address, email);                                              //찾은 정보를 order의 clientTreeWidget으로 보내줌
        }
    }
    else if(index == 3)                                                                                                  //해당 index에서 정보를 비교
    {
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 3), Qt::EditRole, text, -1, Qt::MatchContains);

        foreach(auto index, indexes) {
            int c_id = clientModel->data(index.siblingAtColumn(0)).toInt();
            QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
            QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
            QString address = clientModel->data(index.siblingAtColumn(3)).toString();
            QString email = clientModel->data(index.siblingAtColumn(4)).toString();
            emit sendClient(c_id, clientName, phoneNumber, address, email);                                              //찾은 정보를 order의 clientTreeWidget으로 보내줌
        }
    }

    else if(index == 4)                                                                                                 //찾은 정보를 order의 clientTreeWidget으로 보내줌
    {
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 4), Qt::EditRole, text, -1, Qt::MatchContains);

        foreach(auto index, indexes) {
            int c_id = clientModel->data(index.siblingAtColumn(0)).toInt();
            QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
            QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
            QString address = clientModel->data(index.siblingAtColumn(3)).toString();
            QString email = clientModel->data(index.siblingAtColumn(4)).toString();
            emit sendClient(c_id, clientName, phoneNumber, address, email);                                             //찾은 정보를 order의 clientTreeWidget으로 보내줌
        }
    }
}

void ClientManagerForm::c_clearLineEdit()
{
    ui->clientIdLineEdit->clear();
    ui->clientNameLineEdit->clear();
    ui->phoneNumberLineEdit->clear();
    ui->addressLineEdit->clear();
    ui->emailLineEdit->clear();     //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록 하는 함수 구현
}
