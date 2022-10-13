#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientmanagerform.h"
#include "productmanagerform.h"
#include "ordermanagerform.h"

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


    QMdiSubWindow *cw = ui->mdiArea->addSubWindow(clientForm);
        ui->mdiArea->addSubWindow(productForm);
        ui->mdiArea->addSubWindow(orderForm);
        ui->mdiArea->setActiveSubWindow(cw);


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

