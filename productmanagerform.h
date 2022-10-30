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
    explicit ProductManagerForm(QWidget *parent = nullptr);     //생성자
    ~ProductManagerForm();                                      //소멸자
    void loadData();                                            //저장된 데이터 로드
    void p_clearLineEdit();                                     //lineEdit을 clear


private slots:
    /* QTreeWidget을 위한 슬롯 */
    void showContextMenu(const QPoint &);
    void removeItem();                      //action을 위한 slots

    void on_addPushButton_clicked();                                    //입력 버튼 누를 때
    void on_modifyPushButton_clicked();                                 //수정 버튼 누를 때
    void on_searchPushButton_clicked();                                 //조회 버튼 누를 때
    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);  //treewidget 아이템을 클릭할 때

    void p_findIdProduct(int);          //id로 정보 찾기
    void p_findNameProduct(QString);    //name으로 정보 찾기
    void p_findPriceProduct(QString);   //price로 정보 찾기
    void p_findStockProduct(QString);   //stock으로 정보 찾기
    void on_clearPushButton_clicked();  //clear 버튼 눌렀을 때


   void stockFinded(int);       //order에서 signal이 오면 stock 값을 찾음

signals:
    void p_sendIdProduct(int, ProductItem*);            //ip값을 order로 보냄
    void p_sendNameProduct(QString, ProductItem*);      //name값을 order로 보냄
    void p_sendPriceProduct(QString, ProductItem*);     //price값을 order로 보냄
    void p_sendStockProduct(QString, ProductItem*);     //stock값을  order로 보냄

    void stockSended(int);              // 찾은 stock 값을 보내줌
    //void productAdded(QString);

private:
    int makeId();                       // 아이디 자동 부여

    QMap<int, ProductItem*> productList;
    Ui::ProductManagerForm *ui;
    QMenu* menu;
};

#endif // PRODUCTMANAGER_H
