#include "orderitem.h"

#include <QLabel>
#include <iostream>

using namespace std;

OrderItem::OrderItem(int orderId, QString orderDate, QString clientName, QString phoneNumber, QString address, QString productName, QString orderQuantity, QString totalPrice)
{
    setText(0, QString::number(orderId));   //주문 ID
    setText(1, orderDate);                  //주문날짜
    setText(2, clientName);                 //고객이름
    setText(3, phoneNumber);                //핸드폰번호
    setText(4, address);                    //주소
    setText(5, productName);                //상품명
    setText(6, orderQuantity);              //주문수량
    setText(7, totalPrice);                 //총가격

}

QString OrderItem::getOrderDate() const
{
    return text(1);
}

void OrderItem::setOrderDate(QString& orderDate)
{
    setText(1, orderDate);                        /*QString형 OrderItem 첫 번째 자리*/
}

QString OrderItem::getClientName() const
{
    return text(2);
}

void OrderItem::setClientName(QString& clientName)
{
    setText(2, clientName);                        /*QString형 OrderItem 두 번째 자리*/
}

QString OrderItem::getPhoneNumber() const
{
    return text(3);
}

void OrderItem::setPhoneNumber(QString& phoneNumber)
{
    setText(3, phoneNumber);                        /*QString형 OrderItem 세 번째 자리*/
}

QString OrderItem::getAddress() const
{
    return text(4);
}

void OrderItem::setAddress(QString& address)
{
    setText(4, address);                            /*QString형 OrderItem 네 번째 자리*/
}
QString OrderItem::getProductName() const
{
    return text(5);
}

void OrderItem::setProductName(QString& productName)
{
    setText(5, productName);                         /*QString형 OrderItem 다섯 번째 자리*/
}

QString OrderItem::getOrderQuantity() const
{
    return text(6);
}

void OrderItem::setOrderQuauntity(QString& orderQuantity)
{
    setText(6, orderQuantity);                        /*QString형 OrderItem 여섯 번째 자리*/
}


QString OrderItem::getTotalPrice() const
{
    return text(7);
}

void OrderItem::setTotalPrice(QString& totalPrice)
{
    setText(7, totalPrice);                           /*QString형 OrderItem 일곱 번째 자리*/
}

int OrderItem::orderId() const
{
    return text(0).toInt();                         /*int 형 OrderItem 0번째 자리 return으로 반환받기 때문에
                                                        값을 주거나 얻을 필요 없음 */
}

// 다른 클래스에서 키값을 찾기 위해서 비교연산자를 이용하여
//값을 비교 하기 위해서 설정 (현재 사용x)
bool OrderItem::operator==(const OrderItem &other) const {
    return (this->text(1) == other.text(1));
}
