#include "orderitem.h"

#include <QLabel>
#include <iostream>

using namespace std;

OrderItem::OrderItem(int orderId, QString orderDate, QString clientName, QString phoneNumber, QString address, QString productName, QString orderQuantity, QString totalPrice)
{
    setText(0, QString::number(orderId));
    setText(1, orderDate);
    setText(2, clientName);
    setText(3, phoneNumber);
    setText(4, address);
    setText(5, productName);
    setText(6, orderQuantity);
    setText(7, totalPrice);

}

QString OrderItem::getOrderDate() const
{
    return text(1);
}

void OrderItem::setOrderDate(QString& orderDate)
{
    setText(1, orderDate);
}

QString OrderItem::getClientName() const
{
    return text(2);
}

void OrderItem::setClientName(QString& clientName)
{
    setText(2, clientName);    // c_str() --> const char*
}

QString OrderItem::getPhoneNumber() const
{
    return text(3);
}

void OrderItem::setPhoneNumber(QString& phoneNumber)
{
    setText(3, phoneNumber);
}

QString OrderItem::getAddress() const
{
    return text(4);
}

void OrderItem::setAddress(QString& address)
{
    setText(4, address);
}
QString OrderItem::getProductName() const
{
    return text(5);
}

void OrderItem::setProductName(QString& productName)
{
    setText(5, productName);
}

QString OrderItem::getOrderQuantity() const
{
    return text(6);
}

void OrderItem::setOrderQuauntity(QString& orderQuantity)
{
    setText(6, orderQuantity);
}


QString OrderItem::getTotalPrice() const
{
    return text(7);
}

void OrderItem::setTotalPrice(QString& totalPrice)
{
    setText(7, totalPrice);
}

int OrderItem::orderId() const
{
    return text(0).toInt();
}

// Define copy assignment operator.
bool OrderItem::operator==(const OrderItem &other) const {
    return (this->text(1) == other.text(1));
}
