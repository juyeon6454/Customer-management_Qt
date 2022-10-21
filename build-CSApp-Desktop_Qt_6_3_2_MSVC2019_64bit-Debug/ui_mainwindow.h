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
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionClientInfo = new QAction(MainWindow);
        actionClientInfo->setObjectName(QString::fromUtf8("actionClientInfo"));
        actionProductInfo = new QAction(MainWindow);
        actionProductInfo->setObjectName(QString::fromUtf8("actionProductInfo"));
        actionOrderInfo = new QAction(MainWindow);
        actionOrderInfo->setObjectName(QString::fromUtf8("actionOrderInfo"));
        actionChat = new QAction(MainWindow);
        actionChat->setObjectName(QString::fromUtf8("actionChat"));
        actionChatManager = new QAction(MainWindow);
        actionChatManager->setObjectName(QString::fromUtf8("actionChatManager"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));
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
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionQuit);
        menuFile->addAction(actionNew);
        toolBar->addAction(actionClientInfo);
        toolBar->addSeparator();
        toolBar->addAction(actionProductInfo);
        toolBar->addSeparator();
        toolBar->addAction(actionOrderInfo);
        toolBar->addSeparator();
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
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
