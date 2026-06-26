/********************************************************************************
** Form generated from reading UI file 'historypage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORYPAGE_H
#define UI_HISTORYPAGE_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HistoryPage
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *dateTimeEdit_2;
    QPushButton *pushButton;
    QTableWidget *tableWidget;
    QChartView *widget;

    void setupUi(QWidget *HistoryPage)
    {
        if (HistoryPage->objectName().isEmpty())
            HistoryPage->setObjectName(QString::fromUtf8("HistoryPage"));
        HistoryPage->resize(1302, 668);
        verticalLayout = new QVBoxLayout(HistoryPage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        comboBox = new QComboBox(HistoryPage);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout->addWidget(comboBox);

        dateTimeEdit = new QDateTimeEdit(HistoryPage);
        dateTimeEdit->setObjectName(QString::fromUtf8("dateTimeEdit"));
        dateTimeEdit->setCalendarPopup(true);

        horizontalLayout->addWidget(dateTimeEdit);

        dateTimeEdit_2 = new QDateTimeEdit(HistoryPage);
        dateTimeEdit_2->setObjectName(QString::fromUtf8("dateTimeEdit_2"));
        dateTimeEdit_2->setCalendarPopup(true);

        horizontalLayout->addWidget(dateTimeEdit_2);

        pushButton = new QPushButton(HistoryPage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(HistoryPage);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        widget = new QChartView(HistoryPage);
        widget->setObjectName(QString::fromUtf8("widget"));

        verticalLayout->addWidget(widget);

        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 5);

        retranslateUi(HistoryPage);

        QMetaObject::connectSlotsByName(HistoryPage);
    } // setupUi

    void retranslateUi(QWidget *HistoryPage)
    {
        HistoryPage->setWindowTitle(QApplication::translate("HistoryPage", "Form", nullptr));
        comboBox->setItemText(0, QApplication::translate("HistoryPage", "\346\270\251\345\272\246", nullptr));
        comboBox->setItemText(1, QApplication::translate("HistoryPage", "\346\271\277\345\272\246", nullptr));
        comboBox->setItemText(2, QApplication::translate("HistoryPage", "\347\203\237\351\233\276", nullptr));
        comboBox->setItemText(3, QApplication::translate("HistoryPage", "\347\272\242\345\244\226", nullptr));

        pushButton->setText(QApplication::translate("HistoryPage", "\346\237\245\350\257\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistoryPage: public Ui_HistoryPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORYPAGE_H
