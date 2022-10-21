#ifndef PRODUCTMANAGERFORMH
#define PRODUCTMANAGERFORM_H

#include <QWidget>
#include <QHash>

#include "productitem.h"

class ProductItem;
class QMenu;
class QTreeWidgetItem;

namespace Ui {
class ProductManagerForm;
}

class ProductManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductManagerForm(QWidget *parent = nullptr);
    ~ProductManagerForm();
    void loadData();


private slots:
    /* QTreeWidget을 위한 슬롯 */
    void showContextMenu(const QPoint &);
    void removeItem();

    void on_addPushButton_clicked();
    void on_modifyPushButton_clicked();
    void on_searchPushButton_clicked();
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void p_findIdProduct(int);
    void p_findNameProduct(QString);
    void p_findPriceProduct(QString);
    void p_findStockProduct(QString);
    void on_clearPushButton_clicked();

signals:
    void p_sendIdProduct(int, ProductItem*);
    void p_sendNameProduct(QString, ProductItem*);
    void p_sendPriceProduct(QString, ProductItem*);
    void p_sendStockProduct(QString, ProductItem*);

    void stockAdded(QString);
    //void productAdded(QString);

private:
    int makeId();

    QMap<int, ProductItem*> productList;
    Ui::ProductManagerForm *ui;
    QMenu* menu;
};

#endif // PRODUCTMANAGER_H
