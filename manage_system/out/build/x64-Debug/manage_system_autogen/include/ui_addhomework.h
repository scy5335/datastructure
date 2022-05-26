/********************************************************************************
** Form generated from reading UI file 'addhomework.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDHOMEWORK_H
#define UI_ADDHOMEWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addhomework
{
public:

    void setupUi(QWidget *addhomework)
    {
        if (addhomework->objectName().isEmpty())
            addhomework->setObjectName(QStringLiteral("addhomework"));
        addhomework->resize(400, 300);

        retranslateUi(addhomework);

        QMetaObject::connectSlotsByName(addhomework);
    } // setupUi

    void retranslateUi(QWidget *addhomework)
    {
        addhomework->setWindowTitle(QApplication::translate("addhomework", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class addhomework: public Ui_addhomework {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDHOMEWORK_H
