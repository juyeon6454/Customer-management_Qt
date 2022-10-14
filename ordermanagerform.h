#ifndef ORDERMANAGERFORM_H
#define ORDERMANAGERFORM_H

#include <QWidget>
#include <QHash>

#include "orderitem.h"
//#include "clientmanagerform.h"
//#include "productmanagerform.h"

class OrderItem;
class QMenu;
class QTreeWidgetItem;

class ClientItem;

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

private slots:
    /* QTreeWidget을 위한 슬롯 */

     void showContextMenu(const QPoint &);
      void removeItem();



      void on_orderSearchPushButton_clicked();

      void on_oderInputAddPushButton_clicked();

      void on_orderInputModifyPushButton_clicked();

      void on_orderSearchTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

      //void modifiedClient(ClientItem);
      void on_o_clientSearchPushButton_clicked();

      void o_showIdClient(int, ClientItem*);

signals:
      void o_searchIdClient(int);
      // void clientAdded(int, QString, QString, QString);


private:
    int makeId();

    QMap<int, OrderItem*> orderList;
    Ui::OrderManagerForm *ui;
    QMenu* menu;


};

#endif // ORDERMANAGERFORM_H
