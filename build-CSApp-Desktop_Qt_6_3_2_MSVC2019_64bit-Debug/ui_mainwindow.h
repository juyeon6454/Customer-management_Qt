/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionNew;
    QAction *actionClientInfo;
    QAction *actionProductInfo;
    QAction *actionOrderInfo;
    QAction *actionChat;
    QAction *actionChatManager;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QMdiArea *mdiArea;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setBaseSize(QSize(0, 0));
        QFont font;
        font.setFamilies({QString::fromUtf8("\353\247\221\354\235\200 \352\263\240\353\224\225")});
        MainWindow->setFont(font);
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        MainWindow->setTabShape(QTabWidget::Triangular);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionQuit->setEnabled(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/quit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionClientInfo = new QAction(MainWindow);
        actionClientInfo->setObjectName(QString::fromUtf8("actionClientInfo"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/client.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClientInfo->setIcon(icon1);
        actionProductInfo = new QAction(MainWindow);
        actionProductInfo->setObjectName(QString::fromUtf8("actionProductInfo"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/product.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionProductInfo->setIcon(icon2);
        actionOrderInfo = new QAction(MainWindow);
        actionOrderInfo->setObjectName(QString::fromUtf8("actionOrderInfo"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/order.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOrderInfo->setIcon(icon3);
        actionChat = new QAction(MainWindow);
        actionChat->setObjectName(QString::fromUtf8("actionChat"));
        actionChat->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/chat.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionChat->setIcon(icon4);
        actionChat->setVisible(true);
        actionChat->setMenuRole(QAction::TextHeuristicRole);
        actionChat->setPriority(QAction::NormalPriority);
        actionChatManager = new QAction(MainWindow);
        actionChatManager->setObjectName(QString::fromUtf8("actionChatManager"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/chatmanager.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionChatManager->setIcon(icon5);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
        mdiArea->setAutoFillBackground(false);
        mdiArea->setViewMode(QMdiArea::TabbedView);
        mdiArea->setDocumentMode(true);
        mdiArea->setTabsClosable(false);

        horizontalLayout->addWidget(mdiArea);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menubar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMaximumSize(QSize(50, 16777215));
        toolBar->setMouseTracking(false);
        toolBar->setAutoFillBackground(false);
        toolBar->setMovable(false);
        toolBar->setIconSize(QSize(40, 40));
        toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        toolBar->setFloatable(true);
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionQuit);
        menuFile->addAction(actionNew);
        toolBar->addAction(actionClientInfo);
        toolBar->addAction(actionProductInfo);
        toolBar->addAction(actionOrderInfo);
        toolBar->addAction(actionChatManager);
        toolBar->addSeparator();
        toolBar->addAction(actionChat);
        toolBar->addSeparator();
        toolBar->addAction(actionQuit);
        toolBar->addSeparator();

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, &QAction::triggered, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(tooltip)
        actionQuit->setToolTip(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#endif // QT_CONFIG(tooltip)
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("MainWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
        actionClientInfo->setText(QCoreApplication::translate("MainWindow", "ClientInfo", nullptr));
#if QT_CONFIG(tooltip)
        actionClientInfo->setToolTip(QCoreApplication::translate("MainWindow", "ClientInfo", nullptr));
#endif // QT_CONFIG(tooltip)
        actionProductInfo->setText(QCoreApplication::translate("MainWindow", "ProductInfo", nullptr));
        actionOrderInfo->setText(QCoreApplication::translate("MainWindow", "OrderInfo", nullptr));
        actionChat->setText(QCoreApplication::translate("MainWindow", "Chat", nullptr));
        actionChatManager->setText(QCoreApplication::translate("MainWindow", "ChatManager", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
#if QT_CONFIG(whatsthis)
        toolBar->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
