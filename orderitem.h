#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QTreeWidgetItem>

class OrderItem : public QTreeWidgetItem
{
public:
    explicit OrderItem(int orderId = 0, QString = "", QString = "", QString = "",QString = "",QString = "",QString = "",QString = "");

    QString getOrderDate() const;
    void setOrderDate(QString&);                    /*QString형 OrderItem 첫 번째 자리*/
    QString getClientName() const;
    void setClientName(QString&);                   /*QString형 OrderItem 두 번째 자리*/
    QString getPhoneNumber() const;
    void setPhoneNumber(QString&);                  /*QString형 OrderItem 세 번째 자리*/
    QString getAddress() const;
    void setAddress(QString&);                      /*QString형 OrderItem 네 번째 자리*/
    QString getProductName() const;
    void setProductName(QString&);                  /*QString형 OrderItem 다섯 번째 자리*/
    QString getOrderQuantity() const;
    void setOrderQuauntity(QString&);               /*QString형 OrderItem 여섯 번째 자리*/
    QString getTotalPrice() const;
    void setTotalPrice(QString&);                    /*QString형 OrderItem 일곱 번째 자리*/
    int orderId() const;                             /*int 형 OrderItem 0번째 자리 return으로 반환받기 때문에 값을 주거나 얻을 필요 없음 */
    bool operator==(const OrderItem &other) const;   // 다른 클래스에서 키값을 찾기 위해서 비교연산자를 이용하여
                                                     //값을 비교 하기 위해서 설정 (현재 사용x)

};

#endif // ORDERITEM_H
