#ifndef CLIENTMANAGERFORM_H
#define CLIENTMANAGERFORM_H

#include <QWidget>
#include <QHash>

#include "clientitem.h"

class ClientItem;
class QMenu;
class QTreeWidgetItem;

namespace Ui {
class ClientManagerForm;
}

class ClientManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManagerForm(QWidget *parent = nullptr);
    ~ClientManagerForm();
    void loadData();

private slots:
    /* QTreeWidget을 위한 슬롯 */

    void showContextMenu(const QPoint &);
    void removeItem();              /* QAction을 위한 슬롯 */

    void on_searchPushButton_clicked();
    void on_modifyPushButton_clicked();
    void on_addPushButton_clicked();

    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);
signals:
    void clientAdded(QString);

private:
    int makeId();

    QMap<int, ClientItem*> clientList;
    Ui::ClientManagerForm *ui;
    QMenu* menu;
};

#endif // CLIENTMANAGERFORM_H
