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
    explicit OrderManagerForm(QWidget *parent = nullptr);   //생성자
    ~OrderManagerForm();                                    //소멸자
    void loadData();                                        //저장된 txt 파일 데이터 로드
   // int stockRange();
    void o_clearLineEdit();                                 //lineEdit 기록 정리

private slots:
     /* QTreeWidget을 위한 슬롯 */
     void showContextMenu(const QPoint &);
     void removeItem();                             /* QAction을 위한 슬롯 */

/*      void o_showIdClient(int, ClientItem*);
      void o_showNameClient(QString, ClientItem*);
      void o_showNumberClient(QString, ClientItem*);
      void o_showAddressClient(QString, ClientItem*);
      void o_showEmailClient(QString, ClientItem*);/* /*받아온 고객 정보를 보여주는 slots*/

      void showClient(int, QString, QString, QString, QString);

      void o_showIdProduct(int, ProductItem*);
      void o_showNameProduct(QString, ProductItem*);
      void o_showPriceProduct(QString, ProductItem*);
      void o_showStockProduct(QString, ProductItem*); /*받아온 상품 정보를 보여주는 slots*/

      void on_orderSearchPushButton_clicked();      //주문조회 버튼 누를 때
      void on_oderInputAddPushButton_clicked();     //주문입력 버튼 누를 때
      void on_o_clientSearchPushButton_clicked();   //고객조회 버튼 누를 때
      void on_o_productSearchPushButton_clicked();  //상품조회 버튼 누를 때
      void on_orderInputModifyPushButton_clicked(); //주문변경 버튼 누를 때

      void on_o_clientSearchLineEdit_returnPressed();   //고객조회 엔터값
      void on_o_productSearchLineEdit_returnPressed();  //상품조회 엔터값
      void on_orderSearchLineEdit_returnPressed();      //주문조회 엔터값

      void on_o_clientInfoTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
      void on_o_productInfoTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
      void on_orderSearchTreeWidget_itemClicked(QTreeWidgetItem *item, int column);     /*각 treeWidget의 아이템을 클릭했을 때 lineEdit에 나타남*/

      void on_orderQuantitySpinBox_valueChanged(int);   //주문수량 spinbox값이 변할 때
      void stockShowed(int);                            //재고량을 받아옴

      void on_orderClearPushButton_clicked();           //lineEidt에 기록을 지우기 위한 함수


signals:
/*      void o_searchIdClient(int);
      void o_searchNameClient(QString);
      void o_searchNumberClient(QString);
      void o_searchAddressClient(QString);
      void o_searchEmailClient(QString); */       /*콤보박스를 통해 검색한 내용으로 고객 정보를 찾아달라는 signal*/

      void searchClient(int, QString);
      void searchClient(int, int);

      void o_searchIdProduct(int);
      void o_searchNameProduct(QString);
      void o_searchPriceProduct(QString);
      void o_searchStockProduct(QString);       /*콤보박스를 통해 검색한 내용으로 상품 정보를 찾아달라는 signal*/

      void stockSearched(int);                  //재고량 검색 signal

      void getClientInfo(int);
private:
    int makeId();                       //id 자동부여

    QString currentDateTime();          //날짜 시간 자동부여

    QMap<int, OrderItem*> orderList;    //map으로 orderlist관리
    Ui::OrderManagerForm *ui;
    QMenu* menu;
};

#endif // ORDERMANAGERFORM_H
