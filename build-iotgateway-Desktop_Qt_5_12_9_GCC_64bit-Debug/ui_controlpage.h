/********************************************************************************
** Form generated from reading UI file 'controlpage.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTROLPAGE_H
#define UI_CONTROLPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ControlPage
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *ledbtn;
    QPushButton *buzzerbtn;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *ControlPage)
    {
        if (ControlPage->objectName().isEmpty())
            ControlPage->setObjectName(QString::fromUtf8("ControlPage"));
        ControlPage->resize(811, 605);
        horizontalLayout = new QHBoxLayout(ControlPage);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        ledbtn = new QPushButton(ControlPage);
        ledbtn->setObjectName(QString::fromUtf8("ledbtn"));

        horizontalLayout->addWidget(ledbtn);

        buzzerbtn = new QPushButton(ControlPage);
        buzzerbtn->setObjectName(QString::fromUtf8("buzzerbtn"));

        horizontalLayout->addWidget(buzzerbtn);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        retranslateUi(ControlPage);

        QMetaObject::connectSlotsByName(ControlPage);
    } // setupUi

    void retranslateUi(QWidget *ControlPage)
    {
        ControlPage->setWindowTitle(QApplication::translate("ControlPage", "Form", nullptr));
        ledbtn->setText(QApplication::translate("ControlPage", "led\345\205\263\351\227\255", nullptr));
        buzzerbtn->setText(QApplication::translate("ControlPage", "\350\234\202\351\270\243\345\231\250\345\205\263\351\227\255", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ControlPage: public Ui_ControlPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLPAGE_H
