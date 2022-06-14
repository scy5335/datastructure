/********************************************************************************
** Form generated from reading UI file 'logwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGWINDOW_H
#define UI_LOGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_logwindow
{
public:

    void setupUi(QWidget *logwindow)
    {
        if (logwindow->objectName().isEmpty())
            logwindow->setObjectName(QString::fromUtf8("logwindow"));
        logwindow->resize(400, 300);

        retranslateUi(logwindow);

        QMetaObject::connectSlotsByName(logwindow);
    } // setupUi

    void retranslateUi(QWidget *logwindow)
    {
        logwindow->setWindowTitle(QCoreApplication::translate("logwindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class logwindow: public Ui_logwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGWINDOW_H
