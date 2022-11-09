#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"
//#include "clientitem.h"

#include <QFile>
#include <QMenu>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QTreeView>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>

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
    connect(ui->treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));


}

void ClientManagerForm::loadData()                              //저장된 파일 로드
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "clientConnection");
    db.setDatabaseName("clientlist.db");
    if (db.open( )) {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS client(id INTEGER Primary Key, name VARCHAR(30) NOT NULL, phoneNumber VARCHAR(20) NOT NULL, address VARCHAR(50), email VARCHAR(50));");
        qDebug() << "table";
        clientModel = new QSqlTableModel(this, db);
        clientModel->setTable("client");
        clientModel->select();
        clientModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        clientModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        clientModel->setHeaderData(2, Qt::Horizontal, tr("Phone Number"));
        clientModel->setHeaderData(3, Qt::Horizontal, tr("Address"));
        clientModel->setHeaderData(4, Qt::Horizontal, tr("Email"));

        ui->treeView->setModel(clientModel);
    }

    for(int i = 0; i < clientModel->rowCount(); i++) {
        int clientId = clientModel->data(clientModel->index(i, 0)).toInt();
        QString clientName = clientModel->data(clientModel->index(i, 1)).toString();
        //clientList.insert(id, clientModel->index(i, 0));
       emit clientAdded(clientId, clientName);
    }

}

ClientManagerForm::~ClientManagerForm()
{
    delete ui;
    QSqlDatabase db = QSqlDatabase::database("clientConnection");
    if(db.isOpen()) {
        clientModel->submitAll();
        delete clientModel;
        db.commit();
        db.close();
    }
}


int ClientManagerForm::makeId( )                  //아이디 자동부여
{
    if(clientModel->rowCount() == 0) {               //model에 아무것도 없으면
        return 100;                                  //100부터 반환
    } else {
        auto clientId = clientModel->data(clientModel->index(clientModel->rowCount()-1, 0)).toInt();
        return ++clientId;
    }
}

void ClientManagerForm::removeItem()
{
    QModelIndex index = ui->treeView->currentIndex();
    if(index.isValid()) {
        //clientList.remove(clientModel->data(index.siblingAtColumn(0)).toInt());
        clientModel->removeRow(index.row());
        clientModel->select();
        //ui->treeView->resizeColumnsToContents();
    }
//        emit clientRemoved (item->text(0).toInt(), QString::number(rmindex));       //treewidget에서 빼줌
//    }

    c_clearLineEdit();    //lineEdit에 남은 기록을 지움

}

void ClientManagerForm::showContextMenu(const QPoint &pos)      //마우스 우클릭 위치 알림
{
    QPoint globalPos = ui->treeView->mapToGlobal(pos);
    if(ui->treeView->indexAt(pos).isValid())
    menu->exec(globalPos);
}

void ClientManagerForm::on_searchPushButton_clicked()           //고객 조회 버튼 클릭했을 때
{
    ui->searchTreeWidget->clear();                              //lineEdit에 남아있을 정보를 지움

    int i = ui->searchComboBox->currentIndex();                 //콤보박스 아이템을 인덱스로 받음
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    QModelIndexList indexes = clientModel->match(clientModel->index(0, i), Qt::EditRole, ui->searchLineEdit->text(), -1, Qt::MatchFlags(flag));

    foreach(auto ix, indexes) {
        int id = clientModel->data(ix.siblingAtColumn(0)).toInt(); //c->id();
        QString name = clientModel->data(ix.siblingAtColumn(1)).toString();
        QString number = clientModel->data(ix.siblingAtColumn(2)).toString();
        QString address = clientModel->data(ix.siblingAtColumn(3)).toString();
        QString email = clientModel->data(ix.siblingAtColumn(4)).toString();
        QStringList strings;
        strings << QString::number(id) << name << number << address <<email;
        new QTreeWidgetItem(ui->searchTreeWidget, strings);
        for(int i = 0; i < ui->searchTreeWidget->columnCount(); i++)
            ui->searchTreeWidget->resizeColumnToContents(i);
    }
}


void ClientManagerForm::on_modifyPushButton_clicked()                //수정 버튼 눌렀을 때
{
    QModelIndex index = ui->treeView->currentIndex();
    if(index.isValid()) {
//        int id = clientModel->data(index.siblingAtColumn(0)).toInt();
        QString name, number, address, email;
        name = ui->clientNameLineEdit->text();
        number = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        email = ui->emailLineEdit->text();
#if 1
//        clientModel->setData(index.siblingAtColumn(0), id);
        clientModel->setData(index.siblingAtColumn(1), name);
        clientModel->setData(index.siblingAtColumn(2), number);
        clientModel->setData(index.siblingAtColumn(3), address);
        clientModel->setData(index.siblingAtColumn(4), email);
        clientModel->submit();
#else
        QSqlQuery query(clientModel->database());
        query.prepare("UPDATE client SET name = ?, phoneNumber = ?, address = ?, email = ?, WHERE id = ?");
        query.bindValue(0, name);
        query.bindValue(1, number);
        query.bindValue(2, address);
        query.bindValue(3, email);
        query.bindValue(4, id);
        query.exec();
#endif
        clientModel->select();
        //ui->treeView->resizeColumnsToContents();
    }
       // emit clientModified (key, index, clientName);               //고객 정보 수정시 sever client리스트도 같이 수정


}


void ClientManagerForm::on_addPushButton_clicked()                                       //고객정보 입력 버튼을 누를 때
{

    QString clientName, phoneNumber, address, email;
    int clientId = makeId( );
    ui->clientIdLineEdit->setText(QString::number(clientId));
    clientName = ui->clientNameLineEdit->text();
    phoneNumber = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();
    email = ui->emailLineEdit->text();

    QSqlDatabase db = QSqlDatabase::database("clientConnection");
    if(db.isOpen() && clientName.length()) {
        QSqlQuery query(db);
        query.prepare("INSERT INTO client VALUES (?, ?, ?, ?, ?)");
        query.bindValue(0, clientId);
        query.bindValue(1, clientName);
        query.bindValue(2, phoneNumber);
        query.bindValue(3, address);
        query.bindValue(4, email);
        query.exec();
        clientModel->select();
        //ui->treeView->allColumnsShowFocus();
        }
    else
    {
        QMessageBox::critical(this, tr("Client Info"),                                   //메세지 박스로 다시 입력하게 함
                              tr("There is information that has not been entered."));
    }
    emit clientAdded(clientId, clientName);
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
//    auto items = ui->treeWidget->findItems(QString::number(c_id), Qt::MatchContains|Qt::MatchCaseSensitive,0);

//    foreach(auto i, items) {
//        ClientItem* c = static_cast<ClientItem*>(i);
//        int clientId = c->ClientId();
//        QString clientName = c->getClientName();
//        QString phoneNumber = c->getPhoneNumber();
//        QString address = c->getAddress();
//        QString email = c->getEmail();
//        ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);

//        emit c_sendIdClient(c_id, item);    //order에서 정보를 찾아달라는 signal을 보내면 client 정보를 찾아서 찾았다는 signal을 보내준다 (id값)
//    }
}

void ClientManagerForm::c_findNameClient(QString c_name)
{
//    auto items = ui->treeWidget->findItems(c_name, Qt::MatchContains|Qt::MatchCaseSensitive, 1);

//    foreach(auto i, items) {
//        ClientItem* c = static_cast<ClientItem*>(i);
//        int clientId = c->ClientId();
//        QString clientName = c->getClientName();
//        QString phoneNumber = c->getPhoneNumber();
//        QString address = c->getAddress();
//        QString email = c->getEmail();
//        ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);

//        emit c_sendNameClient(c_name, item);  //order에서 정보를 찾아달라는 signal을 보내면 client 정보를 찾아서 찾았다는 signal을 보내준다 (name 값)
//    }

}

void ClientManagerForm::c_findNumberClient(QString c_number)
{
//    auto items = ui->treeWidget->findItems(c_number, Qt::MatchContains|Qt::MatchCaseSensitive, 2);

//    foreach(auto i, items) {
//        ClientItem* c = static_cast<ClientItem*>(i);
//        int clientId = c->ClientId();
//        QString clientName = c->getClientName();
//        QString phoneNumber = c->getPhoneNumber();
//        QString address = c->getAddress();
//        QString email = c->getEmail();
//        ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);

//        emit c_sendNumberClient(c_number, item); //order에서 정보를 찾아달라는 signal을 보내면 client 정보를 찾아서 찾았다는 signal을 보내준다 (phonenumber 값)
//    }

}

void ClientManagerForm::c_findAddressClient(QString c_address)
{
//    auto items = ui->treeWidget->findItems(c_address, Qt::MatchContains|Qt::MatchCaseSensitive, 3);

//    foreach(auto i, items) {
//        ClientItem* c = static_cast<ClientItem*>(i);
//        int clientId = c->ClientId();
//        QString clientName = c->getClientName();
//        QString phoneNumber = c->getPhoneNumber();
//        QString address = c->getAddress();
//        QString email = c->getEmail();
//        ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);

//        emit c_sendAddressClient(c_address, item); //order에서 정보를 찾아달라는 signal을 보내면 client 정보를 찾아서 찾았다는 signal을 보내준다 (address 값)
//    }

}

void ClientManagerForm::c_findEmailClient(QString c_email)
{
//    auto items = ui->treeWidget->findItems(c_email, Qt::MatchContains|Qt::MatchCaseSensitive, 4);

//    foreach(auto i, items) {
//        ClientItem* c = static_cast<ClientItem*>(i);
//        int clientId = c->ClientId();
//        QString clientName = c->getClientName();
//        QString phoneNumber = c->getPhoneNumber();
//        QString address = c->getAddress();
//        QString email = c->getEmail();
//        ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);

//        emit c_sendEmailClient(c_email, item); //order에서 정보를 찾아달라는 signal을 보내면 client 정보를 찾아서 찾았다는 signal을 보내준다 (email 값)
//    }

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

//bool ClientManagerForm::createConnection( )
//{
////    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
////    db.setDatabaseName("Oracle11gx64");
////    db.setUserName("miniproject_3");
////    db.setPassword("1234");
////    if (!db.open()) {
////        qDebug() << db.lastError().text();
////    } else {
////        qDebug("success");
////    }

////    return true;

//    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

//     QSqlDatabase db = QSqlDatabase::database();
//    db.setDatabaseName("clientlist.db");
//    if (db.open( )) {
//        QSqlQuery query;
//        query.exec("CREATE TABLE IF NOT EXISTS client(id INTEGER Primary Key, name VARCHAR(30) NOT NULL, phoneNumber VARCHAR(20) NOT NULL, address VARCHAR(50), email VARCHAR(50);");
//    }

//    return true;
//}


void ClientManagerForm::on_treeView_clicked(const QModelIndex &index)
{
    QString clientId = clientModel->data(index.siblingAtColumn(0)).toString();
    QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
    QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
    QString address = clientModel->data(index.siblingAtColumn(3)).toString();
    QString email = clientModel->data(index.siblingAtColumn(4)).toString();

    ui->clientIdLineEdit->setText(clientId);
    ui->clientNameLineEdit->setText(clientName);
    ui->phoneNumberLineEdit->setText(phoneNumber);
    ui->addressLineEdit->setText(address);
    ui->toolBox->setCurrentIndex(0);

}

