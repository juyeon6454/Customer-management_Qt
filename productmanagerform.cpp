#include "productmanagerform.h"
#include "ui_productmanagerform.h"

#include <QFile>
#include <QMenu>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTreeView>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QStandardItemModel>

ProductManagerForm::ProductManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductManagerForm)
{
    ui->setupUi(this);      // ui 파일이 만들어짐 (this) 현재 class에 ui 파일 올림

    QList<int> sizes;
    sizes << 300 << 400;
    ui->splitter->setSizes(sizes);                                       /*splitter 사이즈 조절*/

    QAction* removeAction = new QAction(tr("&Remove"));                  //삭제 액션 생성
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));      //액션 신호를 보낼 때 아이템 삭제

    menu = new QMenu;                                                   //메뉴 생성
    menu->addAction(removeAction);                                      //메뉴에 remove 액션 추가
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);          //(우클릭 메뉴)

    connect(ui->treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint))); //우클릭시 알림
    connect(ui->searchLineEdit, SIGNAL(returnPressed()), this, SLOT(on_searchPushButton_clicked()));        //search enter 누를 시 pushbutton 클릭

    s_productModel = new QStandardItemModel(0,4);                            //search view를 위한 model 생성
    s_productModel->setHeaderData(0, Qt::Horizontal, tr("ID"));              //id, name, phonenumber, address, email 칼럼 생성
    s_productModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    s_productModel->setHeaderData(2, Qt::Horizontal, tr("Price"));
    s_productModel->setHeaderData(3, Qt::Horizontal, tr("Stock"));
    ui->searchTreeView->setModel(s_productModel);                            //treeview에 model set
}

void ProductManagerForm::loadData()                                                  //저장된 파일 로드
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "productConnection");     //SQLITE를 이용한 database 생성
    db.setDatabaseName("productlist.db");                                            //database 이름 productlist.db
    if (db.open( )) {                                                                //예외처리
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS product(id INTEGER Primary Key, name VARCHAR(30) NOT NULL, price VARCHAR(20) NOT NULL, stock VARCHAR(50));");
        productModel = new QSqlTableModel(this, db);
        productModel->setTable("product");                                           //query문을 이용해 table 생성
        productModel->select();
        productModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        productModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        productModel->setHeaderData(2, Qt::Horizontal, tr("Price"));
        productModel->setHeaderData(3, Qt::Horizontal, tr("Stock"));                 //table header 생성
        ui->treeView->setModel(productModel);
    }
}

ProductManagerForm::~ProductManagerForm()
{
    delete ui;

    QSqlDatabase db = QSqlDatabase::database("productConnection");                    //db를 닫아줌
    if(db.isOpen()) {
        productModel->submitAll();
        delete productModel;
        db.commit();
        db.close();
    }
}

int ProductManagerForm::makeId( )                      //아이디 자동부여
{
    if(productModel->rowCount() == 0) {               //model에 아무것도 없으면
        return 200;                                   //200부터 반환
    } else {
        auto productId = productModel->data(productModel->index(productModel->rowCount()-1, 0)).toInt();
        return ++productId;                           //productModel의 rowcount로 마지막 id 뒷번호부터 부여
    }
}

void ProductManagerForm::removeItem()                            //Product remove
{
    QModelIndex index = ui->treeView->currentIndex();
    int delid = index.sibling(index.row(), 0).data().toInt();   //treewidget에서 현재  item을 인덱스와 row로 뽑아냄
    int row = index.row();                                      //sever productlist에 보내기 위한 signal 인자

    if(index.isValid()) {
        productModel->removeRow(index.row());                   //model에서 열을 지움
        productModel->select();
    }
    emit productRemoved (delid, QString::number(row));          //sever clientlist로 signal 보냄
    p_clearLineEdit();                                          //lineEdit에 남은 기록을 지움
}

void ProductManagerForm::showContextMenu(const QPoint &pos)      //마우스 우클릭 위치 알림
{
    QPoint globalPos = ui->treeView->mapToGlobal(pos);
    if(ui->treeView->indexAt(pos).isValid())
    menu->exec(globalPos);
}

void ProductManagerForm::on_addPushButton_clicked()             //상품정보 입력 버튼 누를 때
{
    QString productName, price, stock;
    int productId = makeId( );
    ui->productIdLineEdit->setText(QString::number(productId)); //id 자동입력값 반환
    productName = ui->productNameLineEdit->text();
    price = ui->priceLineEdit->text();
    stock=ui->stockLineEdit->text();                            /*lineEdit에 입력된 텍스트*/


    QSqlDatabase db = QSqlDatabase::database("productConnection");
    if(db.isOpen() && productName.length() && price.length() && stock.length()) {       //lineEdit이 비어있을 경우를 위한 예외처리
        QSqlQuery query(productModel->database());
        query.prepare("INSERT INTO product VALUES (?, ?, ?, ?)");
        query.bindValue(0, productId);
        query.bindValue(1, productName);
        query.bindValue(2, price);
        query.bindValue(3, stock);                                                       //Product table에 입력됨
        query.exec();
    }
    else
    {
        QMessageBox::critical(this, tr("Product Info"),                                   //메세지 박스로 다시 입력하게 함
                              tr("There is information that has not been entered."));
    }
    productModel->select();

    p_clearLineEdit();                                                                    //사용한 lineEdit 기록을 지움
}


void ProductManagerForm::on_modifyPushButton_clicked()                //수정 버튼 눌렀을 때
{   
    QModelIndex index = ui->treeView->currentIndex();
    int molid = index.sibling(index.row(), 0).data().toInt();        //수정되었을 때 server의 productList가 같이 수정되도록 변수 설정
    int row = index.row();

    QString productName, price, stock;
    productName = ui->productNameLineEdit->text();
    price = ui->priceLineEdit->text();
    stock = ui->stockLineEdit->text();                               //lineEdit에 있는 text

    if(index.isValid()&& productName.length() && price.length() && stock.length()) {
        productModel->setData(index.siblingAtColumn(1), productName);
        productModel->setData(index.siblingAtColumn(2), price);
        productModel->setData(index.siblingAtColumn(3), stock);      //productModel에 데이터가 입력되도록
        productModel->submit();
        productModel->select();
    } 
    else
    {
        QMessageBox::critical(this, tr("Product Info"),                                   //메세지 박스로 다시 입력하게 함
                              tr("There is information that has not been entered."));
    }
       emit productModified (molid, row, productName);
}


void ProductManagerForm::on_searchPushButton_clicked()           //상품 조회 버튼 클릭했을 때
{

    s_productModel->clear();                                    //lineEdit에 남아있을 정보를 지움
    int i = ui->searchComboBox->currentIndex();                 //콤보박스 아이템을 인덱스로 받음
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;                    //데이터를 찾을 때 해당 단어가 있으면 찾아주도록 하는 속성

    QModelIndexList indexes = productModel->match(productModel->index(0, i), Qt::EditRole, ui->searchLineEdit->text(), -1, flag);

    foreach(auto ix, indexes) {
        int productId = productModel->data(ix.siblingAtColumn(0)).toInt(); //c->id();
        QString productName = productModel->data(ix.siblingAtColumn(1)).toString();
        QString price = productModel->data(ix.siblingAtColumn(2)).toString();
        QString stock = productModel->data(ix.siblingAtColumn(3)).toString();            //model에 있는 data에서 해당 칼럼의 있는 값들을 가져옴;
        QStringList strings;
        strings << QString::number(productId) << productName << price << stock ;         //string에 해당 값들을 넣어줌

    QList<QStandardItem *> items;
    for (int i = 0; i < 4; ++i) {
        items.append(new QStandardItem(strings.at(i)));
    }                                                                                    //for문을 돌면서 standardItem에 item을 append 해줌
    s_productModel->appendRow(items);
    s_productModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    s_productModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
    s_productModel->setHeaderData(2, Qt::Horizontal, tr("Price"));
    s_productModel->setHeaderData(3, Qt::Horizontal, tr("Stock"));                       //생성된 모델에 대한 header 명을 입력

    }
}


void ProductManagerForm::on_clearPushButton_clicked()
{
    p_clearLineEdit();                                      //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록
}

void ProductManagerForm::stockFinded(int stock)             //order에 spinbox 제한값을 위한 함수
{
    QModelIndexList indexes = productModel->match(productModel->index(0, 3), Qt::EditRole, stock, -1,  Qt::MatchContains);

    foreach(auto index, indexes) {
        int p_id = productModel->data(index.siblingAtColumn(0)).toInt();
        QString productName = productModel->data(index.siblingAtColumn(1)).toString();
        QString price = productModel->data(index.siblingAtColumn(2)).toString();
        QString stock = productModel->data(index.siblingAtColumn(3)).toString();    //index 값을 가져와 해당 제품의 재고량을 찾음
        emit stockSended(stock.toInt());                    //찾은 값을 order의 showproduct 함수로 보내는 signal
        }
}


void ProductManagerForm::on_treeView_clicked(const QModelIndex &index)
{
    QString productId = productModel->data(index.siblingAtColumn(0)).toString();
    QString productName = productModel->data(index.siblingAtColumn(1)).toString();
    QString price = productModel->data(index.siblingAtColumn(2)).toString();
    QString stock = productModel->data(index.siblingAtColumn(3)).toString();

    ui->productIdLineEdit->setText(productId);
    ui->productNameLineEdit->setText(productName);
    ui->priceLineEdit->setText(price);
    ui->stockLineEdit->setText(stock);
    ui->toolBox->setCurrentIndex(0);
}

void ProductManagerForm::findProduct(int index, int p_id)                 //order의 productTreewidget combobox의 index가 id일 때 (int)
{
//    auto flag = (index)? Qt::MatchCaseSensitive|Qt::MatchContains
//                        : Qt::MatchContains;//casecontains는 대소문자 구분
    QModelIndexList indexes = productModel->match(productModel->index(0, 0), Qt::EditRole, p_id, -1,  Qt::MatchContains);

    foreach(auto index, indexes) {
        int p_id = productModel->data(index.siblingAtColumn(0)).toInt();
        QString productName = productModel->data(index.siblingAtColumn(1)).toString();
        QString price = productModel->data(index.siblingAtColumn(2)).toString();
        QString stock = productModel->data(index.siblingAtColumn(3)).toString();         //sibling을 이용해 client 정보를 찾아냄
        emit sendProduct(p_id, productName, price, stock);
        }
}

void ProductManagerForm::findProduct(int index, QString text)          //order의 productTreewidget combobox의 index가 id 외 name, price, stock (string)
{
    if(index == 1)
    {
    QModelIndexList indexes = productModel->match(productModel->index(0, 1), Qt::EditRole, text, -1, Qt::MatchContains);

    foreach(auto index, indexes) {
        int p_id = productModel->data(index.siblingAtColumn(0)).toInt();
        QString productName = productModel->data(index.siblingAtColumn(1)).toString();
        QString price = productModel->data(index.siblingAtColumn(2)).toString();
        QString stock = productModel->data(index.siblingAtColumn(3)).toString();
        emit sendProduct(p_id, productName, price, stock);
        }
    }

    else if(index == 2)
    {

    QModelIndexList indexes = productModel->match(productModel->index(0, 2), Qt::EditRole, text, -1,Qt::MatchContains);

    foreach(auto index, indexes) {
        int p_id = productModel->data(index.siblingAtColumn(0)).toInt();
        QString productName = productModel->data(index.siblingAtColumn(1)).toString();
        QString price = productModel->data(index.siblingAtColumn(2)).toString();
        QString stock = productModel->data(index.siblingAtColumn(3)).toString();
        emit sendProduct(p_id, productName, price, stock);
        }
    }
    else if(index == 3)
    {
    QModelIndexList indexes = productModel->match(productModel->index(0, 3), Qt::EditRole, text, -1, Qt::MatchContains);

    foreach(auto index, indexes) {
        int p_id = productModel->data(index.siblingAtColumn(0)).toInt();
        QString productName = productModel->data(index.siblingAtColumn(1)).toString();
        QString price = productModel->data(index.siblingAtColumn(2)).toString();
        QString stock = productModel->data(index.siblingAtColumn(3)).toString();
        emit sendProduct(p_id, productName, price, stock);
        }
    }
}

void ProductManagerForm::p_clearLineEdit()
{
    ui->productIdLineEdit->clear();
    ui->productNameLineEdit->clear();
    ui->priceLineEdit->clear();
    ui->stockLineEdit->clear();               //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록 하는 함수 구현
}
