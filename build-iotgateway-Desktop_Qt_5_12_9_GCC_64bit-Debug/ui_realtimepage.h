/********************************************************************************
** Form generated from reading UI file 'realtimepage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REALTIMEPAGE_H
#define UI_REALTIMEPAGE_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RealtimePage
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *humLabel;
    QLabel *pirLabel;
    QLabel *smokeLabel;
    QLabel *tempLabel;
    QChartView *chartview;

    void setupUi(QWidget *RealtimePage)
    {
        if (RealtimePage->objectName().isEmpty())
            RealtimePage->setObjectName(QString::fromUtf8("RealtimePage"));
        RealtimePage->resize(1167, 684);
        verticalLayout = new QVBoxLayout(RealtimePage);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        humLabel = new QLabel(RealtimePage);
        humLabel->setObjectName(QString::fromUtf8("humLabel"));

        gridLayout->addWidget(humLabel, 0, 0, 1, 1);

        pirLabel = new QLabel(RealtimePage);
        pirLabel->setObjectName(QString::fromUtf8("pirLabel"));

        gridLayout->addWidget(pirLabel, 0, 1, 1, 1);

        smokeLabel = new QLabel(RealtimePage);
        smokeLabel->setObjectName(QString::fromUtf8("smokeLabel"));

        gridLayout->addWidget(smokeLabel, 0, 2, 1, 1);

        tempLabel = new QLabel(RealtimePage);
        tempLabel->setObjectName(QString::fromUtf8("tempLabel"));

        gridLayout->addWidget(tempLabel, 0, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        chartview = new QChartView(RealtimePage);
        chartview->setObjectName(QString::fromUtf8("chartview"));

        verticalLayout->addWidget(chartview);


        retranslateUi(RealtimePage);

        QMetaObject::connectSlotsByName(RealtimePage);
    } // setupUi

    void retranslateUi(QWidget *RealtimePage)
    {
        RealtimePage->setWindowTitle(QApplication::translate("RealtimePage", "Form", nullptr));
        humLabel->setText(QApplication::translate("RealtimePage", "TextLabel", nullptr));
        pirLabel->setText(QApplication::translate("RealtimePage", "TextLabel", nullptr));
        smokeLabel->setText(QApplication::translate("RealtimePage", "TextLabel", nullptr));
        tempLabel->setText(QApplication::translate("RealtimePage", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RealtimePage: public Ui_RealtimePage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REALTIMEPAGE_H
