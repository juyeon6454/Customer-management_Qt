#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QTreeWidgetItem>

class OrderItem : public QTreeWidgetItem
{
public:
    explicit OrderItem(int orderId = 0, QString = "", QString = "", QString = "",QString = "",QString = "",QString = "",QString = "");

    QString getOrderDate() const;
    void setOrderDate(QString&);
    QString getClientName() const;
    void setClientName(QString&);
    QString getPhoneNumber() const;
    void setPhoneNumber(QString&);
    QString getAddress() const;
    void setAddress(QString&);
    QString getProductName() const;
    void setProductName(QString&);
    QString getOrderQuantity() const;
    void setOrderQuauntity(QString&);
    QString getTotalPrice() const;
    void setTotalPrice(QString&);
    int orderId() const;
    bool operator==(const OrderItem &other) const;

};

#endif // ORDERITEM_H
