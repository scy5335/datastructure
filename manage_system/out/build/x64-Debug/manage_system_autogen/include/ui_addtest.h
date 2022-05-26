/********************************************************************************
** Form generated from reading UI file 'addtest.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTEST_H
#define UI_ADDTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addtest
{
public:

    void setupUi(QWidget *addtest)
    {
        if (addtest->objectName().isEmpty())
            addtest->setObjectName(QStringLiteral("addtest"));
        addtest->resize(400, 300);

        retranslateUi(addtest);

        QMetaObject::connectSlotsByName(addtest);
    } // setupUi

    void retranslateUi(QWidget *addtest)
    {
        addtest->setWindowTitle(QApplication::translate("addtest", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class addtest: public Ui_addtest {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTEST_H
