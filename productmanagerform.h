#ifndef PRODUCTMANAGERFORMH_H
#define PRODUCTMANAGERFORM_H

#include <QWidget>
#include <QHash>
#include <QSqlQueryModel>

class QMenu;
class QTreeWidgetItem;
class QSqlDatabase;
class QSqlTableModel;
class QStandardItemModel;

namespace Ui {
class ProductManagerForm;
}

class ProductManagerForm : public QWidget
{
    Q_OBJECT

public:
    explicit ProductManagerForm(QWidget *parent = nullptr);     //생성자
    ~ProductManagerForm();                                      //소멸자
    void loadData();                                            //저장된 데이터 로드
    void p_clearLineEdit();                                     //lineEdit을 clear


private slots:
    /* QTreeWidget을 위한 슬롯 */

    void on_addPushButton_clicked();                                    //입력 버튼 누를 때
    void on_modifyPushButton_clicked();                                 //수정 버튼 누를 때
    void on_searchPushButton_clicked();                                 //조회 버튼 누를 때
    void on_clearPushButton_clicked();                                  //clear 버튼 눌렀을 때
    void on_treeView_clicked(const QModelIndex &index);

    void showContextMenu(const QPoint &);
    void removeItem();                                                  //action을 위한 slots

    void findProduct(int, QString);
    void findProduct(int, int);
    void stockFinded(int);                                              //order에서 signal이 오면 stock 값을 찾음


signals:
    /*받아서 찾은 고객 정보를 보내는 slots*/
    void productAdded(int, QString);             //server에 고객정보 추가
    void productRemoved(int, QString);           //server에 제거된 고객 정보 연동
    void productModified(int, int, QString);     //server에 수정된 고객 정보 연동

    void sendProduct(int, QString, QString, QString);
    void stockSended(int);                               // 찾은 stock 값을 보내줌

private:
    int makeId();                       // 아이디 자동 부여
    Ui::ProductManagerForm *ui;
    QMenu* menu;
    QSqlTableModel* productModel;
    QStandardItemModel* s_productModel;
};

#endif // PRODUCTMANAGER_H
