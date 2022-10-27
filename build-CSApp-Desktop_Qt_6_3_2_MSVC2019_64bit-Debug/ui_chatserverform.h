/********************************************************************************
** Form generated from reading UI file 'chatserverform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATSERVERFORM_H
#define UI_CHATSERVERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatServerForm
{
public:
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *clientListVerticalLayout;
    QLabel *clientListLabel;
    QTreeWidget *clientTreeWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *layoutWidget_2;
    QVBoxLayout *messageVerticalLayout;
    QTreeWidget *messageTreeWidget;
    QHBoxLayout *messageLayout;
    QPushButton *clearPushButton;
    QPushButton *savePushButton;

    void setupUi(QWidget *ChatServerForm)
    {
        if (ChatServerForm->objectName().isEmpty())
            ChatServerForm->setObjectName(QString::fromUtf8("ChatServerForm"));
        ChatServerForm->resize(490, 329);
        verticalLayout = new QVBoxLayout(ChatServerForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(ChatServerForm);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        clientListVerticalLayout = new QVBoxLayout(layoutWidget);
        clientListVerticalLayout->setObjectName(QString::fromUtf8("clientListVerticalLayout"));
        clientListVerticalLayout->setContentsMargins(0, 0, 0, 0);
        clientListLabel = new QLabel(layoutWidget);
        clientListLabel->setObjectName(QString::fromUtf8("clientListLabel"));

        clientListVerticalLayout->addWidget(clientListLabel);

        clientTreeWidget = new QTreeWidget(layoutWidget);
        clientTreeWidget->setObjectName(QString::fromUtf8("clientTreeWidget"));
        clientTreeWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        clientTreeWidget->setRootIsDecorated(false);
        clientTreeWidget->setHeaderHidden(true);

        clientListVerticalLayout->addWidget(clientTreeWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));

        clientListVerticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(layoutWidget);
        layoutWidget_2 = new QWidget(splitter);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        messageVerticalLayout = new QVBoxLayout(layoutWidget_2);
        messageVerticalLayout->setObjectName(QString::fromUtf8("messageVerticalLayout"));
        messageVerticalLayout->setContentsMargins(0, 0, 0, 0);
        messageTreeWidget = new QTreeWidget(layoutWidget_2);
        messageTreeWidget->setObjectName(QString::fromUtf8("messageTreeWidget"));
        messageTreeWidget->setRootIsDecorated(false);
        messageTreeWidget->setWordWrap(true);

        messageVerticalLayout->addWidget(messageTreeWidget);

        messageLayout = new QHBoxLayout();
        messageLayout->setObjectName(QString::fromUtf8("messageLayout"));
        clearPushButton = new QPushButton(layoutWidget_2);
        clearPushButton->setObjectName(QString::fromUtf8("clearPushButton"));

        messageLayout->addWidget(clearPushButton);

        savePushButton = new QPushButton(layoutWidget_2);
        savePushButton->setObjectName(QString::fromUtf8("savePushButton"));

        messageLayout->addWidget(savePushButton);


        messageVerticalLayout->addLayout(messageLayout);

        splitter->addWidget(layoutWidget_2);

        verticalLayout->addWidget(splitter);


        retranslateUi(ChatServerForm);

        QMetaObject::connectSlotsByName(ChatServerForm);
    } // setupUi

    void retranslateUi(QWidget *ChatServerForm)
    {
        ChatServerForm->setWindowTitle(QCoreApplication::translate("ChatServerForm", "Form", nullptr));
        clientListLabel->setText(QCoreApplication::translate("ChatServerForm", "Client List", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = clientTreeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ChatServerForm", "Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ChatServerForm", "Status", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = messageTreeWidget->headerItem();
        ___qtreewidgetitem1->setText(5, QCoreApplication::translate("ChatServerForm", "Time", nullptr));
        ___qtreewidgetitem1->setText(4, QCoreApplication::translate("ChatServerForm", "Message", nullptr));
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("ChatServerForm", "Name", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("ChatServerForm", "ID", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("ChatServerForm", "Port", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("ChatServerForm", "IP", nullptr));
        clearPushButton->setText(QCoreApplication::translate("ChatServerForm", "Clear", nullptr));
        savePushButton->setText(QCoreApplication::translate("ChatServerForm", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatServerForm: public Ui_ChatServerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATSERVERFORM_H
