#include "productmanagerform.h"
#include "ui_productmanagerform.h"
#include "productitem.h"

#include <QFile>
#include <QMenu>
#include <QMessageBox>

ProductManagerForm::ProductManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductManagerForm)
{
    ui->setupUi(this);      // ui 파일이 만들어짐 (this) 현재 class에 ui 파일 올림

    QList<int> sizes;
    sizes << 300 << 400;
    ui->splitter->setSizes(sizes);        /*splitter 사이즈 조절*/

    QAction* removeAction = new QAction(tr("&Remove"));                  //삭제 액션 생성
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));      //액션 신호를 보낼 때 아이템 삭제

    menu = new QMenu;                                                //메뉴 생성
    menu->addAction(removeAction);                                   //메뉴에 remove 액션 추가
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);     //(우클릭 메뉴)
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
}

void ProductManagerForm::loadData()                                             //저장된 파일 로드
{
    QFile file("productlist.txt");                                              //지정된 이름 파일을 열 때 오류 검사
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))                      //오류 발생시 return;
        return;

    QTextStream in(&file);                                                      //오류 발생하지 않으면 clientlist.txt 불러옴
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");                                  // , 을 기준으로 나눠서 row 0~7에 item 저장
        if(row.size()) {
            int productId = row[0].toInt();
            ProductItem* p = new ProductItem(productId, row[1], row[2], row[3]);
            ui->treeWidget->addTopLevelItem(p);                                 //저장한 순서로 treewidget에 나타내줌
            productList.insert(productId, p);
        }
    }
    file.close( );                                                               //파일 열었으니 닫음
}

ProductManagerForm::~ProductManagerForm()
{
    delete ui;

    QFile file("productlist.txt");                                   //데이터 파일을 만들어서 내보냄
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))          //오류 발생시 return;
        return;

    QTextStream out(&file);                                          //오류 발생하지 않으면 clientlist.txt 불러옴
    for (const auto& v : productList) {
        ProductItem *p = v;
        out << p->productId() << ", " <<p->getProductName() << ", "; // , 을 기준으로 나눠서 row 0~7에 item 저장
        out << p->getPrice() << ", ";
        out << p->getStock() << "\n";//ProductItem.key(p)
    }
    file.close( );                                                   //파일 열었으니 닫음
}

int ProductManagerForm::makeId( )                  //아이디 자동부여
{
    if(productList.size( ) == 0) {                 //list에 아무것도 없으면
        return 200;                                //200부터 반환
    } else {
        auto productId = productList.lastKey();    //list에 목록이 있으면 마지막 키를 기준으로
        return ++productId;                        //그 뒷번호부터 반환
    }
}

void ProductManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();                      //상품 정보 아이템 삭제
    if(item != nullptr) {                                                       //아이템이 없으면
        productList.remove(item->text(0).toInt());                              //0번째 (id)를 int 값으로 변환해서
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
        ui->treeWidget->update();
    }
    p_clearLineEdit();    //lineEdit에 남은 기록을 지움
}

void ProductManagerForm::showContextMenu(const QPoint &pos)      //마우스 우클릭 위치 알림
{
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ProductManagerForm::on_addPushButton_clicked()             //상품정보 입력 버튼 누를 때
{
    QString productName, price, stock;
    int productId = makeId( );                                  //id 자동입력값 반환
    productName = ui->productNameLineEdit->text();
    price = ui->priceLineEdit->text();
    stock=ui->stockLineEdit->text();                            /*lineEdit에 입력된 텍스트*/


    if(productName.length() && price.length() && stock.length()) {              //비어있는 값이 있으면
        ProductItem* p = new ProductItem(productId, productName, price, stock);
        productList.insert(productId, p);
        ui->treeWidget->addTopLevelItem(p);
    }   
    else
    {
        QMessageBox::critical(this, tr("Product Info"),                                 //메세지 박스로 다시 입력하게 함
                              tr("There is information that has not been entered."));   //사용한 lineEdit 기록을 지움
    }

    for(int i = 0; i < ui->treeWidget->columnCount(); i++)   /* 컨텐츠의 길이로 QTreeWidget의 헤더의 크기를 고정 */
        ui->treeWidget->resizeColumnToContents(i);

    p_clearLineEdit();      //사용한 lineEdit 기록을 지움
}


void ProductManagerForm::on_modifyPushButton_clicked()                //수정 버튼 눌렀을 때
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();            //treewidget에서 현재 아이템
    if(item != nullptr) {                                             //선택한 아이템이 있을 때
        int key = item->text(0).toInt();                              //item의 0번쨰 텍스트를 int형 key값으로 뽑아옴
        ProductItem* p = productList[key];
        QString productName, price, stock;
        productName = ui->productNameLineEdit->text();
        price = ui->priceLineEdit->text();
        stock = ui->stockLineEdit->text();                            /*key 값을 통해 아이템의 정보들을 해당칸에 나타냄*/
        p->setProductName(productName);
        p->setPrice(price);
        p->setStock(stock);
        productList[key] = p;                                          /*해당 정보들을 clientList에 담음*/
    }  
}


void ProductManagerForm::on_searchPushButton_clicked()           //상품 조회 버튼 클릭했을 때
{
    ui->searchTreeWidget->clear();                               //lineEdit에 남아있을 정보를 지움

    int i = ui->searchComboBox->currentIndex();                  //콤보박스 아이템을 인덱스로 받음
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), flag, i);
        //고객조회입력칸에 있는 텍스트를 뽑아 treewidget에서 아이템을 찾음

        foreach(auto i, items) {                                //해당 인덱스에 있는 item으로 foreach 돌아서
            ProductItem* p = static_cast<ProductItem*>(i);
            int productId = p->productId();
            QString name = p->getProductName();
            QString price = p->getPrice();
            QString stock = p->getStock();
            ProductItem* item = new ProductItem(productId, name, price, stock);
            ui->searchTreeWidget->addTopLevelItem(item);         //해당 정보들을 뽑아서 treewidget에 보여줌
        }
    }
}


void ProductManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->productIdLineEdit->setText(item->text(0));
    ui->productNameLineEdit->setText(item->text(1));
    ui->priceLineEdit->setText(item->text(2));
    ui->stockLineEdit->setText(item->text(3));
    ui->toolBox->setCurrentIndex(0);             /*treeWidget 아이템 클릭시 각 해당칸에 정보 나타남*/
}

void ProductManagerForm::p_findIdProduct(int p_id)
{
    auto items = ui->treeWidget->findItems(QString::number(p_id), Qt::MatchContains|Qt::MatchCaseSensitive, 0);

    foreach(auto i, items) {
        ProductItem* p = static_cast<ProductItem*>(i);
        int productId = p->productId();
        QString productName = p->getProductName();
        QString price = p->getPrice();
        QString stock = p->getStock();
        ProductItem* item = new ProductItem(productId, productName, price, stock);

        emit p_sendIdProduct(p_id, item);     //order에서 정보를 찾아달라는 signal을 보내면 product 정보를 찾아서 찾았다는 signal을 보내준다 (id값)
    }

}

void ProductManagerForm::p_findNameProduct(QString p_name)
{
    auto items = ui->treeWidget->findItems(p_name, Qt::MatchContains|Qt::MatchCaseSensitive, 1);

    foreach(auto i, items) {
        ProductItem* p = static_cast<ProductItem*>(i);
        int productId = p->productId();
        QString productName = p->getProductName();
        QString price = p->getPrice();
        QString stock = p->getStock();
        ProductItem* item = new ProductItem(productId, productName, price, stock);

        emit p_sendNameProduct(p_name, item);  //order에서 정보를 찾아달라는 signal을 보내면 product 정보를 찾아서 찾았다는 signal을 보내준다 (name 값)
    }

}

void ProductManagerForm::p_findPriceProduct(QString p_price)
{
    auto items = ui->treeWidget->findItems(p_price, Qt::MatchContains|Qt::MatchCaseSensitive, 2);

    foreach(auto i, items) {
        ProductItem* p = static_cast<ProductItem*>(i);
        int productId = p->productId();
        QString productName = p->getProductName();
        QString price = p->getPrice();
        QString stock = p->getStock();
        ProductItem* item = new ProductItem(productId, productName, price, stock);

        emit p_sendPriceProduct(p_price, item);     //order에서 정보를 찾아달라는 signal을 보내면 product 정보를 찾아서 찾았다는 signal을 보내준다 (price 값)
    }

}

void ProductManagerForm::p_findStockProduct(QString p_stock)
{
    auto items = ui->treeWidget->findItems(p_stock, Qt::MatchContains|Qt::MatchCaseSensitive, 3);

    foreach(auto i, items) {
        ProductItem* p = static_cast<ProductItem*>(i);
        int productId = p->productId();
        QString productName = p->getProductName();
        QString price = p->getPrice();
        QString stock = p->getStock();
        ProductItem* item = new ProductItem(productId, productName, price, stock);

        emit p_sendStockProduct(p_stock, item);     //order에서 정보를 찾아달라는 signal을 보내면 product 정보를 찾아서 찾았다는 signal을 보내준다 (stock 값)
    }

}



void ProductManagerForm::stockFinded(int stock)
{
    auto items = ui->treeWidget->findItems(QString::number(stock), Qt::MatchContains|Qt::MatchCaseSensitive, 0);


    foreach(auto i, items) {
        ProductItem* p = static_cast<ProductItem*>(i);
        int productId = p->productId();
        QString productName = p->getProductName();
        QString price = p->getPrice();
        QString stock = p->getStock();
        ProductItem* item = new ProductItem(productId, productName, price, stock);

        emit stockSended(stock.toInt());            //order에서 spinbox 값을 제한 할 때 찾아서 siganl 보내줌
    }

}


void ProductManagerForm::on_clearPushButton_clicked()
{
    p_clearLineEdit();                       //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록

}

void ProductManagerForm::p_clearLineEdit()
{
    ui->productIdLineEdit->clear();
    ui->productNameLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->stockLineEdit->clear();               //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록 하는 함수 구현
}
