#include "productitem.h"

#include <QLabel>
#include <iostream>

using namespace std;

ProductItem::ProductItem(int productId, QString productName, QString price, QString stock)
{
    setText(0, QString::number(productId));
    setText(1, productName);
    setText(2, price);
    setText(3, stock);
}

QString ProductItem::getProductName() const
{
    return text(1);
}
void ProductItem::setProductName(QString& productName)
{
    setText(1, productName);                            /*QString형 ProductItem 첫 번째 자리*/
}

QString ProductItem::getPrice() const
{
    return text(2);
}

void ProductItem::setPrice(QString& price)
{
    setText(2, price);                                  /*QString형 ProductItem 두 번째 자리*/
}

QString ProductItem::getStock() const
{
    return text(3);
}

void ProductItem::setStock(QString& stock)
{
    setText(3, stock);                                   /*QString형 ProductItem 세 번째 자리*/
}

int ProductItem::productId() const
{
    return text(0).toInt();
}


bool ProductItem::operator==(const ProductItem &other) const {
    return (this->text(1) == other.text(1));
}
