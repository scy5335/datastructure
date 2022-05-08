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
#include <QLineEdit>
#include <QGridLayout>
#include <QFormLayout>
#include "mygraphview.h"
#include "addtest.h"
#include "addhomework.h"

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
    void display_student_page();
    void display_manage_page();

private:
    Ui::mainwindow *ui;
    QHBoxLayout* layout, *time_button_layout, *lesson_layout, *calendar_layout, *guide_layout,
                *place_layout, *guide_button_layout, *lesson_jump_button, *info_layout;
    QVBoxLayout* time_clock_layout, *calendar_main_layout, *guide_mod_layout;
    QPushButton* accelerate, *slow_down, *to_calendar_module1, *to_calendar_module2,
                *to_guide_module1, *to_guide_module2, *to_lesson_module1, *to_lesson_module2,
                *place_select_button, *place_clear_button, *start_guide, *homework_submit;
    QLabel* timelabel, *speedlabel, *calendar_title, *guide_time, *query_label, *answer_label,
            *lesson_name, *lesson_place, *lesson_teacher, *test_label, *homework_label;
    QListWidget* calendar_list, *test_info, *homework_info;
    QTableWidget* lessontable;
    QWidget* page[3];
    time_form* main_time_form;
    myGraphView* map;
    QStackedWidget* stackwidget;
    QListWidget* query_list, *answer_list;
    QComboBox* place_select;
    QFormLayout* lesson_detail_info_layout, *lesson_message_button;
    void student_page_set();
    void manage_page_set();
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

    //manage
    QComboBox* class_select, *place_message;
    QLabel* ask_class, *class_name_title, *place_message_title, *teacher_name_title, *test_title,
            *homework_title;
    QGridLayout* message_layout, *button_grid;
    QLineEdit* teacher_message, *class_name;
    QHBoxLayout* class_layout, *detail_info_layout;
    QVBoxLayout* manage_main_layout, *class_detail_layout;
    QPushButton* add_lesson, *delete_lesson, *test_add, *homework_add, *homework_del, *test_del;
    QListWidget* test_list, *homework_list;
    addtest* add_test_page;
    addhomework* add_homework_page;
    void test_add_page();
    void homework_add_page();
};

#endif // MAINWINDOW_H
