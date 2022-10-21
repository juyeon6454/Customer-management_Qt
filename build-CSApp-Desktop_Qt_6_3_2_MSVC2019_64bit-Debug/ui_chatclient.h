/********************************************************************************
** Form generated from reading UI file 'chatclient.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATCLIENT_H
#define UI_CHATCLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatClient
{
public:
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter;
    QGroupBox *logGroupBox;
    QVBoxLayout *verticalLayout;
    QSpacerItem *logInUpSpacer;
    QLabel *label_pic;
    QFormLayout *logformLayout;
    QLabel *nameLabel;
    QLabel *ipAddressLabel;
    QLineEdit *ipAddressLineEdit;
    QLabel *portNumLabel;
    QLineEdit *portNumLineEdit;
    QLineEdit *nameLineEdit;
    QHBoxLayout *logPushButtonLayout;
    QPushButton *logInPushButton;
    QPushButton *logOutPushButton;
    QSpacerItem *logInUnderSpacer;
    QGroupBox *chattingGroupBox;
    QVBoxLayout *verticalLayout_2;
    QPushButton *chatInPushButton;
    QTextEdit *messageTextEdit;
    QLineEdit *messageLineEdit;
    QHBoxLayout *chattingPushButtonLayour;
    QPushButton *fileTransferPushButton;
    QPushButton *sendPushButton;

    void setupUi(QWidget *ChatClient)
    {
        if (ChatClient->objectName().isEmpty())
            ChatClient->setObjectName(QString::fromUtf8("ChatClient"));
        ChatClient->resize(613, 390);
        horizontalLayout_3 = new QHBoxLayout(ChatClient);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        splitter = new QSplitter(ChatClient);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        logGroupBox = new QGroupBox(splitter);
        logGroupBox->setObjectName(QString::fromUtf8("logGroupBox"));
        verticalLayout = new QVBoxLayout(logGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        logInUpSpacer = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(logInUpSpacer);

        label_pic = new QLabel(logGroupBox);
        label_pic->setObjectName(QString::fromUtf8("label_pic"));

        verticalLayout->addWidget(label_pic, 0, Qt::AlignHCenter|Qt::AlignVCenter);

        logformLayout = new QFormLayout();
        logformLayout->setObjectName(QString::fromUtf8("logformLayout"));
        nameLabel = new QLabel(logGroupBox);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));

        logformLayout->setWidget(0, QFormLayout::LabelRole, nameLabel);

        ipAddressLabel = new QLabel(logGroupBox);
        ipAddressLabel->setObjectName(QString::fromUtf8("ipAddressLabel"));

        logformLayout->setWidget(1, QFormLayout::LabelRole, ipAddressLabel);

        ipAddressLineEdit = new QLineEdit(logGroupBox);
        ipAddressLineEdit->setObjectName(QString::fromUtf8("ipAddressLineEdit"));

        logformLayout->setWidget(1, QFormLayout::FieldRole, ipAddressLineEdit);

        portNumLabel = new QLabel(logGroupBox);
        portNumLabel->setObjectName(QString::fromUtf8("portNumLabel"));

        logformLayout->setWidget(2, QFormLayout::LabelRole, portNumLabel);

        portNumLineEdit = new QLineEdit(logGroupBox);
        portNumLineEdit->setObjectName(QString::fromUtf8("portNumLineEdit"));

        logformLayout->setWidget(2, QFormLayout::FieldRole, portNumLineEdit);

        nameLineEdit = new QLineEdit(logGroupBox);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));

        logformLayout->setWidget(0, QFormLayout::FieldRole, nameLineEdit);


        verticalLayout->addLayout(logformLayout);

        logPushButtonLayout = new QHBoxLayout();
        logPushButtonLayout->setObjectName(QString::fromUtf8("logPushButtonLayout"));
        logInPushButton = new QPushButton(logGroupBox);
        logInPushButton->setObjectName(QString::fromUtf8("logInPushButton"));

        logPushButtonLayout->addWidget(logInPushButton);

        logOutPushButton = new QPushButton(logGroupBox);
        logOutPushButton->setObjectName(QString::fromUtf8("logOutPushButton"));

        logPushButtonLayout->addWidget(logOutPushButton);


        verticalLayout->addLayout(logPushButtonLayout);

        logInUnderSpacer = new QSpacerItem(20, 115, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(logInUnderSpacer);

        splitter->addWidget(logGroupBox);
        chattingGroupBox = new QGroupBox(splitter);
        chattingGroupBox->setObjectName(QString::fromUtf8("chattingGroupBox"));
        verticalLayout_2 = new QVBoxLayout(chattingGroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        chatInPushButton = new QPushButton(chattingGroupBox);
        chatInPushButton->setObjectName(QString::fromUtf8("chatInPushButton"));

        verticalLayout_2->addWidget(chatInPushButton);

        messageTextEdit = new QTextEdit(chattingGroupBox);
        messageTextEdit->setObjectName(QString::fromUtf8("messageTextEdit"));

        verticalLayout_2->addWidget(messageTextEdit);

        messageLineEdit = new QLineEdit(chattingGroupBox);
        messageLineEdit->setObjectName(QString::fromUtf8("messageLineEdit"));

        verticalLayout_2->addWidget(messageLineEdit);

        chattingPushButtonLayour = new QHBoxLayout();
        chattingPushButtonLayour->setObjectName(QString::fromUtf8("chattingPushButtonLayour"));
        fileTransferPushButton = new QPushButton(chattingGroupBox);
        fileTransferPushButton->setObjectName(QString::fromUtf8("fileTransferPushButton"));

        chattingPushButtonLayour->addWidget(fileTransferPushButton);

        sendPushButton = new QPushButton(chattingGroupBox);
        sendPushButton->setObjectName(QString::fromUtf8("sendPushButton"));

        chattingPushButtonLayour->addWidget(sendPushButton);


        verticalLayout_2->addLayout(chattingPushButtonLayour);

        splitter->addWidget(chattingGroupBox);

        horizontalLayout_3->addWidget(splitter);


        retranslateUi(ChatClient);

        QMetaObject::connectSlotsByName(ChatClient);
    } // setupUi

    void retranslateUi(QWidget *ChatClient)
    {
        ChatClient->setWindowTitle(QCoreApplication::translate("ChatClient", "Form", nullptr));
        logGroupBox->setTitle(QCoreApplication::translate("ChatClient", "Log In", nullptr));
        label_pic->setText(QString());
        nameLabel->setText(QCoreApplication::translate("ChatClient", "Name", nullptr));
        ipAddressLabel->setText(QCoreApplication::translate("ChatClient", "IP Address", nullptr));
        portNumLabel->setText(QCoreApplication::translate("ChatClient", "Port No", nullptr));
        logInPushButton->setText(QCoreApplication::translate("ChatClient", "Log In", nullptr));
        logOutPushButton->setText(QCoreApplication::translate("ChatClient", "Log Out", nullptr));
        chattingGroupBox->setTitle(QCoreApplication::translate("ChatClient", "Chatting", nullptr));
        chatInPushButton->setText(QCoreApplication::translate("ChatClient", "Chat In", nullptr));
        fileTransferPushButton->setText(QCoreApplication::translate("ChatClient", "File Transfer", nullptr));
        sendPushButton->setText(QCoreApplication::translate("ChatClient", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatClient: public Ui_ChatClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATCLIENT_H
