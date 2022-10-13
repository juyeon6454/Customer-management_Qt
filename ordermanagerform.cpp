#include "ordermanagerform.h"
#include "ui_ordermanagerform.h"
#include "orderitem.h"

#include <QFile>
#include <QMenu>

OrderManagerForm::OrderManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 540 << 400;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->orderSearchTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->orderSearchTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

}

void OrderManagerForm::loadData()
{
    QFile file("productlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int orderId = row[0].toInt();
            OrderItem* o = new OrderItem(orderId, row[1], row[2], row[3],row[4],row[5],row[6],row[7]);
            ui->orderSearchTreeWidget->addTopLevelItem(o);
            orderList.insert(orderId, o);

            emit clientAdded(row[2]);
        }
    }
    file.close( );
}

OrderManagerForm::~OrderManagerForm()
{
    delete ui;

    QFile file("orderlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    Q_FOREACH (const auto& v , orderList) {
        OrderItem* o = v;
        out << o->orderId() << ", " << o->getOrderDate() << ", ";
        out << o->getClientName() << ", " <<o->getPhoneNumber() << ", ";
        out << o->getAddress() << ", " <<o->getProductName()<<", ";
        out << o->getOrderQuantity() << ", "<<o->getTotalPrice()<< "\n";
    }
    file.close( );
}

int OrderManagerForm::makeId( )
{
    if(orderList.size( ) == 0) {
        return 300;
    } else {
        auto orderId = orderList.lastKey();
        return ++orderId;
    }
}

void OrderManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->orderSearchTreeWidget->currentItem();
    if(item != nullptr) {
        orderList.remove(item->text(0).toInt());
        ui->orderSearchTreeWidget->takeTopLevelItem(ui->orderSearchTreeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->orderSearchTreeWidget->update();
    }
}

void OrderManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->orderSearchTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}





void OrderManagerForm::on_orderSearchPushButton_clicked()
{
    ui->orderSearchTreeWidget->clear();
//    for(int i = 0; i < ui->treeWidget->columnCount(); i++)
    int i = ui->orderSearchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->orderSearchTreeWidget->findItems(ui->orderSearchLineEdit->text(), flag, i);

    Q_FOREACH(auto i, items) {
            OrderItem* o = static_cast<OrderItem*>(i);
            int orderId = o->orderId();
            QString orderDate = o->getOrderDate();
            QString clientName = o->getClientName();
            QString phoneNumber = o->getPhoneNumber();
            QString address = o->getAddress();
            QString productName = o->getProductName();
            QString orderQuantity = o->getOrderQuantity();
            QString totalPrice = o->getTotalPrice();
            OrderItem* item = new OrderItem(orderId,orderDate, clientName, phoneNumber, address, productName, orderQuantity, totalPrice);
            ui->orderSearchTreeWidget->addTopLevelItem(item);
        }
    }
}


void OrderManagerForm::on_oderInputAddPushButton_clicked()
{
        QString orderDate, clientName, phoneNumber, address, productName, orderQuantity, totalPrice;
        int orderId = makeId( );
        orderDate= ui->orderDateLineEdit->text();
        clientName = ui->clientNameLineEdit->text();
        phoneNumber = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        productName = ui->productNameLineEdit->text();
        orderQuantity = ui->orderQuantitySpinBox->text();
        totalPrice = ui->totalPriceLineEdit->text();
        if(clientName.length()) {
            OrderItem* o = new OrderItem(orderId, orderDate, clientName, phoneNumber, address, productName, orderQuantity, totalPrice);
            orderList.insert(orderId, o);
            ui->orderSearchTreeWidget->addTopLevelItem(o);
            emit clientAdded(clientName);
        }


}


void OrderManagerForm::on_orderInputModifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->orderSearchTreeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        OrderItem* o = orderList[key];
        QString orderDate, clientName, phoneNumber, address, productName, orderQuantity, totalPrice;
        orderDate= ui->orderDateLineEdit->text();
        clientName = ui->clientNameLineEdit->text();
        phoneNumber = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        productName = ui->productNameLineEdit->text();
        orderQuantity = ui->orderQuantitySpinBox->text();
        totalPrice = ui->totalPriceLineEdit->text();
        o->setOrderDate(orderDate);
        o->setClientName(clientName);
        o->setPhoneNumber(phoneNumber);
        o->setAddress(address);
        o->setProductName(productName);
        o->setOrderQuauntity(orderQuantity);
        o->setTotalPrice(totalPrice);
        orderList[key] = o;
    }
}


void OrderManagerForm::on_orderSearchTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    //return ;
        Q_UNUSED(column);
        ui->orderIdLineEdit->setText(item->text(0));
        ui->orderDateLineEdit->setText(item->text(1));
        ui->clientNameLineEdit->setText(item->text(2));
        ui->phoneNumberLineEdit->setText(item->text(3));
        ui->addressLineEdit->setText(item->text(4));
        ui->productNameLineEdit->setText(item->text(5));
        ui->orderQuantitySpinBox->setValue(item->text(6).toInt());
        ui->totalPriceLineEdit->setText(item->text(7));
       // ui->orderListGroupBox->setCurrentIndex(0);
}

