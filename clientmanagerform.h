#ifndef CLIENTMANAGERFORM_H
#define CLIENTMANAGERFORM_H

#include "clientitem.h"
#include <QWidget>
#include <QHash>
#include <QSqlQueryModel>

class ClientItem;
class QMenu;
class QTreeWidgetItem;
class QSqlDatabase;
class QSqlTableModel;

namespace Ui {
class ClientManagerForm;
}

class ClientManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManagerForm(QWidget *parent = nullptr);              //생성자
    ~ClientManagerForm();                                               //소멸자
    void loadData();                                                    //data 저장한 txt 파일을 load
    void c_clearLineEdit();                                             //lineEdit 기록을 남기지 않고 지움

private slots:
    /* QTreeWidget을 위한 슬롯 */
    void on_searchPushButton_clicked();                                 //조회 버튼 누를 때
    void on_modifyPushButton_clicked();                                 //수정 버튼 누를 때
    void on_addPushButton_clicked();                                    //입력 버튼 누를 때
    void on_clearPushButton_clicked();  //clear 버튼을 누를 때
    void on_treeView_clicked(const QModelIndex &index);

    void showContextMenu(const QPoint &);
    void removeItem();                      /* QAction을 위한 슬롯 */

    void findClient(int, QString);
    void findClient(int, int);

signals:
 /*받아서 찾은 고객 정보를 보내는 slots*/
    void clientAdded(int, QString);             //server에 고객정보 추가
    void clientRemoved(int, QString);           //server에 제거된 고객 정보 연동
    void clientModified(int, int, QString);     //server에 수정된 고객 정보 연동

    void sendClient(int, QString, QString, QString,QString);

private:
    int makeId();                               //아이디 자동부여

    QMap<int, ClientItem*> clientList;
    Ui::ClientManagerForm *ui;
    QMenu* menu;

    QSqlTableModel* clientModel;

};

#endif // CLIENTMANAGERFORM_H
