﻿#ifndef MATERIAL_MANAGE_PAGE_H
#define MATERIAL_MANAGE_PAGE_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QFormLayout>
#include <QFileDialog>
#include <QLabel>
#include <QHeaderView>

namespace Ui {
class material_manage_page;
}

class material_manage_page : public QWidget
{
    Q_OBJECT

public:
    explicit material_manage_page(QWidget *parent = nullptr);
    ~material_manage_page();
    void set_all_material(QStringList all_material_list);
    void initial_set();

private:
    Ui::material_manage_page *ui;
    QLineEdit *description, *data_name;
    QPushButton *file_select, *add_material, *del_material, *search;
    QTableWidget *material_list;
    QFormLayout *material_layout;
    QLabel *file_path;
    void file_select_page();
    void create_new_material();
    void try_delete_material();
    void filter_metarials();

signals:
    void add_new_material(QString description, QString file_path);
    void get_all_material(std::string dataname = "");
    void delete_material(QString description);
    void get_search_result(std::string dataname);
};

#endif // MATERIAL_MANAGE_PAGE_H
