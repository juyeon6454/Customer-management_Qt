/********************************************************************************
** Form generated from reading UI file 'ordermanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDERMANAGERFORM_H
#define UI_ORDERMANAGERFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrderManagerForm
{
public:
    QGridLayout *gridLayout;
    QSplitter *splitter;
    QGroupBox *orderInputGroupBox;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *orderIdLabel;
    QLineEdit *orderIdLineEdit;
    QLabel *orderDateLabel;
    QLineEdit *orderDateLineEdit;
    QLabel *ClientNameLabel;
    QLineEdit *clientNameLineEdit;
    QLabel *phoneNumberLabel;
    QLineEdit *phoneNumberLineEdit;
    QLabel *addressLabel;
    QLineEdit *addressLineEdit;
    QLabel *productNameLabel;
    QLineEdit *productNameLineEdit;
    QLabel *orderQuantityLabel;
    QSpinBox *orderQuantitySpinBox;
    QLabel *totalPriceLabel;
    QLineEdit *totalPriceLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *oderInputAddPushButton;
    QPushButton *orderInputModifyPushButton;
    QPushButton *orderClearPushButton;
    QVBoxLayout *searchCPVerticalLayout;
    QHBoxLayout *o_clientSearchHorizontalLayout;
    QComboBox *o_clientSearchComboBox;
    QLineEdit *o_clientSearchLineEdit;
    QPushButton *o_clientSearchPushButton;
    QTreeWidget *o_clientInfoTreeWidget;
    QHBoxLayout *o_productSearchHorizontalLayout;
    QComboBox *o_productSearchComboBox;
    QLineEdit *o_productSearchLineEdit;
    QPushButton *o_productSearchPushButton;
    QTreeWidget *o_productInfoTreeWidget;
    QGroupBox *orderListGroupBox;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_2;
    QTreeWidget *orderSearchTreeWidget;
    QWidget *layoutWidget;
    QVBoxLayout *orderSearchVerticalLayout;
    QHBoxLayout *orderSeacrhHorizontalLayout;
    QComboBox *orderSearchComboBox;
    QLineEdit *orderSearchLineEdit;
    QPushButton *orderSearchPushButton;
    QTreeWidget *orderSearchTreeWidget_2;

    void setupUi(QWidget *OrderManagerForm)
    {
        if (OrderManagerForm->objectName().isEmpty())
            OrderManagerForm->setObjectName(QString::fromUtf8("OrderManagerForm"));
        OrderManagerForm->resize(892, 444);
        gridLayout = new QGridLayout(OrderManagerForm);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        splitter = new QSplitter(OrderManagerForm);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        orderInputGroupBox = new QGroupBox(splitter);
        orderInputGroupBox->setObjectName(QString::fromUtf8("orderInputGroupBox"));
        orderInputGroupBox->setFlat(false);
        gridLayout_3 = new QGridLayout(orderInputGroupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        orderIdLabel = new QLabel(orderInputGroupBox);
        orderIdLabel->setObjectName(QString::fromUtf8("orderIdLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, orderIdLabel);

        orderIdLineEdit = new QLineEdit(orderInputGroupBox);
        orderIdLineEdit->setObjectName(QString::fromUtf8("orderIdLineEdit"));
        orderIdLineEdit->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, orderIdLineEdit);

        orderDateLabel = new QLabel(orderInputGroupBox);
        orderDateLabel->setObjectName(QString::fromUtf8("orderDateLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, orderDateLabel);

        orderDateLineEdit = new QLineEdit(orderInputGroupBox);
        orderDateLineEdit->setObjectName(QString::fromUtf8("orderDateLineEdit"));
        orderDateLineEdit->setReadOnly(true);

        formLayout->setWidget(1, QFormLayout::FieldRole, orderDateLineEdit);

        ClientNameLabel = new QLabel(orderInputGroupBox);
        ClientNameLabel->setObjectName(QString::fromUtf8("ClientNameLabel"));

        formLayout->setWidget(2, QFormLayout::LabelRole, ClientNameLabel);

        clientNameLineEdit = new QLineEdit(orderInputGroupBox);
        clientNameLineEdit->setObjectName(QString::fromUtf8("clientNameLineEdit"));

        formLayout->setWidget(2, QFormLayout::FieldRole, clientNameLineEdit);

        phoneNumberLabel = new QLabel(orderInputGroupBox);
        phoneNumberLabel->setObjectName(QString::fromUtf8("phoneNumberLabel"));

        formLayout->setWidget(3, QFormLayout::LabelRole, phoneNumberLabel);

        phoneNumberLineEdit = new QLineEdit(orderInputGroupBox);
        phoneNumberLineEdit->setObjectName(QString::fromUtf8("phoneNumberLineEdit"));

        formLayout->setWidget(3, QFormLayout::FieldRole, phoneNumberLineEdit);

        addressLabel = new QLabel(orderInputGroupBox);
        addressLabel->setObjectName(QString::fromUtf8("addressLabel"));

        formLayout->setWidget(4, QFormLayout::LabelRole, addressLabel);

        addressLineEdit = new QLineEdit(orderInputGroupBox);
        addressLineEdit->setObjectName(QString::fromUtf8("addressLineEdit"));

        formLayout->setWidget(4, QFormLayout::FieldRole, addressLineEdit);

        productNameLabel = new QLabel(orderInputGroupBox);
        productNameLabel->setObjectName(QString::fromUtf8("productNameLabel"));

        formLayout->setWidget(5, QFormLayout::LabelRole, productNameLabel);

        productNameLineEdit = new QLineEdit(orderInputGroupBox);
        productNameLineEdit->setObjectName(QString::fromUtf8("productNameLineEdit"));

        formLayout->setWidget(5, QFormLayout::FieldRole, productNameLineEdit);

        orderQuantityLabel = new QLabel(orderInputGroupBox);
        orderQuantityLabel->setObjectName(QString::fromUtf8("orderQuantityLabel"));

        formLayout->setWidget(6, QFormLayout::LabelRole, orderQuantityLabel);

        orderQuantitySpinBox = new QSpinBox(orderInputGroupBox);
        orderQuantitySpinBox->setObjectName(QString::fromUtf8("orderQuantitySpinBox"));

        formLayout->setWidget(6, QFormLayout::FieldRole, orderQuantitySpinBox);

        totalPriceLabel = new QLabel(orderInputGroupBox);
        totalPriceLabel->setObjectName(QString::fromUtf8("totalPriceLabel"));

        formLayout->setWidget(7, QFormLayout::LabelRole, totalPriceLabel);

        totalPriceLineEdit = new QLineEdit(orderInputGroupBox);
        totalPriceLineEdit->setObjectName(QString::fromUtf8("totalPriceLineEdit"));
        totalPriceLineEdit->setReadOnly(true);

        formLayout->setWidget(7, QFormLayout::FieldRole, totalPriceLineEdit);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        oderInputAddPushButton = new QPushButton(orderInputGroupBox);
        oderInputAddPushButton->setObjectName(QString::fromUtf8("oderInputAddPushButton"));

        horizontalLayout->addWidget(oderInputAddPushButton);

        orderInputModifyPushButton = new QPushButton(orderInputGroupBox);
        orderInputModifyPushButton->setObjectName(QString::fromUtf8("orderInputModifyPushButton"));

        horizontalLayout->addWidget(orderInputModifyPushButton);

        orderClearPushButton = new QPushButton(orderInputGroupBox);
        orderClearPushButton->setObjectName(QString::fromUtf8("orderClearPushButton"));

        horizontalLayout->addWidget(orderClearPushButton);


        verticalLayout->addLayout(horizontalLayout);

        searchCPVerticalLayout = new QVBoxLayout();
        searchCPVerticalLayout->setObjectName(QString::fromUtf8("searchCPVerticalLayout"));
        o_clientSearchHorizontalLayout = new QHBoxLayout();
        o_clientSearchHorizontalLayout->setObjectName(QString::fromUtf8("o_clientSearchHorizontalLayout"));
        o_clientSearchComboBox = new QComboBox(orderInputGroupBox);
        o_clientSearchComboBox->addItem(QString());
        o_clientSearchComboBox->addItem(QString());
        o_clientSearchComboBox->addItem(QString());
        o_clientSearchComboBox->addItem(QString());
        o_clientSearchComboBox->addItem(QString());
        o_clientSearchComboBox->setObjectName(QString::fromUtf8("o_clientSearchComboBox"));

        o_clientSearchHorizontalLayout->addWidget(o_clientSearchComboBox);

        o_clientSearchLineEdit = new QLineEdit(orderInputGroupBox);
        o_clientSearchLineEdit->setObjectName(QString::fromUtf8("o_clientSearchLineEdit"));

        o_clientSearchHorizontalLayout->addWidget(o_clientSearchLineEdit);

        o_clientSearchPushButton = new QPushButton(orderInputGroupBox);
        o_clientSearchPushButton->setObjectName(QString::fromUtf8("o_clientSearchPushButton"));

        o_clientSearchHorizontalLayout->addWidget(o_clientSearchPushButton);


        searchCPVerticalLayout->addLayout(o_clientSearchHorizontalLayout);

        o_clientInfoTreeWidget = new QTreeWidget(orderInputGroupBox);
        o_clientInfoTreeWidget->setObjectName(QString::fromUtf8("o_clientInfoTreeWidget"));

        searchCPVerticalLayout->addWidget(o_clientInfoTreeWidget);

        o_productSearchHorizontalLayout = new QHBoxLayout();
        o_productSearchHorizontalLayout->setObjectName(QString::fromUtf8("o_productSearchHorizontalLayout"));
        o_productSearchComboBox = new QComboBox(orderInputGroupBox);
        o_productSearchComboBox->addItem(QString());
        o_productSearchComboBox->addItem(QString());
        o_productSearchComboBox->addItem(QString());
        o_productSearchComboBox->addItem(QString());
        o_productSearchComboBox->setObjectName(QString::fromUtf8("o_productSearchComboBox"));

        o_productSearchHorizontalLayout->addWidget(o_productSearchComboBox);

        o_productSearchLineEdit = new QLineEdit(orderInputGroupBox);
        o_productSearchLineEdit->setObjectName(QString::fromUtf8("o_productSearchLineEdit"));

        o_productSearchHorizontalLayout->addWidget(o_productSearchLineEdit);

        o_productSearchPushButton = new QPushButton(orderInputGroupBox);
        o_productSearchPushButton->setObjectName(QString::fromUtf8("o_productSearchPushButton"));

        o_productSearchHorizontalLayout->addWidget(o_productSearchPushButton);


        searchCPVerticalLayout->addLayout(o_productSearchHorizontalLayout);

        o_productInfoTreeWidget = new QTreeWidget(orderInputGroupBox);
        o_productInfoTreeWidget->setObjectName(QString::fromUtf8("o_productInfoTreeWidget"));

        searchCPVerticalLayout->addWidget(o_productInfoTreeWidget);


        verticalLayout->addLayout(searchCPVerticalLayout);


        gridLayout_3->addLayout(verticalLayout, 0, 0, 1, 1);

        splitter->addWidget(orderInputGroupBox);
        orderListGroupBox = new QGroupBox(splitter);
        orderListGroupBox->setObjectName(QString::fromUtf8("orderListGroupBox"));
        orderListGroupBox->setFlat(false);
        orderListGroupBox->setCheckable(false);
        verticalLayout_3 = new QVBoxLayout(orderListGroupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter_2 = new QSplitter(orderListGroupBox);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        orderSearchTreeWidget = new QTreeWidget(splitter_2);
        orderSearchTreeWidget->setObjectName(QString::fromUtf8("orderSearchTreeWidget"));
        splitter_2->addWidget(orderSearchTreeWidget);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        orderSearchVerticalLayout = new QVBoxLayout(layoutWidget);
        orderSearchVerticalLayout->setObjectName(QString::fromUtf8("orderSearchVerticalLayout"));
        orderSearchVerticalLayout->setContentsMargins(0, 0, 0, 0);
        orderSeacrhHorizontalLayout = new QHBoxLayout();
        orderSeacrhHorizontalLayout->setObjectName(QString::fromUtf8("orderSeacrhHorizontalLayout"));
        orderSearchComboBox = new QComboBox(layoutWidget);
        orderSearchComboBox->addItem(QString());
        orderSearchComboBox->addItem(QString());
        orderSearchComboBox->addItem(QString());
        orderSearchComboBox->addItem(QString());
        orderSearchComboBox->addItem(QString());
        orderSearchComboBox->addItem(QString());
        orderSearchComboBox->addItem(QString());
        orderSearchComboBox->addItem(QString());
        orderSearchComboBox->setObjectName(QString::fromUtf8("orderSearchComboBox"));

        orderSeacrhHorizontalLayout->addWidget(orderSearchComboBox);

        orderSearchLineEdit = new QLineEdit(layoutWidget);
        orderSearchLineEdit->setObjectName(QString::fromUtf8("orderSearchLineEdit"));

        orderSeacrhHorizontalLayout->addWidget(orderSearchLineEdit);

        orderSearchPushButton = new QPushButton(layoutWidget);
        orderSearchPushButton->setObjectName(QString::fromUtf8("orderSearchPushButton"));

        orderSeacrhHorizontalLayout->addWidget(orderSearchPushButton);


        orderSearchVerticalLayout->addLayout(orderSeacrhHorizontalLayout);

        orderSearchTreeWidget_2 = new QTreeWidget(layoutWidget);
        orderSearchTreeWidget_2->setObjectName(QString::fromUtf8("orderSearchTreeWidget_2"));

        orderSearchVerticalLayout->addWidget(orderSearchTreeWidget_2);

        splitter_2->addWidget(layoutWidget);

        verticalLayout_3->addWidget(splitter_2);

        splitter->addWidget(orderListGroupBox);

        gridLayout->addWidget(splitter, 0, 0, 1, 1);

#if QT_CONFIG(shortcut)
        orderIdLabel->setBuddy(orderIdLineEdit);
        orderDateLabel->setBuddy(orderDateLineEdit);
        ClientNameLabel->setBuddy(clientNameLineEdit);
        phoneNumberLabel->setBuddy(phoneNumberLineEdit);
        addressLabel->setBuddy(addressLineEdit);
        productNameLabel->setBuddy(productNameLineEdit);
        orderQuantityLabel->setBuddy(orderQuantitySpinBox);
        totalPriceLabel->setBuddy(totalPriceLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(OrderManagerForm);

        QMetaObject::connectSlotsByName(OrderManagerForm);
    } // setupUi

    void retranslateUi(QWidget *OrderManagerForm)
    {
        OrderManagerForm->setWindowTitle(QCoreApplication::translate("OrderManagerForm", "Form", nullptr));
        orderInputGroupBox->setTitle(QCoreApplication::translate("OrderManagerForm", "Input Order", nullptr));
        orderIdLabel->setText(QCoreApplication::translate("OrderManagerForm", "&ID", nullptr));
        orderIdLineEdit->setText(QString());
        orderDateLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Order Date", nullptr));
        ClientNameLabel->setText(QCoreApplication::translate("OrderManagerForm", "Client Name", nullptr));
        clientNameLineEdit->setText(QString());
        phoneNumberLabel->setText(QCoreApplication::translate("OrderManagerForm", "Phone Number", nullptr));
        addressLabel->setText(QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        productNameLabel->setText(QCoreApplication::translate("OrderManagerForm", "Product Name", nullptr));
        orderQuantityLabel->setText(QCoreApplication::translate("OrderManagerForm", "&Order Quantity", nullptr));
        totalPriceLabel->setText(QCoreApplication::translate("OrderManagerForm", "Total Price", nullptr));
        oderInputAddPushButton->setText(QCoreApplication::translate("OrderManagerForm", "Add", nullptr));
        orderInputModifyPushButton->setText(QCoreApplication::translate("OrderManagerForm", "Modify", nullptr));
        orderClearPushButton->setText(QCoreApplication::translate("OrderManagerForm", "Clear", nullptr));
        o_clientSearchComboBox->setItemText(0, QCoreApplication::translate("OrderManagerForm", "Client ID", nullptr));
        o_clientSearchComboBox->setItemText(1, QCoreApplication::translate("OrderManagerForm", "Client Name", nullptr));
        o_clientSearchComboBox->setItemText(2, QCoreApplication::translate("OrderManagerForm", "Phone Number", nullptr));
        o_clientSearchComboBox->setItemText(3, QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        o_clientSearchComboBox->setItemText(4, QCoreApplication::translate("OrderManagerForm", "E-mail", nullptr));

        o_clientSearchPushButton->setText(QCoreApplication::translate("OrderManagerForm", "Search", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = o_clientInfoTreeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QCoreApplication::translate("OrderManagerForm", "E-mail", nullptr));
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("OrderManagerForm", "Phone Number", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("OrderManagerForm", "Client Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("OrderManagerForm", "Client ID", nullptr));
        o_productSearchComboBox->setItemText(0, QCoreApplication::translate("OrderManagerForm", "Product ID", nullptr));
        o_productSearchComboBox->setItemText(1, QCoreApplication::translate("OrderManagerForm", "Product Name", nullptr));
        o_productSearchComboBox->setItemText(2, QCoreApplication::translate("OrderManagerForm", "Price", nullptr));
        o_productSearchComboBox->setItemText(3, QCoreApplication::translate("OrderManagerForm", "Stock", nullptr));

        o_productSearchPushButton->setText(QCoreApplication::translate("OrderManagerForm", "Search", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = o_productInfoTreeWidget->headerItem();
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("OrderManagerForm", "Stock", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("OrderManagerForm", "Price", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("OrderManagerForm", "Product Name", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("OrderManagerForm", "Product ID", nullptr));
        orderListGroupBox->setTitle(QCoreApplication::translate("OrderManagerForm", "Order List", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = orderSearchTreeWidget->headerItem();
        ___qtreewidgetitem2->setText(7, QCoreApplication::translate("OrderManagerForm", "Total Price", nullptr));
        ___qtreewidgetitem2->setText(6, QCoreApplication::translate("OrderManagerForm", "Order Quantity", nullptr));
        ___qtreewidgetitem2->setText(5, QCoreApplication::translate("OrderManagerForm", "Product Name", nullptr));
        ___qtreewidgetitem2->setText(4, QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        ___qtreewidgetitem2->setText(3, QCoreApplication::translate("OrderManagerForm", "Phone number", nullptr));
        ___qtreewidgetitem2->setText(2, QCoreApplication::translate("OrderManagerForm", "Client Name", nullptr));
        ___qtreewidgetitem2->setText(1, QCoreApplication::translate("OrderManagerForm", "Order Date", nullptr));
        ___qtreewidgetitem2->setText(0, QCoreApplication::translate("OrderManagerForm", "ID", nullptr));
        orderSearchComboBox->setItemText(0, QCoreApplication::translate("OrderManagerForm", "Order ID", nullptr));
        orderSearchComboBox->setItemText(1, QCoreApplication::translate("OrderManagerForm", "Order Date", nullptr));
        orderSearchComboBox->setItemText(2, QCoreApplication::translate("OrderManagerForm", "Client Name", nullptr));
        orderSearchComboBox->setItemText(3, QCoreApplication::translate("OrderManagerForm", "Phone number", nullptr));
        orderSearchComboBox->setItemText(4, QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        orderSearchComboBox->setItemText(5, QCoreApplication::translate("OrderManagerForm", "Product Name", nullptr));
        orderSearchComboBox->setItemText(6, QCoreApplication::translate("OrderManagerForm", "Order Quantity", nullptr));
        orderSearchComboBox->setItemText(7, QCoreApplication::translate("OrderManagerForm", "Total Price", nullptr));

        orderSearchPushButton->setText(QCoreApplication::translate("OrderManagerForm", "Search", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = orderSearchTreeWidget_2->headerItem();
        ___qtreewidgetitem3->setText(7, QCoreApplication::translate("OrderManagerForm", "Total Price", nullptr));
        ___qtreewidgetitem3->setText(6, QCoreApplication::translate("OrderManagerForm", "Order Quantity", nullptr));
        ___qtreewidgetitem3->setText(5, QCoreApplication::translate("OrderManagerForm", "Product Name", nullptr));
        ___qtreewidgetitem3->setText(4, QCoreApplication::translate("OrderManagerForm", "Address", nullptr));
        ___qtreewidgetitem3->setText(3, QCoreApplication::translate("OrderManagerForm", "Phone Number", nullptr));
        ___qtreewidgetitem3->setText(2, QCoreApplication::translate("OrderManagerForm", "Client Name", nullptr));
        ___qtreewidgetitem3->setText(1, QCoreApplication::translate("OrderManagerForm", "Order Date", nullptr));
        ___qtreewidgetitem3->setText(0, QCoreApplication::translate("OrderManagerForm", "Order ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OrderManagerForm: public Ui_OrderManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDERMANAGERFORM_H
