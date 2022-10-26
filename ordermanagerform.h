#ifndef ORDERMANAGERFORM_H
#define ORDERMANAGERFORM_H

#include <QWidget>
#include <QHash>

#include "orderitem.h"
#include "productitem.h"
//#include "clientmanagerform.h"
//#include "productmanagerform.h"

class OrderItem;
class QMenu;
class QTreeWidgetItem;

class ClientItem;
class ProductItem;

namespace Ui {
class OrderManagerForm;
}

class OrderManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit OrderManagerForm(QWidget *parent = nullptr);
    ~OrderManagerForm();
    void loadData();
    int stockRange();

private slots:
    /* QTreeWidget을 위한 슬롯 */

     void showContextMenu(const QPoint &);
     void removeItem();
     //void stockReceived(QString);


      void on_orderSearchPushButton_clicked();
      void on_oderInputAddPushButton_clicked();
      void on_orderInputModifyPushButton_clicked();
      void on_orderSearchTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

      void on_o_clientSearchPushButton_clicked();

      void o_showIdClient(int, ClientItem*);
      void o_showNameClient(QString, ClientItem*);
      void o_showNumberClient(QString, ClientItem*);
      void o_showAddressClient(QString, ClientItem*);
      void o_showEmailClient(QString, ClientItem*);

      void o_showIdProduct(int, ProductItem*);
      void o_showNameProduct(QString, ProductItem*);
      void o_showPriceProduct(QString, ProductItem*);
      void o_showStockProduct(QString, ProductItem*);


      void on_o_productSearchPushButton_clicked();
      void on_o_clientInfoTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
      void on_o_productInfoTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

      void on_o_clientSearchLineEdit_returnPressed();

      void on_o_productSearchLineEdit_returnPressed();

      void on_orderSearchLineEdit_returnPressed();

      void on_orderQuantitySpinBox_valueChanged(int);

      void stockShowed(int);

      void on_orderClearPushButton_clicked();

signals:
      void o_searchIdClient(int);
      void o_searchNameClient(QString);
      void o_searchNumberClient(QString);
      void o_searchAddressClient(QString);
      void o_searchEmailClient(QString);

      void o_searchIdProduct(int);
      void o_searchNameProduct(QString);
      void o_searchPriceProduct(QString);
      void o_searchStockProduct(QString);

      void stockSearched(int);
      //void clientModified()


private:
    int makeId();

    QString currentDateTime();

    QMap<int, OrderItem*> orderList;
    QHash<int, ProductItem*> stockList;
    Ui::OrderManagerForm *ui;
    QMenu* menu;
};

#endif // ORDERMANAGERFORM_H
