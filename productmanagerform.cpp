#include "productmanagerform.h"
#include "ui_productmanagerform.h"
#include "productitem.h"

#include <QFile>
#include <QMenu>

ProductManagerForm::ProductManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductManagerForm)
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

void ProductManagerForm::loadData()
{
    QFile file("productlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int productId = row[0].toInt();
            ProductItem* p = new ProductItem(productId, row[1], row[2], row[3]);
            ui->treeWidget->addTopLevelItem(p);
            productList.insert(productId, p);

            emit productAdded(row[1]);
        }
    }
    file.close( );
}

ProductManagerForm::~ProductManagerForm()
{
    delete ui;

    QFile file("productlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : productList) {
        ProductItem *p = v;
        out << p->productId() << ", " <<p->getProductName() << ", ";
        out << p->getPrice() << ", ";
        out << p->getStock() << "\n";//ProductItem.key(p)
    }
    file.close( );
}

int ProductManagerForm::makeId( )
{
    if(productList.size( ) == 0) {
        return 100;
    } else {
        auto productId = productList.lastKey();
        return ++productId;
    }
}

void ProductManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        productList.remove(item->text(0).toInt());
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->treeWidget->update();
    }
}

void ProductManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ProductManagerForm::on_addPushButton_clicked()
{
    QString productName, price, stock;
    int productId = makeId( );
    productName = ui->productNameLineEdit->text();
    price = ui->priceLineEdit->text();
    stock = ui->stockLineEdit->text();
    if(productName.length()) {
        ProductItem* p = new ProductItem(productId, productName, price, stock);
        productList.insert(productId, p);
        ui->treeWidget->addTopLevelItem(p);
        emit productAdded(productName);
    }
}


void ProductManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        ProductItem* p = productList[key];
        QString productName, price, stock;
        productName = ui->productNameLineEdit->text();
        price = ui->priceLineEdit->text();
        stock = ui->stockLineEdit->text();
        p->setProductName(productName);
        p->setPrice(price);
        p->setStock(stock);
        productList[key] = p;
    }
}


void ProductManagerForm::on_searchPushButton_clicked()
{
    ui->searchTreeWidget->clear();
//    for(int i = 0; i < ui->treeWidget->columnCount(); i++)
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), flag, i);

        foreach(auto i, items) {
            ProductItem* p = static_cast<ProductItem*>(i);
            int productId = p->productId();
            QString name = p->getProductName();
            QString price = p->getPrice();
            QString stock = p->getStock();
            ProductItem* item = new ProductItem(productId, name, price, stock);
            ui->searchTreeWidget->addTopLevelItem(item);
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
    ui->toolBox->setCurrentIndex(0);
}

