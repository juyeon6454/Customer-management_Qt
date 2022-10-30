#ifndef PRODUCTITEM_H
#define PRODUCTITEM_H

#include <QTreeWidgetItem>

class ProductItem : public QTreeWidgetItem
{
public:
    explicit ProductItem(int productId = 0, QString = "", QString = "", QString = "");

    QString getProductName() const;
    void setProductName(QString&);                   /*QString형 ProductItem 첫 번째 자리*/
    QString getPrice() const;
    void setPrice(QString&);                         /*QString형 ProductItem 두 번째 자리*/
    QString getStock() const;
    void setStock(QString&);                         /*QString형 ProductItem 세 번째 자리*/
    int productId() const;                           /*int형 ProductItem 0번째 자리 return으로 반환받기 때문에 값을 주거나 얻을 필요 없음 */
    bool operator==(const ProductItem &other) const;
};


#endif // PRODUCTITEM_H
