/********************************************************************************
** Form generated from reading UI file 'productmanagerform.ui'
**
** Created by: Qt User Interface Compiler version 6.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRODUCTMANAGERFORM_H
#define UI_PRODUCTMANAGERFORM_H

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

class Ui_ProductManagerForm
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QToolBox *toolBox;
    QWidget *inputPage;
    QVBoxLayout *verticalLayout;
    QFormLayout *productFormLayout;
    QLabel *productIdLabel;
    QLineEdit *productIdLineEdit;
    QLabel *productNameLabel;
    QLineEdit *productNameLineEdit;
    QLabel *priceLabel;
    QLineEdit *priceLineEdit;
    QLabel *stockLabel;
    QLineEdit *stockLineEdit;
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
    QTreeWidget *treeWidget;

    void setupUi(QWidget *ProductManagerForm)
    {
        if (ProductManagerForm->objectName().isEmpty())
            ProductManagerForm->setObjectName(QString::fromUtf8("ProductManagerForm"));
        ProductManagerForm->resize(933, 366);
        verticalLayout_3 = new QVBoxLayout(ProductManagerForm);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter = new QSplitter(ProductManagerForm);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        toolBox = new QToolBox(splitter);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        inputPage = new QWidget();
        inputPage->setObjectName(QString::fromUtf8("inputPage"));
        inputPage->setGeometry(QRect(0, 0, 464, 306));
        verticalLayout = new QVBoxLayout(inputPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        productFormLayout = new QFormLayout();
        productFormLayout->setObjectName(QString::fromUtf8("productFormLayout"));
        productIdLabel = new QLabel(inputPage);
        productIdLabel->setObjectName(QString::fromUtf8("productIdLabel"));

        productFormLayout->setWidget(0, QFormLayout::LabelRole, productIdLabel);

        productIdLineEdit = new QLineEdit(inputPage);
        productIdLineEdit->setObjectName(QString::fromUtf8("productIdLineEdit"));
        productIdLineEdit->setReadOnly(true);

        productFormLayout->setWidget(0, QFormLayout::FieldRole, productIdLineEdit);

        productNameLabel = new QLabel(inputPage);
        productNameLabel->setObjectName(QString::fromUtf8("productNameLabel"));

        productFormLayout->setWidget(1, QFormLayout::LabelRole, productNameLabel);

        productNameLineEdit = new QLineEdit(inputPage);
        productNameLineEdit->setObjectName(QString::fromUtf8("productNameLineEdit"));

        productFormLayout->setWidget(1, QFormLayout::FieldRole, productNameLineEdit);

        priceLabel = new QLabel(inputPage);
        priceLabel->setObjectName(QString::fromUtf8("priceLabel"));

        productFormLayout->setWidget(2, QFormLayout::LabelRole, priceLabel);

        priceLineEdit = new QLineEdit(inputPage);
        priceLineEdit->setObjectName(QString::fromUtf8("priceLineEdit"));

        productFormLayout->setWidget(2, QFormLayout::FieldRole, priceLineEdit);

        stockLabel = new QLabel(inputPage);
        stockLabel->setObjectName(QString::fromUtf8("stockLabel"));

        productFormLayout->setWidget(3, QFormLayout::LabelRole, stockLabel);

        stockLineEdit = new QLineEdit(inputPage);
        stockLineEdit->setObjectName(QString::fromUtf8("stockLineEdit"));

        productFormLayout->setWidget(3, QFormLayout::FieldRole, stockLineEdit);


        verticalLayout->addLayout(productFormLayout);

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
        searchPage->setGeometry(QRect(0, 0, 464, 306));
        verticalLayout_2 = new QVBoxLayout(searchPage);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        idHorizontalLayout = new QHBoxLayout();
        idHorizontalLayout->setObjectName(QString::fromUtf8("idHorizontalLayout"));
        searchComboBox = new QComboBox(searchPage);
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
        treeWidget = new QTreeWidget(splitter);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        splitter->addWidget(treeWidget);

        verticalLayout_3->addWidget(splitter);

#if QT_CONFIG(shortcut)
        productIdLabel->setBuddy(productIdLineEdit);
        productNameLabel->setBuddy(productNameLineEdit);
        priceLabel->setBuddy(priceLineEdit);
        stockLabel->setBuddy(stockLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(ProductManagerForm);

        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ProductManagerForm);
    } // setupUi

    void retranslateUi(QWidget *ProductManagerForm)
    {
        ProductManagerForm->setWindowTitle(QCoreApplication::translate("ProductManagerForm", "Form", nullptr));
        productIdLabel->setText(QCoreApplication::translate("ProductManagerForm", "&ID", nullptr));
        productIdLineEdit->setText(QString());
        productNameLabel->setText(QCoreApplication::translate("ProductManagerForm", "&Name", nullptr));
        productNameLineEdit->setText(QString());
        priceLabel->setText(QCoreApplication::translate("ProductManagerForm", "Price", nullptr));
        stockLabel->setText(QCoreApplication::translate("ProductManagerForm", "Stock", nullptr));
        addPushButton->setText(QCoreApplication::translate("ProductManagerForm", "Add", nullptr));
        modifyPushButton->setText(QCoreApplication::translate("ProductManagerForm", "Modify", nullptr));
        clearPushButton->setText(QCoreApplication::translate("ProductManagerForm", "Clear", nullptr));
        toolBox->setItemText(toolBox->indexOf(inputPage), QCoreApplication::translate("ProductManagerForm", "Input", nullptr));
        searchComboBox->setItemText(0, QCoreApplication::translate("ProductManagerForm", "ID", nullptr));
        searchComboBox->setItemText(1, QCoreApplication::translate("ProductManagerForm", "Name", nullptr));
        searchComboBox->setItemText(2, QCoreApplication::translate("ProductManagerForm", "Price", nullptr));
        searchComboBox->setItemText(3, QCoreApplication::translate("ProductManagerForm", "Stock", nullptr));

        searchPushButton->setText(QCoreApplication::translate("ProductManagerForm", "Search", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = searchTreeWidget->headerItem();
        ___qtreewidgetitem->setText(3, QCoreApplication::translate("ProductManagerForm", "Stock", nullptr));
        ___qtreewidgetitem->setText(2, QCoreApplication::translate("ProductManagerForm", "Price", nullptr));
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ProductManagerForm", "Name", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ProductManagerForm", "ID", nullptr));
        toolBox->setItemText(toolBox->indexOf(searchPage), QCoreApplication::translate("ProductManagerForm", "Search", nullptr));
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->headerItem();
        ___qtreewidgetitem1->setText(3, QCoreApplication::translate("ProductManagerForm", "Stock", nullptr));
        ___qtreewidgetitem1->setText(2, QCoreApplication::translate("ProductManagerForm", "Price", nullptr));
        ___qtreewidgetitem1->setText(1, QCoreApplication::translate("ProductManagerForm", "Name", nullptr));
        ___qtreewidgetitem1->setText(0, QCoreApplication::translate("ProductManagerForm", "ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProductManagerForm: public Ui_ProductManagerForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRODUCTMANAGERFORM_H
