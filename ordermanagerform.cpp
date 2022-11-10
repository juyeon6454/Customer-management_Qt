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
    ui->setupUi(this);       // ui 파일이 만들어짐 (this) 현재 class에 ui 파일 올림

    QList<int> sizes;
    sizes << 400 << 500;
    ui->splitter->setSizes(sizes);      /*splitter 사이즈 조절*/

    QAction* removeAction = new QAction(tr("&Remove"));                 //삭제 액션 생성
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));     //액션 신호를 보낼 때 아이템 삭제

    menu = new QMenu;                                                           //메뉴 생성
    menu->addAction(removeAction);                                              //메뉴에 remove 액션 추가
    ui->orderSearchTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);     //(우클릭 메뉴)
    connect(ui->orderSearchTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    ui->o_clientInfoTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);    //삭제 우클릭 메뉴
}

void OrderManagerForm::loadData()                           //저장된 파일 로드
{
    QFile file("orderlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  //지정된 이름 파일을 열 때 오류 검사
        return;                                             //오류 발생시 return;

    QTextStream in(&file);                                  //오류 발생하지 않으면 orderlist.txt 불러옴
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");              // , 을 기준으로 나눠서 row 0~7에 item 저장
        if(row.size()) {
            int orderId = row[0].toInt();
            OrderItem* o = new OrderItem(orderId, row[1], row[2], row[3],row[4],row[5],row[6],row[7]);
            ui->orderSearchTreeWidget->addTopLevelItem(o);
            orderList.insert(orderId, o);                   //저장한 순서로 treewidget에 나타내줌
        }
    }
    file.close( );                                          //파일 열었으니 닫음
}

OrderManagerForm::~OrderManagerForm()
{
    delete ui;                                                          //ui delete

    QFile file("orderlist.txt");                                        //데이터 파일을 만들어서 내보냄
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

int OrderManagerForm::makeId( )                 //아이디 자동부여
{
    if(orderList.size( ) == 0) {                //list에 아무것도 없으면
        return 300;                             //300부터 반환
    } else {
        auto orderId = orderList.lastKey();     //list에 목록이 있으면 마지막 키를 기준으로
        return ++orderId;                       //그 뒷번호부터 반환
    }
}

void OrderManagerForm::removeItem()                                     //주문 아이템 삭제
{
    QTreeWidgetItem* item = ui->orderSearchTreeWidget->currentItem();   //주문조회treewidget에서 현재 지정된 아이템
    if(item != nullptr) {                                               //아이템이 없으면
        orderList.remove(item->text(0).toInt());                        //0번째 (id)를 int 값으로 변환해서
        ui->orderSearchTreeWidget->takeTopLevelItem(ui->orderSearchTreeWidget->indexOfTopLevelItem(item));
        ui->orderSearchTreeWidget->update();                            //treewidget에서 빼줌
    }

    o_clearLineEdit();      //lineEdit에 남은 기록을 지움
}

void OrderManagerForm::showContextMenu(const QPoint &pos)               //마우스 우클릭 위치 알림
{
    QPoint globalPos = ui->orderSearchTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}


void OrderManagerForm::on_orderSearchPushButton_clicked()       //주문 조회 버튼 클릭했을 때
{
    ui->orderSearchTreeWidget_2->clear();                       //lineEdit에 남아있을 정보를 지움

    int i = ui->orderSearchComboBox->currentIndex();            //콤보박스 아이템을 인덱스로 받음
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->orderSearchTreeWidget->findItems(ui->orderSearchLineEdit->text(), flag, i);
        //주문조회입력칸에 있는 텍스트를 뽑아 treewidget에서 아이템을 찾음

    Q_FOREACH(auto i, items) {                              //해당 인덱스에 있는 item으로 foreact 돌아서
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
            ui->orderSearchTreeWidget_2->addTopLevelItem(item); //해당 정보들을 뽑아서 2_treewidget에 보여줌
        }
  }
    ui->orderSearchTreeWidget_2->setFocus();
}


void OrderManagerForm::on_oderInputAddPushButton_clicked()                                              //주문 입력 버튼을 누를 때
{
        QString orderDate, clientName, phoneNumber, address, productName, orderQuantity, totalPrice;
        int orderId = makeId( );                                                                        //id 자동입력값 반환
        orderDate=currentDateTime();                                                                    //주문 날짜 및 시간 자동입력값 반환
        clientName = ui->clientNameLineEdit->text();
        phoneNumber = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        productName = ui->productNameLineEdit->text();                                                  /*lineEdit에 입력된 텍스트*/

        orderQuantity = ui->orderQuantitySpinBox->text();                                               //주문수량 spinbox로 뽑아옴
        int s = ui->o_productInfoTreeWidget->currentItem()->text(3).toInt();                            //상품 조회 treewidget에서 stock값을 뽑아서 spinbox 제한값 범위 지정
        ui->orderQuantitySpinBox->setRange(1,s);                                                        //최소값 1 최대값 s (물품 재고량에 따라 달라짐)

        totalPrice = ui->totalPriceLineEdit->text();                                                    //totalPrice spinbox 변화에 따른 값이 나타남

        if(clientName.length()&&phoneNumber.length()&&address.length()&&productName.length()&& orderQuantity.length()) {                //비어있는 값이 있으면
            OrderItem* o = new OrderItem(orderId, orderDate, clientName, phoneNumber, address, productName, orderQuantity,totalPrice);
            orderList.insert(orderId, o);
            ui->orderSearchTreeWidget->addTopLevelItem(o);
        }
        else
        {
            QMessageBox::critical(this, tr("Order Info"), \
                                  tr("There is information that has not been entered."));                                               //메세지 박스로 다시 입력하게 함
        }
        o_clearLineEdit();                                                                                                               //사용한 lineEdit 기록을 지움
}

QString OrderManagerForm::currentDateTime()         //날짜시간 자동입력 함수
{
    QString time_format = "yyyy-MM-dd  HH:mm:ss";
    QDateTime a = QDateTime::currentDateTime();     //현재 날짜시간을 받아옴
    QString as = a.toString(time_format);

    return as;                                      //as 값 반환
}

void OrderManagerForm::stockShowed(int stock)                               //product에서 재고량 받아옴
{
    Q_UNUSED(stock);
    if(ui->o_productInfoTreeWidget->currentItem() != nullptr)               //treewidget에 지정한 아이템이 있을 때
    {
    ui->orderQuantitySpinBox->setRange(1, stock);                           //spinbox 제한 범위 설정
    int s = ui->o_productInfoTreeWidget->currentItem()->text(3).toInt();    //product조회 시 선택한 아이템이 있으면
    ui->orderQuantitySpinBox->setRange(1, s);                               //spinbox 제한 범위 설정
    }
}

void OrderManagerForm::on_orderInputModifyPushButton_clicked()              //수정 버튼 눌렀을 때
{
    QTreeWidgetItem* item = ui->orderSearchTreeWidget->currentItem();       //treewidget에서 현재 아이템
    if(item != nullptr) {                                                   //선택한 아이템이 있을 때
        int key = item->text(0).toInt();                                    //item의 0번쨰 텍스트를 int형 key값으로 뽑아옴
        OrderItem* o = orderList[key];
        QString orderDate, clientName, phoneNumber, address, productName, orderQuantity, totalPrice;
        orderDate= ui->orderDateLineEdit->text();
        clientName = ui->clientNameLineEdit->text();
        phoneNumber = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        productName = ui->productNameLineEdit->text();
        orderQuantity = ui->orderQuantitySpinBox->text();                   /*key 값을 통해 아이템의 정보들을 해당칸에 나타냄*/

        ui->totalPriceLineEdit->clear();                                    //수정할 때 다시 계산한 값이 들어가도록 원래 값 비워줌
        int x = ui->orderQuantitySpinBox->text().toInt();                   //spinbox 값 x
        int y = ui->o_productInfoTreeWidget->currentItem()->text(2).toInt();//상품 가격 y
        totalPrice = QString::number(x*y);                                  //totalPrice x*y
        ui->totalPriceLineEdit->setText(totalPrice);                        //계산한 값을 해당 lineEdit에 나타냄

        o->setOrderDate(orderDate);
        o->setClientName(clientName);
        o->setPhoneNumber(phoneNumber);
        o->setAddress(address);
        o->setProductName(productName);
        o->setOrderQuauntity(orderQuantity);
        o->setTotalPrice(totalPrice);
        orderList[key] = o;                                                  /*해당 정보들을 orderList에 담음*/
    }
}

void OrderManagerForm::on_orderSearchTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
        Q_UNUSED(column);
        ui->orderIdLineEdit->setText(item->text(0));
        ui->orderDateLineEdit->setText(item->text(1));
        ui->clientNameLineEdit->setText(item->text(2));
        ui->phoneNumberLineEdit->setText(item->text(3));
        ui->addressLineEdit->setText(item->text(4));
        ui->productNameLineEdit->setText(item->text(5));
        ui->orderQuantitySpinBox->setValue(item->text(6).toInt());
        ui->totalPriceLineEdit->setText(item->text(7));                     /*treeWidget 아이템 클릭시 각 해당칸에 정보 나타남*/
}

void OrderManagerForm::showClient(int c_id, QString clientName, QString phoneNumber, QString address, QString email)
{
    ui->o_clientInfoTreeWidget->clear();
    QTreeWidgetItem *clientItem = new QTreeWidgetItem(ui->o_clientInfoTreeWidget);

    if(QString::number(c_id).length()) {
    clientItem->setText(0, QString::number(c_id));
    clientItem->setText(1, clientName);
    clientItem->setText(2, phoneNumber);
    clientItem->setText(3, address);
    clientItem->setText(4, email);

    }
//    if(QString::number(c_id).length()) {
//        ClientItem* c = new ClientItem(c_id, clientName, phoneNumber, address, email); /*id로 해당 고객의 정보를 전부 가져와 보여줌*/
//        ui->o_clientInfoTreeWidget->addTopLevelItem(c);
//    }

    ui->o_clientInfoTreeWidget->addTopLevelItem(clientItem);
}

void OrderManagerForm::showProduct(int p_id, QString productName, QString price, QString stock)
{
    ui->o_productInfoTreeWidget->clear();
    QTreeWidgetItem *productItem = new QTreeWidgetItem(ui->o_productInfoTreeWidget);

    if(QString::number(p_id).length()) {
    productItem->setText(0, QString::number(p_id));
    productItem->setText(1, productName);
    productItem->setText(2, price);
    productItem->setText(3, stock);
    }
//    if(QString::number(c_id).length()) {
//        ClientItem* c = new ClientItem(c_id, clientName, phoneNumber, address, email); /*id로 해당 고객의 정보를 전부 가져와 보여줌*/
//        ui->o_clientInfoTreeWidget->addTopLevelItem(c);
//    }
}



void OrderManagerForm::on_o_clientSearchPushButton_clicked() //고객정보 조회 버튼을 누를 때
{
   ui->o_clientInfoTreeWidget->clear();

   int index = ui->o_clientSearchComboBox->currentIndex();  //어떤 콤보박스 카테고리가 선택되었는지 인덱스로 받아옴
   if(index == 0)
   {
    int c_id = ui->o_clientSearchLineEdit->text().toInt();
    emit searchClient(index, c_id);                            //id로 검색 할 때 signal로 id값을 보내줌
   }
   else
   {
      QString text = ui->o_clientSearchLineEdit->text();
      emit searchClient(index, text);                      //이름으로 검색 할 때 signal로 이름 값을 보내줌
   }
}

void OrderManagerForm::o_showIdProduct(int p_id, ProductItem* productItem)  /*id로 해당 상품의 정보를 전부 가져와 보여줌*/
{
    QString productName, price, stock;
    int productId = productItem->productId();
    productName = productItem->getProductName();
    price = productItem->getPrice();
    stock = productItem->getStock();
    if(QString::number(productId).length()) {
        ProductItem* p = new ProductItem(productId, productName, price, stock);
        ui->o_productInfoTreeWidget->addTopLevelItem(p);
    }
}


void OrderManagerForm::o_showNameProduct(QString p_name, ProductItem* productItem)  /*상품명으로 해당 상품의 정보를 전부 가져와 보여줌*/
{
    QString productName, price, stock;
    int productId = productItem->productId();
    productName = productItem->getProductName();
    price = productItem->getPrice();
    stock = productItem->getStock();
    if(productName.length()) {
        ProductItem* p = new ProductItem(productId, productName, price, stock);
        ui->o_productInfoTreeWidget->addTopLevelItem(p);
    }
}

void OrderManagerForm::o_showPriceProduct(QString p_price, ProductItem* productItem)  /*상품가격으로 해당 상품의 정보를 전부 가져와 보여줌*/
{
    QString productName, price, stock;
    int productId = productItem->productId();
    productName = productItem->getProductName();
    price = productItem->getPrice();
    stock = productItem->getStock();
    if(price.length()) {
        ProductItem* p = new ProductItem(productId, productName, price, stock);
        ui->o_productInfoTreeWidget->addTopLevelItem(p);
    }
}

void OrderManagerForm::o_showStockProduct(QString p_stock, ProductItem* productItem)  /*재고량으로 해당 상품의 정보를 전부 가져와 보여줌*/
{
    QString productName, price, stock;
    int productId = productItem->productId();
    productName = productItem->getProductName();
    price = productItem->getPrice();
    stock = productItem->getStock();

    if(stock.length()) {
        ProductItem* p = new ProductItem(productId, productName, price, stock);
        ui->o_productInfoTreeWidget->addTopLevelItem(p);
    }
}


void OrderManagerForm::on_o_productSearchPushButton_clicked()  //상품정보 조회 버튼을 누를 때
{

    ui->o_productInfoTreeWidget->clear();

    int index = ui->o_productSearchComboBox->currentIndex();  //어떤 콤보박스 카테고리가 선택되었는지 인덱스로 받아옴
    if(index == 0)
    {
     int p_id = ui->o_productSearchLineEdit->text().toInt();
     emit searchProduct(index, p_id);                            //id로 검색 할 때 signal로 id값을 보내줌
    }
    else
    {
       QString text = ui->o_productSearchLineEdit->text();
       emit searchProduct(index, text);                      //이름으로 검색 할 때 signal로 이름 값을 보내줌
    }
}


void OrderManagerForm::on_o_clientInfoTreeWidget_itemClicked(QTreeWidgetItem *item, int column) /*아이템 클릭시 lineEdit에 나타나도록*/
{
    Q_UNUSED(column);
    ui->clientNameLineEdit->setText(item->text(1));
    ui->phoneNumberLineEdit->setText(item->text(2));
    ui->addressLineEdit->setText(item->text(3));
}


void OrderManagerForm::on_o_productInfoTreeWidget_itemClicked(QTreeWidgetItem *item, int column) /*아이템 클릭시 lineEdit에 나타나도록*/
{
    Q_UNUSED(column);
    ui->orderQuantitySpinBox->setValue(0);
    ui->productNameLineEdit->setText(item->text(1));
    ui->totalPriceLineEdit->setText(item->text(2));
}


void OrderManagerForm::on_o_clientSearchLineEdit_returnPressed()    //enter를 눌렀을 때도 고객 조회가 되도록 구현
{

//    ui->o_clientInfoTreeWidget->clear();

//    int index = ui->o_clientSearchComboBox->currentIndex();  //어떤 콤보박스 카테고리가 선택되었는지 인덱스로 받아옴
//    if(index == 0)
//    {
//     int c_id = ui->o_clientSearchLineEdit->text().toInt();
//     emit o_searchIdClient(c_id);                            //id로 검색 할 때 signal로 id값을 보내줌
//    }
//    else if(index == 1)
//    {
//       QString c_name = ui->o_clientSearchLineEdit->text();
//       emit o_searchNameClient(c_name);                      //이름으로 검색 할 때 signal로 이름 값을 보내줌
//    }

//    else if(index == 2)
//    {
//       QString c_number = ui->o_clientSearchLineEdit->text();
//       emit o_searchNumberClient(c_number);                  //핸드폰번호로 검색 할 때 signal로 핸드폰번호 값을 보내줌
//    }

//    else if(index == 3)
//    {
//       QString c_address = ui->o_clientSearchLineEdit->text();
//       emit o_searchAddressClient(c_address);                //주소로 검색 할 때 signal로 주소 값을 보내줌
//    }

//    else if(index == 4)
//    {
//       QString c_email = ui->o_clientSearchLineEdit->text();
//       emit o_searchEmailClient(c_email);                    //email로 검색 할 때 signal로 email 값을 보내줌
//    }
}


void OrderManagerForm::on_o_productSearchLineEdit_returnPressed()   //enter를 눌렀을 때도 상품 조회가 되도록 구현
{

//    ui->o_clientInfoTreeWidget->clear();

//    int index = ui->o_clientSearchComboBox->currentIndex();  //어떤 콤보박스 카테고리가 선택되었는지 인덱스로 받아옴
//    if(index == 0)
//    {
//     int c_id = ui->o_clientSearchLineEdit->text().toInt();
//     emit o_searchIdClient(c_id);                            //id로 검색 할 때 signal로 id값을 보내줌
//    }
//    else if(index == 1)
//    {
//       QString c_name = ui->o_clientSearchLineEdit->text();
//       emit o_searchNameClient(c_name);                      //이름으로 검색 할 때 signal로 이름 값을 보내줌
//    }

//    else if(index == 2)
//    {
//       QString c_number = ui->o_clientSearchLineEdit->text();
//       emit o_searchNumberClient(c_number);                  //핸드폰번호로 검색 할 때 signal로 핸드폰번호 값을 보내줌
//    }

//    else if(index == 3)
//    {
//       QString c_address = ui->o_clientSearchLineEdit->text();
//       emit o_searchAddressClient(c_address);                //주소로 검색 할 때 signal로 주소 값을 보내줌
//    }

//    else if(index == 4)
//    {
//       QString c_email = ui->o_clientSearchLineEdit->text();
//       emit o_searchEmailClient(c_email);                    //email로 검색 할 때 signal로 email 값을 보내줌
//    }
}


void OrderManagerForm::on_orderSearchLineEdit_returnPressed()   //enter 눌렀을 때 주문조회 되도록
{
    ui->orderSearchTreeWidget_2->clear();                       //lineEdit에 남아있을 정보를 지움

    int i = ui->orderSearchComboBox->currentIndex();            //콤보박스 아이템을 인덱스로 받음
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->orderSearchTreeWidget->findItems(ui->orderSearchLineEdit->text(), flag, i);
        //주문조회입력칸에 있는 텍스트를 뽑아 treewidget에서 아이템을 찾음

    Q_FOREACH(auto i, items) {                              //해당 인덱스에 있는 item으로 foreact 돌아서
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
            ui->orderSearchTreeWidget_2->addTopLevelItem(item); //해당 정보들을 뽑아서 2_treewidget에 보여줌
        }
  }
    ui->orderSearchTreeWidget_2->setFocus();
}


void OrderManagerForm::on_orderQuantitySpinBox_valueChanged(int stock) //재고량의 스핀박스 값이 변할 때
{

    if (ui->o_productInfoTreeWidget->currentItem() == nullptr){       //트리위젯에 아이템이 없을 때 아이템을 클릭해도 죽지 않도록 처리
        void on_o_clientInfoTreeWidget_itemClicked();
    }
    else
    {
        int x = ui->orderQuantitySpinBox->text().toInt();
        int y = ui->o_productInfoTreeWidget->currentItem()->text(2).toInt();
        int totalPrice = x*y;
        ui->totalPriceLineEdit->setText(QString::number(totalPrice));           /*상품총합계 계산한 값이 계속 변해서 나타나도록*/
    }
    emit stockSearched(stock);                                                  //변하는 재고량을 signal 보내줌

}

void OrderManagerForm::on_orderClearPushButton_clicked()
{
    o_clearLineEdit();          //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록
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
    ui->orderQuantitySpinBox->setValue(0);   //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록 하는 함수 구현

}

