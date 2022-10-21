#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QTreeWidgetItem>

class ProductItem : public QTreeWidgetItem
{
public:
    explicit ProductItem(int productId = 0, QString = "", QString = "", QString = "");

    QString getProductName() const;
    void setProductName(QString&);
    QString getPrice() const;
    void setPrice(QString&);
    QString getStock() const;
    void setStock(QString&);
    int productId() const;
    bool operator==(const ProductItem &other) const;
};


#endif // PRODUCTITEM_H
