#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QTime>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QListWidget>
#include <QComboBox>
#include "mygraphview.h"

class time_form
{
public:
    static void set_time();
    static QTime get_time();

private:
    static QTime program_time;
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
    QHBoxLayout* layout, *time_button_layout, *lesson_layout, *calendar_layout, *guide_layout,
                *place_layout, *guide_button_layout;
    QVBoxLayout* time_clock_layout, *calendar_main_layout, *guide_mod_layout;
    QPushButton* accelerate, *slow_down, *to_calendar_module1, *to_calendar_module2,
                *to_guide_module1, *to_guide_module2, *to_lesson_module1, *to_lesson_module2,
                *place_select_button, *place_clear_button, *start_guide;
    QLabel* timelabel, *speedlabel, *calendar_title, *guide_time;
    QListWidget* calendar_list;
    QTableWidget* lessontable;
    QWidget* page[3];
    time_form* main_time_form;
    myGraphView* map;
    QStackedWidget* stackwidget;
    QListWidget* query_list, *answer_list;
    QComboBox* place_select;
    void pageset();
    void send_place_info();
    void set_place_info(int id);
    void switch_to_calendar_page();
    void switch_to_lesson_page();
    void switch_to_guide_page();
    void set_lesson_page();
    void set_calendar_page();
    void set_guide_page();
    void get_guide_result();
    void clear_guide_list();
};

#endif // MAINWINDOW_H
