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

    void c_findIdClient(int);
    void c_findNameClient(QString);
    void c_findNumberClient(QString);
    void c_findAddressClient(QString);
    void c_findEmailClient(QString);

    void on_clearPushButton_clicked();

signals:

    void c_sendIdClient(int, ClientItem*);
    void c_sendNameClient(QString, ClientItem*);
    void c_sendNumberClient(QString, ClientItem*);
    void c_sendAddressClient(QString, ClientItem*);
    void c_sendEmailClient(QString, ClientItem*);

    void clientAdded(int, QString);
    void clientRemoved(int, QString);
    void clientModified(int, int, QString);
private:
    int makeId();

    QMap<int, ClientItem*> clientList;
    Ui::ClientManagerForm *ui;
    QMenu* menu;

};

#endif // CLIENTMANAGERFORM_H
