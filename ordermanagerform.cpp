#include "ordermanagerform.h"
#include "clientitem.h"
#include "ui_ordermanagerform.h"
#include "orderitem.h"

#include <QFile>
#include <QMenu>

#include <QDateTime>
#include <QDateEdit>
#include <QMessageBox>


OrderManagerForm::OrderManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 400 << 500;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->orderSearchTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->orderSearchTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    ui->o_clientInfoTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);//

}

void OrderManagerForm::loadData()
{
    QFile file("orderlist.txt");
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
            //emit clientAdded(row[2]);
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

    o_clearLineEdit();
}

void OrderManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->orderSearchTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}


void OrderManagerForm::on_orderSearchPushButton_clicked()
{
    ui->orderSearchTreeWidget_2->clear();
    //for(int i = 0; i < ui->treeWidget->columnCount(); i++)
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
            ui->orderSearchTreeWidget_2->addTopLevelItem(item);
        }
  }
    ui->orderSearchTreeWidget_2->setFocus();
}


void OrderManagerForm::on_oderInputAddPushButton_clicked()
{
        QString orderDate, clientName, phoneNumber, address, productName, orderQuantity, totalPrice;
        int orderId = makeId( );
        orderDate=currentDateTime();
        clientName = ui->clientNameLineEdit->text();
        phoneNumber = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        productName = ui->productNameLineEdit->text();
        orderQuantity = ui->orderQuantitySpinBox->text();
        int s = ui->o_productInfoTreeWidget->currentItem()->text(3).toInt();
        ui->orderQuantitySpinBox->setRange(1,s);
        //ui->orderQuantitySpinBox->setMaximum(s); //// 쓰지마셈 걍;;


        totalPrice = ui->totalPriceLineEdit->text();

        if(clientName.length()&&phoneNumber.length()&&address.length()&&productName.length()&& orderQuantity.length()) {
            OrderItem* o = new OrderItem(orderId, orderDate, clientName, phoneNumber, address, productName, orderQuantity,totalPrice);
            orderList.insert(orderId, o);
            ui->orderSearchTreeWidget->addTopLevelItem(o);
        }
        else
        {
            QMessageBox::critical(this, tr("Order Info"), \
                                  tr("There is information that has not been entered."));
        }
        o_clearLineEdit();
}

QString OrderManagerForm::currentDateTime()
{
    QString time_format = "yyyy-MM-dd  HH:mm:ss";
    QDateTime a = QDateTime::currentDateTime();
    QString as = a.toString(time_format);
    qDebug() << as;

    return as;
}

void OrderManagerForm::stockShowed(int stock)
{
    Q_UNUSED(stock);
    if(ui->o_productInfoTreeWidget->currentItem() != nullptr)
    {
    ui->orderQuantitySpinBox->setRange(1, stock);
    int s = ui->o_productInfoTreeWidget->currentItem()->text(3).toInt();
    ui->orderQuantitySpinBox->setRange(1, s);
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
        ui->totalPriceLineEdit->clear();
       //totalPrice = ui->totalPriceLineEdit->text();
        int x = ui->orderQuantitySpinBox->text().toInt();
        int y = ui->o_productInfoTreeWidget->currentItem()->text(2).toInt();
        totalPrice = QString::number(x*y);
        ui->totalPriceLineEdit->setText(totalPrice);
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

void OrderManagerForm::o_showIdClient(int c_id, ClientItem* clientItem)
{
    QString clientName, phoneNumber, address, email;
    int clientId = clientItem->ClientId();
    clientName = clientItem->getClientName();
    phoneNumber = clientItem->getPhoneNumber();
    address = clientItem->getAddress();
    email = clientItem->getEmail();
    if(QString::number(clientId).length()) {
        ClientItem* c = new ClientItem(clientId, clientName, phoneNumber, address, email);
//        clientList.insert(clientId, c);
        ui->o_clientInfoTreeWidget->addTopLevelItem(c);
    }
    //ui->o_clientInfoTreeWidget->addTopLevelItem(clientItem);
}


void OrderManagerForm::o_showNameClient(QString c_name, ClientItem* clientItem)
{
    QString clientName, phoneNumber, address, email;
    int clientId = clientItem->ClientId();
    clientName = clientItem->getClientName();
    phoneNumber = clientItem->getPhoneNumber();
    address = clientItem->getAddress();
    email = clientItem->getEmail();
    if(clientName.length()) {
        ClientItem* c = new ClientItem(clientId, clientName, phoneNumber, address,email);
        //clientList.insert(c_name, c);
        ui->o_clientInfoTreeWidget->addTopLevelItem(c);
    }
    //ui->o_clientInfoTreeWidget->addTopLevelItem(clientItem);
}


void OrderManagerForm::o_showNumberClient(QString c_number, ClientItem* clientItem)
{
    QString clientName, phoneNumber, address, email;
    int clientId = clientItem->ClientId();
    clientName = clientItem->getClientName();
    phoneNumber = clientItem->getPhoneNumber();
    address = clientItem->getAddress();
    email = clientItem->getEmail();
    if(phoneNumber.length()) {
        ClientItem* c = new ClientItem(clientId, clientName, phoneNumber, address, email);
        //clientList.insert(c_number, c);
        ui->o_clientInfoTreeWidget->addTopLevelItem(c);
    }
    //ui->o_clientInfoTreeWidget->addTopLevelItem(clientItem);
}

void OrderManagerForm::o_showAddressClient(QString c_address, ClientItem* clientItem)
{
    QString clientName, phoneNumber, address, email;
    int clientId = clientItem->ClientId();
    clientName = clientItem->getClientName();
    phoneNumber = clientItem->getPhoneNumber();
    address = clientItem->getAddress();
    email = clientItem->getEmail();
    if(address.length()) {
        ClientItem* c = new ClientItem(clientId, clientName, phoneNumber, address, email);
        //clientList.insert(c_address, c);
        ui->o_clientInfoTreeWidget->addTopLevelItem(c);
    }
    //ui->o_clientInfoTreeWidget->addTopLevelItem(clientItem);
}

void OrderManagerForm::o_showEmailClient(QString c_email, ClientItem* clientItem)
{
    QString clientName, phoneNumber, address,email;
    int clientId = clientItem->ClientId();
    clientName = clientItem->getClientName();
    phoneNumber = clientItem->getPhoneNumber();
    address = clientItem->getAddress();
    email = clientItem->getEmail();
    if(email.length()) {
        ClientItem* c = new ClientItem(clientId, clientName, phoneNumber, address,email);
        //clientList.insert(clientId, c);
        ui->o_clientInfoTreeWidget->addTopLevelItem(c);
    }
    //ui->o_clientInfoTreeWidget->addTopLevelItem(clientItem);
}

void OrderManagerForm::on_o_clientSearchPushButton_clicked()
{//combobox

   ui->o_clientInfoTreeWidget->clear();

   int index = ui->o_clientSearchComboBox->currentIndex();
   qDebug() << index;
   if(index == 0)
   {
    int c_id = ui->o_clientSearchLineEdit->text().toInt();
    emit o_searchIdClient(c_id);
   }
   else if(index == 1)
   {
      QString c_name = ui->o_clientSearchLineEdit->text();
      emit o_searchNameClient(c_name);
   }

   else if(index == 2)
   {
      QString c_number = ui->o_clientSearchLineEdit->text();
      emit o_searchNumberClient(c_number);
   }

   else if(index == 3)
   {
      QString c_address = ui->o_clientSearchLineEdit->text();
      emit o_searchAddressClient(c_address);
   }

   else if(index == 4)
   {
      QString c_email = ui->o_clientSearchLineEdit->text();
      emit o_searchEmailClient(c_email);
   }
}

void OrderManagerForm::o_showIdProduct(int p_id, ProductItem* productItem)
{
    QString productName, price, stock;
    int productId = productItem->productId();
    productName = productItem->getProductName();
    price = productItem->getPrice();
    stock = productItem->getStock();
    if(QString::number(productId).length()) {
        ProductItem* p = new ProductItem(productId, productName, price, stock);
//        clientList.insert(productId, c);
        ui->o_productInfoTreeWidget->addTopLevelItem(p);
    }
    //ui->o_clientInfoTreeWidget->addTopLevelItem(ProductItem);
}


void OrderManagerForm::o_showNameProduct(QString p_name, ProductItem* productItem)
{
    QString productName, price, stock;
    int productId = productItem->productId();
    productName = productItem->getProductName();
    price = productItem->getPrice();
    stock = productItem->getStock();
    if(productName.length()) {
        ProductItem* p = new ProductItem(productId, productName, price, stock);
//        clientList.insert(productId, c);
        ui->o_productInfoTreeWidget->addTopLevelItem(p);
    }
    //ui->o_clientInfoTreeWidget->addTopLevelItem(ProductItem);
}
void OrderManagerForm::o_showPriceProduct(QString p_price, ProductItem* productItem)
{
    QString productName, price, stock;
    int productId = productItem->productId();
    productName = productItem->getProductName();
    price = productItem->getPrice();
    stock = productItem->getStock();
    if(price.length()) {
        ProductItem* p = new ProductItem(productId, productName, price, stock);
//        clientList.insert(productId, c);
        ui->o_productInfoTreeWidget->addTopLevelItem(p);
    }
    //ui->o_clientInfoTreeWidget->addTopLevelItem(ProductItem);
}
void OrderManagerForm::o_showStockProduct(QString p_stock, ProductItem* productItem)
{
    QString productName, price, stock;
    int productId = productItem->productId();
    productName = productItem->getProductName();
    price = productItem->getPrice();
    stock = productItem->getStock();

    if(stock.length()) {
        ProductItem* p = new ProductItem(productId, productName, price, stock);
//        clientList.insert(productId, c);
          //stockList.insert(productId, p->stock);
        ui->o_productInfoTreeWidget->addTopLevelItem(p);
    }
    //ui->o_clientInfoTreeWidget->addTopLevelItem(ProductItem);
}



void OrderManagerForm::on_o_productSearchPushButton_clicked()
{

     ui->o_productInfoTreeWidget->clear();

    int index = ui->o_productSearchComboBox->currentIndex();
    qDebug() << index;
    if(index == 0)
    {
     int p_id = ui->o_productSearchLineEdit->text().toInt();
     emit o_searchIdProduct(p_id);
    }
    else if(index == 1)
    {
       QString p_name = ui->o_productSearchLineEdit->text();
       emit o_searchNameProduct(p_name);
    }

    else if(index == 2)
    {
       QString p_price = ui->o_productSearchLineEdit->text();
       emit o_searchPriceProduct(p_price);
    }

    else if(index == 3)
    {
       QString p_stock = ui->o_productSearchLineEdit->text();
       emit o_searchStockProduct(p_stock);
    }

}


void OrderManagerForm::on_o_clientInfoTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->clientNameLineEdit->setText(item->text(1));
    ui->phoneNumberLineEdit->setText(item->text(2));
    ui->addressLineEdit->setText(item->text(3));
    //ui->toolBox->setCurrentIndex(0);

}


void OrderManagerForm::on_o_productInfoTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->orderQuantitySpinBox->setValue(0);
    ui->productNameLineEdit->setText(item->text(1));
    //ui->orderQuantitySpinBox->setText(item->);
    ui->totalPriceLineEdit->setText(item->text(2));
}




void OrderManagerForm::on_o_clientSearchLineEdit_returnPressed()
{

    ui->o_clientInfoTreeWidget->clear();

    int index = ui->o_clientSearchComboBox->currentIndex();
    qDebug() << index;
    if(index == 0)
    {
     int c_id = ui->o_clientSearchLineEdit->text().toInt();
     emit o_searchIdClient(c_id);
    }
    else if(index == 1)
    {
       QString c_name = ui->o_clientSearchLineEdit->text();
       emit o_searchNameClient(c_name);
    }

    else if(index == 2)
    {
       QString c_number = ui->o_clientSearchLineEdit->text();
       emit o_searchNumberClient(c_number);
    }

    else if(index == 3)
    {
       QString c_address = ui->o_clientSearchLineEdit->text();
       emit o_searchAddressClient(c_address);
    }

    else if(index == 4)
    {
       QString c_email = ui->o_clientSearchLineEdit->text();
       emit o_searchEmailClient(c_email);
    }
}


void OrderManagerForm::on_o_productSearchLineEdit_returnPressed()
{

    ui->o_productInfoTreeWidget->clear();

   int index = ui->o_productSearchComboBox->currentIndex();
   qDebug() << index;
   if(index == 0)
   {
    int p_id = ui->o_productSearchLineEdit->text().toInt();
    emit o_searchIdProduct(p_id);
   }
   else if(index == 1)
   {
      QString p_name = ui->o_productSearchLineEdit->text();
      emit o_searchNameProduct(p_name);
   }

   else if(index == 2)
   {
      QString p_price = ui->o_productSearchLineEdit->text();
      emit o_searchPriceProduct(p_price);
   }

   else if(index == 3)
   {
      QString p_stock = ui->o_productSearchLineEdit->text();
      emit o_searchStockProduct(p_stock);
   }

}


void OrderManagerForm::on_orderSearchLineEdit_returnPressed()
{
    ui->orderSearchTreeWidget_2->clear();
    //for(int i = 0; i < ui->treeWidget->columnCount(); i++)
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
            ui->orderSearchTreeWidget_2->addTopLevelItem(item);
        }
  }
    ui->orderSearchTreeWidget_2->setFocus();
}


void OrderManagerForm::on_orderQuantitySpinBox_valueChanged(int stock)
{

    if (ui->o_productInfoTreeWidget->currentItem() == nullptr){
        void on_o_clientInfoTreeWidget_itemClicked();
    }
    else
    {
        int x = ui->orderQuantitySpinBox->text().toInt();
        int y = ui->o_productInfoTreeWidget->currentItem()->text(2).toInt();
        int totalPrice = x*y;
        ui->totalPriceLineEdit->setText(QString::number(totalPrice));
    }
    emit stockSearched(stock);

}

void OrderManagerForm::on_orderClearPushButton_clicked()
{
    o_clearLineEdit();
}

void OrderManagerForm::o_clearLineEdit()
{
    ui->orderDateLineEdit->clear();
    ui->orderIdLineEdit->clear();
    ui->addressLineEdit->clear();
    ui->clientNameLineEdit->clear();
    ui->phoneNumberLineEdit->clear();
    ui->totalPriceLineEdit->clear();
    ui->productNameLineEdit->clear();
    ui->orderQuantitySpinBox->setValue(0);
}

