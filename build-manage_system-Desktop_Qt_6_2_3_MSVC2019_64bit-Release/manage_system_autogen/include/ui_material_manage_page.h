/********************************************************************************
** Form generated from reading UI file 'material_manage_page.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIAL_MANAGE_PAGE_H
#define UI_MATERIAL_MANAGE_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_material_manage_page
{
public:

    void setupUi(QWidget *material_manage_page)
    {
        if (material_manage_page->objectName().isEmpty())
            material_manage_page->setObjectName(QString::fromUtf8("material_manage_page"));
        material_manage_page->resize(400, 300);

        retranslateUi(material_manage_page);

        QMetaObject::connectSlotsByName(material_manage_page);
    } // setupUi

    void retranslateUi(QWidget *material_manage_page)
    {
        material_manage_page->setWindowTitle(QCoreApplication::translate("material_manage_page", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class material_manage_page: public Ui_material_manage_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIAL_MANAGE_PAGE_H
