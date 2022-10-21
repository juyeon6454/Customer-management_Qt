/********************************************************************************
** Form generated from reading UI file 'clientmanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTMANAGERFORM_H
#define UI_CLIENTMANAGERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientManagerForm
{
public:
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QToolBox *toolBox;
    QWidget *inputPage;
    QVBoxLayout *verticalLayout;
    QFormLayout *clientFormLayout;
    QLabel *clientIdLabel;
    QLineEdit *clientIdLineEdit;
    QLabel *clientNameLabel;
    QLineEdit *clientNameLineEdit;
    QLabel *phoneNumberLabel;
    QLineEdit *phoneNumberLineEdit;
    QLabel *addressLabel;
    QLineEdit *addressLineEdit;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *amHorizontalLayout;
    QPushButton *addPushButton;
    QPushButton *modifyPushButton;
    QPushButton *clearPushButton;
    QWidget *searchPage;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *idHorizontalLayout;
    QComboBox *searchComboBox;
    QLineEdit *searchLineEdit;
    QPushButton *searchPushButton;
    QTreeWidget *searchTreeWidget;
    QWidget *layoutWidget;
    QVBoxLayout *clientListVerticalLayout;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *ClientManagerForm)
    {
        if (ClientManagerForm->objectName().isEmpty())
            ClientManagerForm->setObjectName(QString::fromUtf8("ClientManagerForm"));
        ClientManagerForm->resize(529, 330);
        horizontalLayout = new QHBoxLayout(ClientManagerForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(ClientManagerForm);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        inputPage = new QWidget();
        inputPage->setObjectName(QString::fromUtf8("inputPage"));
        inputPage->setGeometry(QRect(0, 0, 262, 260));
        verticalLayout = new QVBoxLayout(inputPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        clientFormLayout = new QFormLayout();
        clientFormLayout->setObjectName(QString::fromUtf8("clientFormLayout"));
        clientIdLabel = new QLabel(inputPage);
        clientIdLabel->setObjectName(QString::fromUtf8("clientIdLabel"));

        clientFormLayout->setWidget(0, QFormLayout::LabelRole, clientIdLabel);

        clientIdLineEdit = new QLineEdit(inputPage);
        clientIdLineEdit->setObjectName(QString::fromUtf8("clientIdLineEdit"));
        clientIdLineEdit->setReadOnly(true);

        clientFormLayout->setWidget(0, QFormLayout::FieldRole, clientIdLineEdit);

        clientNameLabel = new QLabel(inputPage);
        clientNameLabel->setObjectName(QString::fromUtf8("clientNameLabel"));

        clientFormLayout->setWidget(1, QFormLayout::LabelRole, clientNameLabel);

        clientNameLineEdit = new QLineEdit(inputPage);
        clientNameLineEdit->setObjectName(QString::fromUtf8("clientNameLineEdit"));

        clientFormLayout->setWidget(1, QFormLayout::FieldRole, clientNameLineEdit);

        phoneNumberLabel = new QLabel(inputPage);
        phoneNumberLabel->setObjectName(QString::fromUtf8("phoneNumberLabel"));

        clientFormLayout->setWidget(2, QFormLayout::LabelRole, phoneNumberLabel);

        phoneNumberLineEdit = new QLineEdit(inputPage);
        phoneNumberLineEdit->setObjectName(QString::fromUtf8("phoneNumberLineEdit"));

        clientFormLayout->setWidget(2, QFormLayout::FieldRole, phoneNumberLineEdit);

        addressLabel = new QLabel(inputPage);
        addressLabel->setObjectName(QString::fromUtf8("addressLabel"));

        clientFormLayout->setWidget(3, QFormLayout::LabelRole, addressLabel);

        addressLineEdit = new QLineEdit(inputPage);
        addressLineEdit->setObjectName(QString::fromUtf8("addressLineEdit"));

        clientFormLayout->setWidget(3, QFormLayout::FieldRole, addressLineEdit);

        emailLabel = new QLabel(inputPage);
        emailLabel->setObjectName(QString::fromUtf8("emailLabel"));

        clientFormLayout->setWidget(4, QFormLayout::LabelRole, emailLabel);

        emailLineEdit = new QLineEdit(inputPage);
        emailLineEdit->setObjectName(QString::fromUtf8("emailLineEdit"));

        clientFormLayout->setWidget(4, QFormLayout::FieldRole, emailLineEdit);


        verticalLayout->addLayout(clientFormLayout);

        verticalSpacer = new QSpacerItem(17, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        amHorizontalLayout = new QHBoxLayout();
        amHorizontalLayout->setObjectName(QString::fromUtf8("amHorizontalLayout"));
        addPushButton = new QPushButton(inputPage);
        addPushButton->setObjectName(QString::fromUtf8("addPushButton"));

        amHorizontalLayout->addWidget(addPushButton);

        modifyPushButton = new QPushButton(inputPage);
        modifyPushButton->setObjectName(QString::fromUtf8("modifyPushButton"));

        amHorizontalLayout->addWidget(modifyPushButton);

        clearPushButton = new QPushButton(inputPage);
        clearPushButton->setObjectName(QString::fromUtf8("clearPushButton"));

        amHorizontalLayout->addWidget(clearPushButton);


        verticalLayout->addLayout(amHorizontalLayout);

        toolBox->addItem(inputPage, QString::fromUtf8("Input"));
        searchPage = new QWidget();
        searchPage->setObjectName(QString::fromUtf8("searchPage"));
        searchPage->setGeometry(QRect(0, 0, 210, 270));
        verticalLayout_2 = new QVBoxLayout(searchPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        idHorizontalLayout = new QHBoxLayout();
        idHorizontalLayout->setObjectName(QString::fromUtf8("idHorizontalLayout"));
        searchComboBox = new QComboBox(searchPage);
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->addItem(QString());
        searchComboBox->setObjectName(QString::fromUtf8("searchComboBox"));

        idHorizontalLayout->addWidget(searchComboBox);

        searchLineEdit = new QLineEdit(searchPage);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));

        idHorizontalLayout->addWidget(searchLineEdit);


        verticalLayout_2->addLayout(idHorizontalLayout);

        searchPushButton = new QPushButton(searchPage);
        searchPushButton->setObjectName(QString::fromUtf8("searchPushButton"));

        verticalLayout_2->addWidget(searchPushButton);

        searchTreeWidget = new QTreeWidget(searchPage);
        searchTreeWidget->setObjectName(QString::fromUtf8("searchTreeWidget"));

        verticalLayout_2->addWidget(searchTreeWidget);

        toolBox->addItem(searchPage, QString::fromUtf8("Search"));
        splitter->addWidget(toolBox);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        clientListVerticalLayout = new QVBoxLayout(layoutWidget);
        clientListVerticalLayout->setObjectName(QString::fromUtf8("clientListVerticalLayout"));
        clientListVerticalLayout->setContentsMargins(0, 0, 0, 0);
        treeWidget = new QTreeWidget(layoutWidget);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setRootIsDecorated(false);

        clientListVerticalLayout->addWidget(treeWidget);

        splitter->addWidget(layoutWidget);

        horizontalLayout->addWidget(splitter);

#if QT_CONFIG(shortcut)
        clientIdLabel->setBuddy(clientIdLineEdit);
        clientNameLabel->setBuddy(clientNameLineEdit);
        phoneNumberLabel->setBuddy(phoneNumberLineEdit);
        addressLabel->setBuddy(addressLineEdit);
        emailLabel->setBuddy(emailLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(ClientManagerForm);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ClientManagerForm);
    } // setupUi

    void retranslateUi(QWidget *ClientManagerForm)
    {
        ClientManagerForm->setWindowTitle(QCoreApplication::translate("ClientManagerForm", "Form", nullptr));
        clientIdLabel->setText(QCoreApplication::translate("ClientManagerForm", "&ID", nullptr));
        clientIdLineEdit->setText(QString());
        clientNameLabel->setText(QCoreApplication::translate("ClientManagerForm", "&Name", nullptr));
        clientNameLineEdit->setText(QString());
        phoneNumberLabel->setText(QCoreApplication::translate("ClientManagerForm", "&Phone number", nullptr));
        addressLabel->setText(QCoreApplication::translate("ClientManagerForm", "&Address", nullptr));
        emailLabel->setText(QCoreApplication::translate("ClientManagerForm", "&E-mail", nullptr));
        addPushButton->setText(QCoreApplication::translate("ClientManagerForm", "Add", nullptr));
        modifyPushButton->setText(QCoreApplication::translate("ClientManagerForm", "Modify", nullptr));
        clearPushButton->setText(QCoreApplication::translate("ClientManagerForm", "Clear", nullptr));
        toolBox->setItemText(toolBox->indexOf(inputPage), QCoreApplication::translate("ClientManagerForm", "Input", nullptr));
        searchComboBox->setItemText(0, QCoreApplication::translate("ClientManagerForm", "ID", nullptr));
        searchComboBox->setItemText(1, QCoreApplication::translate("ClientManagerForm", "Name", nullptr));
        searchComboBox->setItemText(2, QCoreApplication::translate("ClientManagerForm", "Phone number", nullptr));
        searchComboBox->setItemText(3, QCoreApplication::translate("ClientManagerForm", "Address", nullptr));
        searchComboBox->setItemText(4, QCoreApplication::translate("ClientManagerForm", "E-mail", nullptr));

        searchPushButton->setText(QCoreApplication::translate("ClientManagerForm", "Search", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = searchTreeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("ClientManagerForm", "E-mail", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("ClientManagerForm", "Address", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ClientManagerForm", "Phone number", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ClientManagerForm", "Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ClientManagerForm", "ID", nullptr));
        toolBox->setItemText(toolBox->indexOf(searchPage), QCoreApplication::translate("ClientManagerForm", "Search", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->headerItem();
        ___qtreewidgetitem1->setText(4, QCoreApplication::translate("ClientManagerForm", "E-mail", nullptr));
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("ClientManagerForm", "Address", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("ClientManagerForm", "Phone Number", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("ClientManagerForm", "Name", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("ClientManagerForm", "ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientManagerForm: public Ui_ClientManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTMANAGERFORM_H
