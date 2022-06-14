/********************************************************************************
** Form generated from reading UI file 'addtest.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTEST_H
#define UI_ADDTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addtest
{
public:

    void setupUi(QWidget *addtest)
    {
        if (addtest->objectName().isEmpty())
            addtest->setObjectName(QString::fromUtf8("addtest"));
        addtest->resize(400, 300);

        retranslateUi(addtest);

        QMetaObject::connectSlotsByName(addtest);
    } // setupUi

    void retranslateUi(QWidget *addtest)
    {
        addtest->setWindowTitle(QCoreApplication::translate("addtest", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addtest: public Ui_addtest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTEST_H
