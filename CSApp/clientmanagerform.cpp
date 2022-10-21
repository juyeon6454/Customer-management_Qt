#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"
#include "clientitem.h"

#include <QFile>
#include <QMenu>

ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 540 << 400;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

}

void ClientManagerForm::loadData()
{
    QFile file("clientlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int clientId = row[0].toInt();
            ClientItem* c = new ClientItem(clientId, row[1], row[2], row[3],row[4]);
            ui->treeWidget->addTopLevelItem(c);
            clientList.insert(clientId, c);

            emit clientAdded(clientId,row[1]);
            //emit clientModified(clientId,row[1], row[2], row[3],row[4]);
        }
    }
    file.close( );
}

ClientManagerForm::~ClientManagerForm()
{
    delete ui;

    QFile file("clientlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : clientList) {
        ClientItem* c = v;
        out << c->ClientId() << ", " << c->getClientName() << ", ";
        out << c->getPhoneNumber() << ", ";
        out << c->getAddress() << ", ";
        out << c->getEmail() << "\n";
    }
    file.close( );
}


int ClientManagerForm::makeId( )
{
    if(clientList.size( ) == 0) {
        return 100;
    } else {
        auto ClientId = clientList.lastKey();
        return ++ClientId;
    }
}

void ClientManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    int rmindex = ui->treeWidget->indexOfTopLevelItem(item);
    if(item != nullptr) {
        clientList.remove(item->text(0).toInt());
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->treeWidget->update();

        emit clientRemoved (item->text(0).toInt(), QString::number(rmindex));
    }

    ui->clientNameLineEdit->clear();
    ui->phoneNumberLineEdit->clear();
    ui->addressLineEdit->clear();
    ui->emailLineEdit->clear();

}

void ClientManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ClientManagerForm::on_searchPushButton_clicked()
{
    ui->searchTreeWidget->clear();

//    for(int i = 0; i < ui->treeWidget->columnCount(); i++)
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), flag, i);

        foreach(auto i, items) {
            ClientItem* c = static_cast<ClientItem*>(i);
            int clientId = c->ClientId();
            QString clientName = c->getClientName();
            QString phoneNumber = c->getPhoneNumber();
            QString address = c->getAddress();
            QString email = c->getEmail();
            ClientItem* item = new ClientItem(clientId,clientName, phoneNumber, address, email);
            ui->searchTreeWidget->addTopLevelItem(item);
        }
    }
}


void ClientManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        ClientItem* c = clientList[key];
        QString clientName, phoneNumber, address, email;
        clientName = ui->clientNameLineEdit->text();
        phoneNumber = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        email = ui->emailLineEdit->text();
        c->setClientName(clientName);
        c->setPhoneNumber(phoneNumber);
        c->setAddress(address);
        c->setEmail(email);
        clientList[key] = c;

        ui->clientNameLineEdit->clear();
        ui->phoneNumberLineEdit->clear();
        ui->addressLineEdit->clear();
        ui->emailLineEdit->clear();



        emit clientAdded(key, clientName);//server로 client이름 전달
        //emit clientModified(key, clientName,phoneNumber, address,email);
        //버튼 눌렀을때 clientModified emit

    }

}


void ClientManagerForm::on_addPushButton_clicked()
{
    QString clientName, phoneNumber, address,email;
    int clientId = makeId( );
    clientName = ui->clientNameLineEdit->text();
    phoneNumber = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();
    email = ui->emailLineEdit->text();
    if(clientName.length()) {
        ClientItem* c = new ClientItem(clientId, clientName, phoneNumber, address, email);
        clientList.insert(clientId, c);
        ui->treeWidget->addTopLevelItem(c);

        emit clientAdded(clientId,clientName);
    }
    ui->clientNameLineEdit->clear();
    ui->phoneNumberLineEdit->clear();
    ui->addressLineEdit->clear();
    ui->emailLineEdit->clear();

}


void ClientManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
//    ui->clientIdLineEdit->clear();
//    ui->clientNameLineEdit->clear();
//    ui->phoneNumberLineEdit->clear();
//    ui->addressLineEdit->clear();
//    ui->emailLineEdit->clear();

    ui->clientIdLineEdit->setText(item->text(0));
    ui->clientNameLineEdit->setText(item->text(1));
    ui->phoneNumberLineEdit->setText(item->text(2));
    ui->addressLineEdit->setText(item->text(3));
    ui->emailLineEdit->setText(item->text(4));
    ui->toolBox->setCurrentIndex(0);



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

        emit c_sendIdClient(c_id, item);
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

        emit c_sendNameClient(c_name, item);
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

        emit c_sendNumberClient(c_number, item);
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

        emit c_sendAddressClient(c_address, item);
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

        emit c_sendEmailClient(c_email, item);
    }

}


void ClientManagerForm::on_clearPushButton_clicked()
{
    ui->clientIdLineEdit->clear();
    ui->clientNameLineEdit->clear();
    ui->phoneNumberLineEdit->clear();
    ui->addressLineEdit->clear();
    ui->emailLineEdit->clear();
}

