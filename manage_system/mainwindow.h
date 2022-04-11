#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTime>
#include <QLabel>

class time_form
{

public:
    void set_time();
    QTime get_time();

private:
    static QTime pro_time;
};

namespace Ui {
class mainwindow;
}

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    explicit mainwindow(QWidget *parent = nullptr);
    ~mainwindow();
    void display();

private:
    Ui::mainwindow *ui;
    void pageset();
    QHBoxLayout* layout;
    QTableWidget* lessontable;
    QLabel* timelabel;
    time_form* main_time_form;
};

#endif // MAINWINDOW_H
