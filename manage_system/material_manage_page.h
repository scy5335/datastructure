#ifndef MATERIAL_MANAGE_PAGE_H
#define MATERIAL_MANAGE_PAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QFormLayout>
#include <QFileDialog>
#include <QLabel>

namespace Ui {
class material_manage_page;
}

class material_manage_page : public QWidget
{
    Q_OBJECT

public:
    explicit material_manage_page(QWidget *parent = nullptr);
    ~material_manage_page();

private:
    Ui::material_manage_page *ui;
    QLineEdit *description;
    QPushButton *file_select, *add_material, *del_material;
    QListWidget *material_list;
    QFormLayout *material_layout;
    QLabel *file_path;
    void file_select_page();
};

#endif // MATERIAL_MANAGE_PAGE_H
