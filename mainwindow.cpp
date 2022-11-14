#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clientmanagerform.h"
#include "productmanagerform.h"
#include "ordermanagerform.h"
#include "chatclient.h"
#include "chatserverform.h"

#include <QApplication>
#include <QTreeView>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    clientForm = new ClientManagerForm(this);          //client Info 생성
    clientForm->setWindowTitle(tr("Client Info"));
    connect(clientForm, SIGNAL(destroyed()),           //삭제 시그널을 보내도 나중에 삭제하도록
            clientForm, SLOT(deleteLater()));

    productForm = new ProductManagerForm(this);
    productForm->setWindowTitle(tr("Product Info"));    //product Info 생성
    connect(productForm, SIGNAL(destroyed()),           //삭제 시그널을 보내도 나중에 삭제하도록
            productForm, SLOT(deleteLater()));

    orderForm = new OrderManagerForm(this);             //Order Info 생성
    orderForm->setWindowTitle(tr("Order Info"));        //삭제 시그널을 보내도 나중에 삭제하도록
    connect(orderForm, SIGNAL(destroyed()),
            orderForm, SLOT(deleteLater()));

    serverForm = new ChatServerForm(this);              //chat Manager 생성
    serverForm->setWindowTitle(tr("Chat Manager"));     //삭제 시그널을 보내도 나중에 삭제하도록
    connect(serverForm, SIGNAL(destroyed()),
            serverForm, SLOT(deleteLater()));

    QMdiSubWindow *cw = ui->mdiArea->addSubWindow(clientForm);
    ui->mdiArea->addSubWindow(productForm);
    ui->mdiArea->addSubWindow(orderForm);
    ui->mdiArea->addSubWindow(serverForm);
    ui->mdiArea->setActiveSubWindow(cw);                        //가장 먼저 보이는 창 clientForm

    connect(orderForm, SIGNAL(searchClient(int, QString)), clientForm, SLOT(findClient(int,QString)));
    connect(orderForm, SIGNAL(searchClient(int, int)), clientForm, SLOT(findClient(int, int)));
    connect(clientForm, SIGNAL(sendClient(int, QString, QString, QString,QString)),orderForm, SLOT(showClient(int,QString, QString, QString,QString)));
    /*order에서 client 정보를 요청하면 client 정보를 찾아서 order 고객정보조회 lienedit로 받아감*/

    connect(orderForm, SIGNAL(searchProduct(int, QString)), productForm, SLOT(findProduct(int,QString)));
    connect(orderForm, SIGNAL(searchProduct(int, int)), productForm, SLOT(findProduct(int, int)));
    connect(productForm, SIGNAL(sendProduct(int, QString, QString, QString)),orderForm, SLOT(showProduct(int,QString, QString, QString)));
    /*order에서 product 정보를 요청하면 product 정보를 찾아서 order 상품정보조회 lienedit로 받아감*/

    connect(clientForm, SIGNAL(clientAdded(int, QString)), serverForm, SLOT(addClient(int, QString)));
    connect(clientForm, SIGNAL(clientRemoved(int,QString)), serverForm, SLOT(removeServerClient(int, QString)));
    connect(clientForm, SIGNAL(clientModified(int, int, QString)), serverForm, SLOT(modifyServerClient(int, int, QString)));
    /*server clientList로 client 정보 연결 (수정, 삭제시에도)*/

    connect(orderForm, SIGNAL(stockSearched(int)), productForm, SLOT(stockFinded(int)));
    connect(productForm, SIGNAL(stockSended(int)), orderForm, SLOT(stockShowed(int)));
    /*재고량 spinbox 값 제한할 때 product에서 order로 재고량 전달*/

    clientForm->loadData();
    productForm->loadData();
    orderForm->loadData();      /*저장된 정보들.txt을 불러옴*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClientInfo_triggered()    //toolbar에 clienttInfo를 눌렀을 때 clientForm으로 이동
{
    if(clientForm != nullptr) {
        clientForm->setFocus();
    }
}

void MainWindow::on_actionProductInfo_triggered()   //toolbar에 productInfo를 눌렀을 때 productForm으로 이동
{
    if(productForm != nullptr) {
        productForm->setFocus();
    }
}

void MainWindow::on_actionOrderInfo_triggered()     //toolbar에 orderInfo를 눌렀을 때 orderForm으로 이동
{
    if(orderForm != nullptr) {
        orderForm->setFocus();
    }
}

void MainWindow::on_actionChat_triggered()          //toolbar에 chat 눌렀을 때 chatForm으로 이동
{
    ChatClient* chatForm = new ChatClient(nullptr);
    chatForm->show();
}


void MainWindow::on_actionChatManager_triggered()
{
    if(serverForm != nullptr) {
        serverForm->setFocus();                     //toolbar에 chatmanager를 눌렀을 때 serverForm으로 이동
    }
}

