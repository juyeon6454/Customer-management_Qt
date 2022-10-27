#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientmanagerform.h"
#include "productmanagerform.h"
#include "ordermanagerform.h"
#include "chatclient.h"
#include "chatserverform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ClientManagerForm *clientForm1 = new ClientManagerForm(0);
//    clientForm1->show();
    clientForm = new ClientManagerForm(this);
    clientForm->setWindowTitle(tr("Client Info"));
    connect(clientForm, SIGNAL(destroyed()),
            clientForm, SLOT(deleteLater()));

//    ui->tabWidget->addTab(clientForm, "&Client Info");
//    ProductManagerForm *productForm = new ProductManagerForm(this);
//    productForm->setWindowTitle(tr("Product Info"));

    productForm = new ProductManagerForm(this);
    productForm->setWindowTitle(tr("Product Info"));
    connect(productForm, SIGNAL(destroyed()),
            productForm, SLOT(deleteLater()));

    orderForm = new OrderManagerForm(this);
    orderForm->setWindowTitle(tr("Order Info"));
    connect(orderForm, SIGNAL(destroyed()),
            orderForm, SLOT(deleteLater()));

    serverForm = new ChatServerForm(this);
    serverForm->setWindowTitle(tr("Chat Manager"));
    connect(serverForm, SIGNAL(destroyed()),
            serverForm, SLOT(deleteLater()));
    //toolbar 추가

    QMdiSubWindow *cw = ui->mdiArea->addSubWindow(clientForm);
    ui->mdiArea->addSubWindow(productForm);
    ui->mdiArea->addSubWindow(orderForm);
    ui->mdiArea->addSubWindow(serverForm);
    ui->mdiArea->setActiveSubWindow(cw); //가장 먼저 보이는 창

    connect(orderForm, SIGNAL(o_searchIdClient(int)), clientForm, SLOT(c_findIdClient(int)));
    connect(clientForm, SIGNAL(c_sendIdClient(int, ClientItem*)), orderForm, SLOT(o_showIdClient(int, ClientItem*)));
    connect(orderForm, SIGNAL(o_searchNameClient(QString)), clientForm, SLOT(c_findNameClient(QString)));
    connect(clientForm, SIGNAL(c_sendNameClient(QString, ClientItem*)), orderForm, SLOT(o_showNameClient(QString, ClientItem*)));
    connect(orderForm, SIGNAL(o_searchNumberClient(QString)), clientForm, SLOT(c_findNumberClient(QString)));
    connect(clientForm, SIGNAL(c_sendNumberClient(QString, ClientItem*)), orderForm, SLOT(o_showNumberClient(QString, ClientItem*)));
    connect(orderForm, SIGNAL(o_searchAddressClient(QString)), clientForm, SLOT(c_findAddressClient(QString)));
    connect(clientForm, SIGNAL(c_sendAddressClient(QString, ClientItem*)), orderForm, SLOT(o_showAddressClient(QString, ClientItem*)));
    connect(orderForm, SIGNAL(o_searchEmailClient(QString)), clientForm, SLOT(c_findEmailClient(QString)));
    connect(clientForm, SIGNAL(c_sendEmailClient(QString, ClientItem*)), orderForm, SLOT(o_showEmailClient(QString, ClientItem*)));
    //client 정보를 order 고객정보찾기 lienedit로 받아감

    connect(orderForm, SIGNAL(o_searchIdProduct(int)), productForm, SLOT(p_findIdProduct(int)));
    connect(productForm, SIGNAL(p_sendIdProduct(int, ProductItem*)), orderForm, SLOT(o_showIdProduct(int, ProductItem*)));
    connect(orderForm, SIGNAL(o_searchNameProduct(QString)), productForm, SLOT(p_findNameProduct(QString)));
    connect(productForm, SIGNAL(p_sendNameProduct(QString, ProductItem*)), orderForm, SLOT(o_showNameProduct(QString, ProductItem*)));
    connect(orderForm, SIGNAL(o_searchPriceProduct(QString)), productForm, SLOT(p_findPriceProduct(QString)));
    connect(productForm, SIGNAL(p_sendPriceProduct(QString, ProductItem*)), orderForm, SLOT(o_showPriceProduct(QString, ProductItem*)));
    connect(orderForm, SIGNAL(o_searchStockProduct(QString)), productForm, SLOT(p_findStockProduct(QString)));
    connect(productForm, SIGNAL(p_sendStockProduct(QString, ProductItem*)), orderForm, SLOT(o_showStockProduct(QString, ProductItem*)));
    //product 정보를 order 상품정보찾기 lienedit로 받아감

    connect(clientForm, SIGNAL(clientAdded(int, QString)), serverForm, SLOT(addClient(int, QString)));
    connect(clientForm, SIGNAL(clientRemoved(int,QString)), serverForm, SLOT(removeServerClient(int, QString)));
    connect(clientForm, SIGNAL(clientModified(int, int, QString)), serverForm, SLOT(modifyServerClient(int, int, QString)));
    //server clientList로 client 정보 연결

    //connect(clientForm, SIGNAL(clientModified(i nt, ClientItem*)), orderForm, SLOT(modifyClient(int, OrderItem*)));
    //client 정보를 수정했을 때 order, product 수정 및 삭제

    connect(orderForm, SIGNAL(stockSearched(int)), productForm, SLOT(stockFinded(int)));
    connect(productForm, SIGNAL(stockSended(int)), orderForm, SLOT(stockShowed(int)));
    //재고량 spinbox 값 제한할 때


    clientForm->loadData();
    productForm->loadData();
    orderForm->loadData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClientInfo_triggered()
{
    if(clientForm != nullptr) {
        clientForm->setFocus();
    }
}

void MainWindow::on_actionProductInfo_triggered()
{
    if(productForm != nullptr) {
        productForm->setFocus();
    }
}

void MainWindow::on_actionOrderInfo_triggered()
{
    if(orderForm != nullptr) {
        orderForm->setFocus();
    }
}


void MainWindow::on_actionChat_triggered()
{
    ChatClient* chatForm = new ChatClient(nullptr);
    chatForm->show();
}


void MainWindow::on_actionChatManager_triggered()
{
    if(serverForm != nullptr) {
        serverForm->setFocus();
    }
}
