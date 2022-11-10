#include "productmanagerform.h"
#include "ui_productmanagerform.h"
//#include "productitem.h"

#include <QFile>
#include <QMenu>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTreeView>
#include <QSqlDatabase>
#include <QSqlRecord>

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
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);     //(우클릭 메뉴)

    connect(ui->treeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui->searchLineEdit, SIGNAL(returnPressed()), this, SLOT(on_searchPushButton_clicked()));
}

void ProductManagerForm::loadData()                                             //저장된 파일 로드
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "productConnection");
    db.setDatabaseName("productlist.db");
    if (db.open( )) {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS product(id INTEGER Primary Key, name VARCHAR(30) NOT NULL, price VARCHAR(20) NOT NULL, stock VARCHAR(50));");
        productModel = new QSqlTableModel(this, db);
        productModel->setTable("product");
        productModel->select();
        productModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        productModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        productModel->setHeaderData(2, Qt::Horizontal, tr("Price"));
        productModel->setHeaderData(3, Qt::Horizontal, tr("Stock"));
        ui->treeView->setModel(productModel);
    }

/*    for(int i = 0; i < productModel->rowCount(); i++) {
        int productId = productModel->data(productModel->index(i, 0)).toInt();
        QString productName = productModel->data(productModel->index(i, 1)).toString();

    }    */                                                       //파일 열었으니 닫음
}

ProductManagerForm::~ProductManagerForm()
{
    delete ui;

    QSqlDatabase db = QSqlDatabase::database("productConnection");
    if(db.isOpen()) {
        productModel->submitAll();
        delete productModel;
        db.commit();
        db.close();
    }                                                //파일 열었으니 닫음
}

int ProductManagerForm::makeId( )                  //아이디 자동부여
{
    if(productModel->rowCount() == 0) {               //model에 아무것도 없으면
        return 200;                                  //100부터 반환
    } else {
        auto productId = productModel->data(productModel->index(productModel->rowCount()-1, 0)).toInt();
        return ++productId;
    }
}

void ProductManagerForm::removeItem()
{
    QModelIndex index = ui->treeView->currentIndex();
    int delid = index.sibling(index.row(), 0).data().toInt();

    int row = index.row();
    if(index.isValid()) {
        productModel->removeRow(index.row());
        productModel->select();
        //ui->treeView->resizeColumnsToContents();
    }
    emit productRemoved (delid, QString::number(row));
    p_clearLineEdit();    //lineEdit에 남은 기록을 지움
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
    ui->productIdLineEdit->setText(QString::number(productId));//id 자동입력값 반환
    productName = ui->productNameLineEdit->text();
    price = ui->priceLineEdit->text();
    stock=ui->stockLineEdit->text();                            /*lineEdit에 입력된 텍스트*/


    QSqlDatabase db = QSqlDatabase::database("productConnection");
    if(db.isOpen() && productName.length() && price.length() && stock.length()) {
        QSqlQuery query(productModel->database());
        query.prepare("INSERT INTO product VALUES (?, ?, ?, ?)");
        query.bindValue(0, productId);
        query.bindValue(1, productName);
        query.bindValue(2, price);
        query.bindValue(3, stock);
        query.exec();
    }
    else
    {
        QMessageBox::critical(this, tr("Product Info"),                                   //메세지 박스로 다시 입력하게 함
                              tr("There is information that has not been entered."));
    }
    productModel->select();

    p_clearLineEdit();      //사용한 lineEdit 기록을 지움
}


void ProductManagerForm::on_modifyPushButton_clicked()                //수정 버튼 눌렀을 때
{   
    QModelIndex index = ui->treeView->currentIndex();
    int molid = index.sibling(index.row(), 0).data().toInt();

    QString productName, price, stock;
    productName = ui->productNameLineEdit->text();
    price = ui->priceLineEdit->text();
    stock = ui->stockLineEdit->text();

    int row = index.row();
    if(index.isValid()) {
//        int id = clientModel->data(index.siblingAtColumn(0)).toInt();
#if 1
//        clientModel->setData(index.siblingAtColumn(0), id);
        productModel->setData(index.siblingAtColumn(1), productName);
        productModel->setData(index.siblingAtColumn(2), price);
        productModel->setData(index.siblingAtColumn(3), stock);
        productModel->submit();
#else
        QSqlQuery query(productModel->database());
        query.prepare("UPDATE product SET productName = ?, price = ?, stock = ?, WHERE id = ?");
        query.bindValue(0, productName);
        query.bindValue(1, price);
        query.bindValue(2, stock);
        query.bindValue(3, id);
        query.exec();
#endif
        productModel->select();
        //ui->treeView->resizeColumnsToContents();
    }
       emit productModified (molid, row, productName);
}


void ProductManagerForm::on_searchPushButton_clicked()           //상품 조회 버튼 클릭했을 때
{
    ui->searchTreeWidget->clear();                              //lineEdit에 남아있을 정보를 지움

    int i = ui->searchComboBox->currentIndex();                 //콤보박스 아이템을 인덱스로 받음
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    QModelIndexList indexes = productModel->match(productModel->index(0, i), Qt::EditRole, ui->searchLineEdit->text(), -1, Qt::MatchFlags(flag));

    foreach(auto ix, indexes) {
        int productId = productModel->data(ix.siblingAtColumn(0)).toInt(); //c->id();
        QString productName = productModel->data(ix.siblingAtColumn(1)).toString();
        QString price = productModel->data(ix.siblingAtColumn(2)).toString();
        QString stock = productModel->data(ix.siblingAtColumn(3)).toString();
        QStringList strings;
        strings << QString::number(productId) << productName << price << stock ;
        new QTreeWidgetItem(ui->searchTreeWidget, strings);
        for(int i = 0; i < ui->searchTreeWidget->columnCount(); i++)
            ui->searchTreeWidget->resizeColumnToContents(i);
    }
}


void ProductManagerForm::on_clearPushButton_clicked()
{
    p_clearLineEdit();                       //clear 버튼을 눌렀을 때 lineEdit 기록이 지워지도록
}

void ProductManagerForm::stockFinded(int stock)
{
//    auto items = ui->treeWidget->findItems(QString::number(stock), Qt::MatchContains|Qt::MatchCaseSensitive, 0);


//    foreach(auto i, items) {
//        ProductItem* p = static_cast<ProductItem*>(i);
//        int productId = p->productId();
//        QString productName = p->getProductName();
//        QString price = p->getPrice();
//        QString stock = p->getStock();
//        ProductItem* item = new ProductItem(productId, productName, price, stock);

//        emit stockSended(stock.toInt());            //order에서 spinbox 값을 제한 할 때 찾아서 siganl 보내줌
//    }

    auto flag = (stock)? Qt::MatchCaseSensitive|Qt::MatchContains
                        : Qt::MatchCaseSensitive;
    QModelIndexList indexes = productModel->match(productModel->index(0, 3), Qt::EditRole, stock, -1,  Qt::MatchFlags(flag));

    foreach(auto index, indexes) {
        int p_id = productModel->data(index.siblingAtColumn(0)).toInt();
        QString productName = productModel->data(index.siblingAtColumn(1)).toString();
        QString price = productModel->data(index.siblingAtColumn(2)).toString();
        QString stock = productModel->data(index.siblingAtColumn(3)).toString();
        emit stockSended(stock.toInt());
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

void ProductManagerForm::findProduct(int index, int p_id)
{
    auto flag = (index)? Qt::MatchCaseSensitive|Qt::MatchContains
                        : Qt::MatchContains;
    QModelIndexList indexes = productModel->match(productModel->index(0, 0), Qt::EditRole, p_id, -1,  Qt::MatchFlags(flag));

    foreach(auto index, indexes) {
        int p_id = productModel->data(index.siblingAtColumn(0)).toInt();
        QString productName = productModel->data(index.siblingAtColumn(1)).toString();
        QString price = productModel->data(index.siblingAtColumn(2)).toString();
        QString stock = productModel->data(index.siblingAtColumn(3)).toString();
        emit sendProduct(p_id, productName, price, stock);
        }
}

void ProductManagerForm::findProduct(int index, QString text)
{
    //int i = ui->treeView->currentIndex();
    auto flag = (index)? Qt::MatchCaseSensitive|Qt::MatchContains
                       : Qt::MatchContains;
    if(index == 1)
    {
    QModelIndexList indexes = productModel->match(productModel->index(0, 1), Qt::EditRole, text, -1, Qt::MatchFlags(flag));

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

    QModelIndexList indexes = productModel->match(productModel->index(0, 2), Qt::EditRole, text, -1,Qt::MatchFlags(flag));

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
    QModelIndexList indexes = productModel->match(productModel->index(0, 3), Qt::EditRole, text, -1, Qt::MatchFlags(flag));

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
