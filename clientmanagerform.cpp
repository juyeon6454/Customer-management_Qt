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


int ClientManagerForm::makeId( )                     //아이디 자동부여
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
    int delid = index.sibling(index.row(), 0).data().toInt();

    int row = index.row();
    if(index.isValid()) {
        //clientList.remove(clientModel->data(index.siblingAtColumn(0)).toInt());
        clientModel->removeRow(index.row());
        clientModel->select();
        //ui->treeView->resizeColumnsToContents();
    }
    emit clientRemoved (delid, QString::number(row));       //treewidget에서 빼줌
    c_clearLineEdit();                                                                //lineEdit에 남은 기록을 지움

}

void ClientManagerForm::showContextMenu(const QPoint &pos)      //마우스 우클릭 위치 알림
{
    QPoint globalPos = ui->treeView->mapToGlobal(pos);
    if(ui->treeView->indexAt(pos).isValid())
    menu->exec(globalPos);
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
    if(db.isOpen() && clientName.length() && phoneNumber.length() && address.length()) {
        QSqlQuery query(clientModel->database());
        query.prepare("INSERT INTO client VALUES (?, ?, ?, ?, ?)");
        query.bindValue(0, clientId);
        query.bindValue(1, clientName);
        query.bindValue(2, phoneNumber);
        query.bindValue(3, address);
        query.bindValue(4, email);
        query.exec();

    }
//        if(clientName.length()) {
//            QSqlQuery query;

//        query.exec(QString("CREATE TABLE CLIENT(%1, '%2', '%3', '%4', '%5')")\
//                      .arg(clientId).arg(clientName).arg(phoneNumber).arg(address).arg(email));
//        clientModel->select();
//    }
    else
    {
        QMessageBox::critical(this, tr("Client Info"),                                   //메세지 박스로 다시 입력하게 함
                              tr("There is information that has not been entered."));
    }
    clientModel->select();
    emit clientAdded(clientId, clientName);                                              //server로 clientlist 보내기 위한 signal
    c_clearLineEdit();                                                                   //사용한 lineEdit 기록을 지움

}

void ClientManagerForm::on_modifyPushButton_clicked()                //수정 버튼 눌렀을 때
{
    QModelIndex index = ui->treeView->currentIndex();
    int molid = index.sibling(index.row(), 0).data().toInt();
    //QString moName = index.sibling(index.row(), 1).data().toString();
    QString clientName, phonenumber, address, email;
    clientName = ui->clientNameLineEdit->text();
    phonenumber = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();
    email = ui->emailLineEdit->text();
    int row = index.row();
    if(index.isValid()) {
//        int id = clientModel->data(index.siblingAtColumn(0)).toInt();
#if 1
//        clientModel->setData(index.siblingAtColumn(0), id);
        clientModel->setData(index.siblingAtColumn(1), clientName);
        clientModel->setData(index.siblingAtColumn(2), phonenumber);
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
       emit clientModified (molid, row, clientName);               //고객 정보 수정시 sever client리스트도 같이 수정


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
    ui->emailLineEdit->setText(email);
    ui->toolBox->setCurrentIndex(0);

}

void ClientManagerForm::findClient(int index, int c_id)
{
    auto flag = (index)? Qt::MatchCaseSensitive|Qt::MatchContains
                        : Qt::MatchCaseSensitive;
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 0), Qt::EditRole, c_id, -1,  Qt::MatchFlags(flag));

    foreach(auto index, indexes) {
        int c_id = clientModel->data(index.siblingAtColumn(0)).toInt();
        QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
        QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
        QString address = clientModel->data(index.siblingAtColumn(3)).toString();
        QString email = clientModel->data(index.siblingAtColumn(3)).toString();
        emit sendClient(c_id, clientName, phoneNumber, address, email);
        }
}

void ClientManagerForm::findClient(int index, QString text)
{
    //int i = ui->treeView->currentIndex();
    auto flag = (index)? Qt::MatchCaseSensitive|Qt::MatchContains
                       : Qt::MatchCaseSensitive;
    if(index == 1)
    {
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 1), Qt::EditRole, text, -1, Qt::MatchFlags(flag));

        foreach(auto index, indexes) {
            int c_id = clientModel->data(index.siblingAtColumn(0)).toInt();
            QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
            QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
            QString address = clientModel->data(index.siblingAtColumn(3)).toString();
            QString email = clientModel->data(index.siblingAtColumn(3)).toString();
            emit sendClient(c_id, clientName, phoneNumber, address, email);
            }
    }

    else if(index == 2)
    {

    QModelIndexList indexes = clientModel->match(clientModel->index(0, 2), Qt::EditRole, text, -1,Qt::MatchFlags(flag));

        foreach(auto index, indexes) {
            int c_id = clientModel->data(index.siblingAtColumn(0)).toInt();
            QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
            QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
            QString address = clientModel->data(index.siblingAtColumn(3)).toString();
            QString email = clientModel->data(index.siblingAtColumn(3)).toString();
            emit sendClient(c_id, clientName, phoneNumber, address, email);
        }
    }
    else if(index == 3)
    {
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 3), Qt::EditRole, text, -1, Qt::MatchFlags(flag));

        foreach(auto index, indexes) {
            int c_id = clientModel->data(index.siblingAtColumn(0)).toInt();
            QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
            QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
            QString address = clientModel->data(index.siblingAtColumn(3)).toString();
            QString email = clientModel->data(index.siblingAtColumn(3)).toString();
            emit sendClient(c_id, clientName, phoneNumber, address, email);
        }
    }

    else if(index == 4)
    {
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 4), Qt::EditRole, text, -1, Qt::MatchFlags(flag));

        foreach(auto index, indexes) {
            int c_id = clientModel->data(index.siblingAtColumn(0)).toInt();
            QString clientName = clientModel->data(index.siblingAtColumn(1)).toString();
            QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
            QString address = clientModel->data(index.siblingAtColumn(3)).toString();
            QString email = clientModel->data(index.siblingAtColumn(3)).toString();
            emit sendClient(c_id, clientName, phoneNumber, address, email);
        }
    }
}
