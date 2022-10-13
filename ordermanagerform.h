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

signals:
    void clientAdded(QString);

private:
    int makeId();

    QMap<int, OrderItem*> orderList;
    Ui::OrderManagerForm *ui;
    QMenu* menu;
};

#endif // ORDERMANAGERFORM_H
