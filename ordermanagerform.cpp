 #include "ordermanagerform.h"
#include "ui_ordermanagerform.h"

#include <QFile>
#include <QMenu>
#include <QDateTime>
#include <QDateEdit>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTreeView>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlError>
#include <QStandardItemModel>

OrderManagerForm::OrderManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderManagerForm)
{
    ui->setupUi(this);                  // ui 파일이 만들어짐 (this) 현재 class에 ui 파일 올림

    QList<int> sizes;
    sizes << 400 << 500;
    ui->splitter->setSizes(sizes);      /*splitter 사이즈 조절*/

    QAction* removeAction = new QAction(tr("&Remove"));                 //삭제 액션 생성
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));     //액션 신호를 보낼 때 아이템 삭제

    menu = new QMenu;                                                           //메뉴 생성
    menu->addAction(removeAction);                                              //메뉴에 remove 액션 추가
    ui->orderSearchTreeView->setContextMenuPolicy(Qt::CustomContextMenu);       //(우클릭 메뉴)
    connect(ui->orderSearchTreeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));  //우클릭시 알림

    ui->o_clientInfoTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);    //삭제 우클릭 메뉴

    s_orderModel = new QStandardItemModel(0,8);                                 //search view를 위한 model 생성
    s_orderModel->setHeaderData(0, Qt::Horizontal, tr("OrderID"));              //id, date, clientName, number, address, productname, order Quantity 칼럼 생성
    s_orderModel->setHeaderData(1, Qt::Horizontal, tr("OrderDate"));
    s_orderModel->setHeaderData(2, Qt::Horizontal, tr("Client Name"));
    s_orderModel->setHeaderData(3, Qt::Horizontal, tr("PhoneNumber"));
    s_orderModel->setHeaderData(4, Qt::Horizontal, tr("Address"));
    s_orderModel->setHeaderData(5, Qt::Horizontal, tr("Product Name"));
    s_orderModel->setHeaderData(6, Qt::Horizontal, tr("Order Quantity"));
    s_orderModel->setHeaderData(7, Qt::Horizontal, tr("Total Price"));
    ui->orderSearchTreeView_2->setModel(s_orderModel);                           //treeview에 model set

}

void OrderManagerForm::loadData()                                                //저장된 파일 로드
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "orderConnection");   //SQLITE를 이용한 database 생성
    db.setDatabaseName("orderlist.db");                                          //database 이름 productlist.db
    if (db.open( )) {                                                            //예외처리
        QSqlQuery query(db);                                                     //query문을 이용해 table 생성
        query.exec("CREATE TABLE IF NOT EXISTS ordertable(\
                   OrderID INTEGER Primary Key,\
                   OrderDate VARCHAR(50),\
                   Client Name VARCHAR(30),\
                   PhoneNumber VARCHAR(20),\
                   Address VARCHAR(50),\
                   Product Name VARCHAR(50),\
                   Order Quantity VARCHAR(50),\
                   Total Price VARCHAR(50));");
        orderModel = new QSqlTableModel(this, db);
        orderModel->setTable("ordertable");
        orderModel->select();
        orderModel->setHeaderData(0, Qt::Horizontal, tr("OrderID"));
        orderModel->setHeaderData(1, Qt::Horizontal, tr("OrderDate"));
        orderModel->setHeaderData(2, Qt::Horizontal, tr("Client Name"));
        orderModel->setHeaderData(3, Qt::Horizontal, tr("PhoneNumber"));
        orderModel->setHeaderData(4, Qt::Horizontal, tr("Address"));
        orderModel->setHeaderData(5, Qt::Horizontal, tr("Product Name"));
        orderModel->setHeaderData(6, Qt::Horizontal, tr("Order Quantity"));
        orderModel->setHeaderData(7, Qt::Horizontal, tr("Total Price"));          //table header 생성
        ui->orderSearchTreeView->setModel(orderModel);
    }                               
}

OrderManagerForm::~OrderManagerForm()
{
    delete ui;                                                          //ui delete

    QSqlDatabase db = QSqlDatabase::database("orderConnection");        //db를 닫아줌
    if(db.isOpen()) {
        orderModel->submitAll();
        delete orderModel;
        db.commit();
        db.close();
    }
}

int OrderManagerForm::makeId( )                     //아이디 자동부여
{
    if(orderModel->rowCount() == 0) {               //model에 아무것도 없으면
        return 300;                                 //300부터 반환
    } else {
        auto orderId = orderModel->data(orderModel->index(orderModel->rowCount()-1, 0)).toInt();
        return ++orderId;                           //ordertModel의 rowcount로 마지막 id 뒷번호부터 부여
    }
}

void OrderManagerForm::removeItem()                                     //주문 아이템 삭제
{
    QModelIndex index = ui->orderSearchTreeView->currentIndex();

    if(index.isValid()) {
        orderModel->removeRow(index.row());                             //model에서 열을 지움
        orderModel->select();
    }
    o_clearLineEdit();                                                  //lineEdit에 남은 기록을 지움
}

void OrderManagerForm::showContextMenu(const QPoint &pos)               //마우스 우클릭 위치 알림
{
    QPoint globalPos = ui->orderSearchTreeView->mapToGlobal(pos);
    menu->exec(globalPos);
}


void OrderManagerForm::on_oderInputAddPushButton_clicked()                                              //주문 입력 버튼을 누를 때
{

        QString orderDate, clientName, phoneNumber, address, productName, orderQuantity, totalPrice;
        int orderId = makeId( );
        ui->orderIdLineEdit->setText(QString::number(orderId));//id 자동입력값 반환
        orderDate=currentDateTime();                                                                    //주문 날짜 및 시간 자동입력값 반환
        clientName = ui->clientNameLineEdit->text();
        phoneNumber = ui->phoneNumberLineEdit->text();
        address = ui->addressLineEdit->text();
        productName = ui->productNameLineEdit->text();                                                  /*lineEdit에 입력된 텍스트*/
        orderQuantity = ui->orderQuantitySpinBox->text();                                               //주문수량 spinbox로 뽑아옴

        if(ui->o_productInfoTreeWidget->currentItem() != nullptr) {

        int s = ui->o_productInfoTreeWidget->currentItem()->text(3).toInt();                            //상품 조회 treewidget에서 stock값을 뽑아서 spinbox 제한값 범위 지
        ui->orderQuantitySpinBox->setRange(1,s);                                                        //최소값 1 최대값 s (물품 재고량에 따라 달라짐)
        totalPrice = ui->totalPriceLineEdit->text();
        }
        //totalPrice spinbox 변화에 따른 값이 나타남

        QSqlDatabase db = QSqlDatabase::database("orderConnection");
        if(db.isOpen()&&clientName.length()&&phoneNumber.length()&&address.length()&& productName.length() ) {      //lineEdit이 비어있을 경우를 위한 예외처리
            QSqlQuery query(orderModel->database());
            query.prepare("INSERT INTO ordertable VALUES (?, ?, ?, ?, ?, ? ,?, ?)");
            query.bindValue(0, orderId);
            query.bindValue(1, orderDate);
            query.bindValue(2, clientName);
            query.bindValue(3, phoneNumber);
            query.bindValue(4, address);
            query.bindValue(5, productName);
            query.bindValue(6, orderQuantity);
            query.bindValue(7, totalPrice);                                                                           //order table에 입력됨
            query.exec();
            orderModel->select();
        }
        else
       {
            QMessageBox::critical(this, tr("Order Info"), \
                                  tr("There is information that has not been entered."));                                               //메세지 박스로 다시 입력하게 함
        }
        o_clearLineEdit();                                                                                                               //사용한 lineEdit 기록을 지움
}

void OrderManagerForm::on_orderInputModifyPushButton_clicked()              //수정 버튼 눌렀을 때
{
    QModelIndex index = ui->orderSearchTreeView->currentIndex();
    QString clientName, phoneNumber, address, productName, orderQuantity, totalPrice;
    clientName = ui->clientNameLineEdit->text();
    phoneNumber = ui->phoneNumberLineEdit->text();
    address = ui->addressLineEdit->text();
    productName = ui->productNameLineEdit->text();
    orderQuantity = ui->orderQuantitySpinBox->text();                   /*key 값을 통해 아이템의 정보들을 해당칸에 나타냄*/
    int x = ui->orderQuantitySpinBox->text().toInt();
     if(ui->o_productInfoTreeWidget->currentItem() != nullptr)
         {                                                              //spinbox 값 x
    int y = ui->o_productInfoTreeWidget->currentItem()->text(2).toInt();//상품 가격 y
    totalPrice = QString::number(x*y);                                  //totalPrice x*y
    ui->totalPriceLineEdit->setText(totalPrice);
    }                                                                   //계산한 값을 해당 lineEdit에 나타냄
    if(index.isValid()) {
        orderModel->setData(index.siblingAtColumn(2), clientName);
        orderModel->setData(index.siblingAtColumn(3), phoneNumber);
        orderModel->setData(index.siblingAtColumn(4), address);
        orderModel->setData(index.siblingAtColumn(5), productName);
        orderModel->setData(index.siblingAtColumn(6), orderQuantity);
        orderModel->setData(index.siblingAtColumn(7), totalPrice);      //order table에 입력됨
        orderModel->submit();
    }

    else
   {
        QMessageBox::critical(this, tr("Order Info"), \
                              tr("There is information that has not been entered."));  //메세지 박스로 lineEdit이 비어있음을 알림
    }
    orderModel->select();
}

void OrderManagerForm::on_orderSearchPushButton_clicked()       //주문 조회 버튼 클릭했을 때
{
    s_orderModel->clear();
    //ui->orderSearchTreeView_2->reset();                       //lineEdit에 남아있을 정보를 지움
    int i = ui->orderSearchComboBox->currentIndex();            //콤보박스 아이템을 인덱스로 받음
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    QModelIndexList indexes = orderModel->match(orderModel->index(0, i), Qt::EditRole, ui->orderSearchLineEdit->text(), -1, flag);
    //주문조회입력칸에 있는 텍스트를 뽑아 treewidget에서 아이템을 찾음

    foreach(auto ix, indexes) {                                                      //해당 인덱스에 있는 item으로 foreact 돌아서
            int orderId = orderModel->data(ix.siblingAtColumn(0)).toInt();
            QString orderDate = orderModel->data(ix.siblingAtColumn(1)).toString();
            QString clientName = orderModel->data(ix.siblingAtColumn(2)).toString();
            QString phoneNumber = orderModel->data(ix.siblingAtColumn(3)).toString();
            QString address = orderModel->data(ix.siblingAtColumn(4)).toString();
            QString productName = orderModel->data(ix.siblingAtColumn(5)).toString();
            QString orderQuantity =orderModel->data(ix.siblingAtColumn(6)).toString();
            QString totalPrice = orderModel->data(ix.siblingAtColumn(7)).toString();
            QStringList strings;
            strings << QString::number(orderId) << orderDate << clientName << phoneNumber <<address << productName <<orderQuantity <<totalPrice;

            QList<QStandardItem *> items;
            for (int i = 0; i < 8; ++i) {
                items.append(new QStandardItem(strings.at(i)));
            }
            s_orderModel->appendRow(items);
            s_orderModel->setHeaderData(0, Qt::Horizontal, tr("OrderID"));
            s_orderModel->setHeaderData(1, Qt::Horizontal, tr("OrderDate"));
            s_orderModel->setHeaderData(2, Qt::Horizontal, tr("Client Name"));
            s_orderModel->setHeaderData(3, Qt::Horizontal, tr("PhoneNumber"));
            s_orderModel->setHeaderData(4, Qt::Horizontal, tr("Address"));
            s_orderModel->setHeaderData(5, Qt::Horizontal, tr("Product Name"));
            s_orderModel->setHeaderData(6, Qt::Horizontal, tr("Order Quantity"));
            s_orderModel->setHeaderData(7, Qt::Horizontal, tr("Total Price"));          //table header 생성
    }
    ui->orderSearchTreeView_2->setFocus();
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


void OrderManagerForm::showClient(int c_id, QString clientName, QString phoneNumber, QString address, QString email)
{
    QTreeWidgetItem *clientItem = new QTreeWidgetItem(ui->o_clientInfoTreeWidget);                                      //client로부터 받아온 정보를 treewidget에 보여줌

    if(QString::number(c_id).length()) {
    clientItem->setText(0, QString::number(c_id));
    clientItem->setText(1, clientName);
    clientItem->setText(2, phoneNumber);
    clientItem->setText(3, address);
    clientItem->setText(4, email);
    ui->o_clientInfoTreeWidget->addTopLevelItem(clientItem);

    }
}

void OrderManagerForm::showProduct(int p_id, QString productName, QString price, QString stock)
{
    QTreeWidgetItem *productItem = new QTreeWidgetItem(ui->o_productInfoTreeWidget);    //product로부터 받아온 정보를 treewidget에 보여줌

    if(QString::number(p_id).length()) {
    productItem->setText(0, QString::number(p_id));
    productItem->setText(1, productName);
    productItem->setText(2, price);
    productItem->setText(3, stock);
    ui->o_productInfoTreeWidget->addTopLevelItem(productItem);
    }
}



void OrderManagerForm::on_o_clientSearchPushButton_clicked() //고객정보 조회 버튼을 누를 때
{
   ui->o_clientInfoTreeWidget->clear();

   int index = ui->o_clientSearchComboBox->currentIndex();   //어떤 콤보박스 카테고리가 선택되었는지 인덱스로 받아옴
   if(index == 0)
   {
    int c_id = ui->o_clientSearchLineEdit->text().toInt();
    emit searchClient(index, c_id);                          //id로 검색 할 때 signal로 id값을 보내줌
   }
   else
   {
      QString text = ui->o_clientSearchLineEdit->text();
      emit searchClient(index, text);                        //이름으로 검색 할 때 signal로 이름 값을 보내줌
   }
}


void OrderManagerForm::on_o_productSearchPushButton_clicked()  //상품정보 조회 버튼을 누를 때
{

    ui->o_productInfoTreeWidget->clear();

    int index = ui->o_productSearchComboBox->currentIndex();   //어떤 콤보박스 카테고리가 선택되었는지 인덱스로 받아옴
    if(index == 0)
    {
     int p_id = ui->o_productSearchLineEdit->text().toInt();
     emit searchProduct(index, p_id);                          //id로 검색 할 때 signal로 id값을 보내줌
    }
    else
    {
       QString text = ui->o_productSearchLineEdit->text();
       emit searchProduct(index, text);                       //이름으로 검색 할 때 signal로 이름 값을 보내줌
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



void OrderManagerForm::on_o_productSearchLineEdit_returnPressed()   //enter를 눌렀을 때도 상품 조회가 되도록 구현
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


void OrderManagerForm::on_orderSearchLineEdit_returnPressed()   //enter 눌렀을 때 주문조회 되도록
{
    s_orderModel->clear();
    //ui->orderSearchTreeView_2->reset();                       //lineEdit에 남아있을 정보를 지움
    int i = ui->orderSearchComboBox->currentIndex();            //콤보박스 아이템을 인덱스로 받음
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    QModelIndexList indexes = orderModel->match(orderModel->index(0, i), Qt::EditRole, ui->orderSearchLineEdit->text(), -1, flag);
      //주문조회입력칸에 있는 텍스트를 뽑아 treewidget에서 아이템을 찾음

    foreach(auto ix, indexes) {                                                     //해당 인덱스에 있는 item으로 foreacth 돌아서
            int orderId = orderModel->data(ix.siblingAtColumn(0)).toInt();
            QString orderDate = orderModel->data(ix.siblingAtColumn(1)).toString();
            QString clientName = orderModel->data(ix.siblingAtColumn(2)).toString();
            QString phoneNumber = orderModel->data(ix.siblingAtColumn(3)).toString();
            QString address = orderModel->data(ix.siblingAtColumn(4)).toString();
            QString productName = orderModel->data(ix.siblingAtColumn(5)).toString();
            QString orderQuantity =orderModel->data(ix.siblingAtColumn(6)).toString();
            QString totalPrice = orderModel->data(ix.siblingAtColumn(7)).toString();        //칼럼 위치로 해당 데이터를 뽑음
            QStringList strings;
            strings << QString::number(orderId) << orderDate << clientName << phoneNumber <<address << productName <<orderQuantity <<totalPrice;

            QList<QStandardItem *> items;
            for (int i = 0; i < 8; ++i) {
                items.append(new QStandardItem(strings.at(i)));
            }
            s_orderModel->appendRow(items);
            s_orderModel->setHeaderData(0, Qt::Horizontal, tr("OrderID"));
            s_orderModel->setHeaderData(1, Qt::Horizontal, tr("OrderDate"));
            s_orderModel->setHeaderData(2, Qt::Horizontal, tr("Client Name"));
            s_orderModel->setHeaderData(3, Qt::Horizontal, tr("PhoneNumber"));
            s_orderModel->setHeaderData(4, Qt::Horizontal, tr("Address"));
            s_orderModel->setHeaderData(5, Qt::Horizontal, tr("Product Name"));
            s_orderModel->setHeaderData(6, Qt::Horizontal, tr("Order Quantity"));
            s_orderModel->setHeaderData(7, Qt::Horizontal, tr("Total Price"));              //header 설정
    }

    ui->orderSearchTreeView_2->setFocus();
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


void OrderManagerForm::on_orderSearchTreeView_clicked(const QModelIndex &index)
{
    QString orderId = orderModel->data(index.siblingAtColumn(0)).toString();
    QString orderDate = orderModel->data(index.siblingAtColumn(1)).toString();
    QString clientName = orderModel->data(index.siblingAtColumn(2)).toString();
    QString phoneNumber = orderModel->data(index.siblingAtColumn(3)).toString();
    QString address = orderModel->data(index.siblingAtColumn(4)).toString();
    QString productName = orderModel->data(index.siblingAtColumn(5)).toString();
    QString orderQuantity =orderModel->data(index.siblingAtColumn(6)).toString();
    QString totalPrice = orderModel->data(index.siblingAtColumn(7)).toString();

    ui->orderIdLineEdit->setText(orderId);
    ui->orderDateLineEdit->setText(orderDate);
    ui->clientNameLineEdit->setText(clientName);
    ui->phoneNumberLineEdit->setText(phoneNumber);
    ui->addressLineEdit->setText(address);
    ui->productNameLineEdit->setText(productName);
    ui->orderQuantitySpinBox->setValue(orderQuantity.toInt());                   /*key 값을 통해 아이템의 정보들을 해당칸에 나타냄*/
    ui->totalPriceLineEdit->setText(totalPrice);
    //ui->toolBox->setCurrentIndex(0);
}

