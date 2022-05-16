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
#include <QRadioButton>
#include <QCheckBox>
#include <QMessageBox>
#include <QButtonGroup>
#include "mygraphview.h"
#include "addtest.h"
#include "addhomework.h"
#include "material_manage_page.h"
#include "myclock.h"

class material_detail : public QWidget{
    Q_OBJECT

private:
    QListWidget *material_list;
    QHBoxLayout *layout;

public:
    material_detail(QWidget *parent = nullptr);
};

class alarm_page : public QWidget{
    Q_OBJECT

private:
    QTableWidget *alarm_list;
    QLabel *alarm_list_title, *day_name, *hour_minute;
    QLineEdit *alarm_description;
    QRadioButton *only_once, *every_day, *every_week;
    QPushButton *add_alarm, *del_alarm;
    QStackedWidget *day_widget;
    QWidget *page[2];
    QComboBox *hour, *minute;
    QHBoxLayout *radio_layout, *time_layout, *day_layout;
    QFormLayout *new_alarm_layout;
    QCheckBox *day[7];
    int alarm_id[maxLen], alarm_count;
    QButtonGroup *times_group;
    void hide_day();
    void display_day();
    void get_new_alarm();
    void set_type(int row, int column);
    void deletealarm();

signals:
    void create_new_alarm(Alarm a);
    void alarm_type_changed(int row);
    void delete_signal(int id);

public:
    alarm_page(QWidget *parent = nullptr);
    void set_alarm_list(MyClock *clock);
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
                *place_layout, *guide_button_layout, *lesson_jump_button, *info_layout,
                *s_calendar_time_layout, *e_calendar_time_layout, *activity_radio,
                *calendar_change_button, *mode_select;
    QVBoxLayout* time_clock_layout, *calendar_main_layout, *guide_mod_layout, *calendar_right;
    QPushButton* accelerate, *to_calendar_module1, *to_calendar_module2,
                *to_guide_module1, *to_guide_module2, *to_lesson_module1, *to_lesson_module2,
                *place_select_button, *place_clear_button, *start_guide, *homework_submit,
                *material_list_button, *calendar_add, *calendar_del, *alarm_modify;
    QLabel* timelabel, *datelabel, *speedlabel, *calendar_title, *guide_time, *query_label, *answer_label,
            *lesson_name, *lesson_place, *lesson_teacher, *test_label, *homework_label;
    QListWidget* calendar_list, *test_info, *homework_info;
    QTableWidget* lessontable, *alarm_list;
    QWidget* page[3], *time_widget;
    myGraphView* map;
    QStackedWidget* stackwidget;
    QListWidget* query_list, *answer_list;
    QComboBox* place_select, *calendar_place;
    QFormLayout* lesson_detail_info_layout, *lesson_message_button, *calendar_info_layout;
    material_detail *student_material_page;
    QComboBox* s_nian, *s_yue, *s_ri, *s_shi, *s_fen, *e_nian, *e_yue, *e_ri, *e_shi, *e_fen;
    QLabel *s_nian_name, *s_yue_name, *s_ri_name, *s_shi_name, *s_fen_name,
           *e_nian_name, *e_yue_name, *e_ri_name, *e_shi_name, *e_fen_name;
    QLineEdit *calendar_description, *speed_change;
    QRadioButton *single_activity, *group_activity, *time_first, *dist_only, *mix;
    QButtonGroup *mode_group;
    alarm_page *alarm_set_page;
    MyClock *Clock;
    int speed;

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
    void show_material_page();
    void set_time();
    void s_change_day();
    void e_change_day();
    void calendar_set_place(QStringList name);
    void show_alarm_page();
    void add_speed();
    void dec_speed();
    QString trans_time(MyTime);
    QString trans_date(MyTime);
    void time_change();
    void alarm_type_modify(int row);
    void alarm_flash();
    void clock_ring(string description);
    void add_alarm(Alarm a);
    void delete_alarm(int id);

    //manage
    QComboBox* class_select, *place_message;
    QLabel* ask_class, *class_name_title, *place_message_title, *teacher_name_title, *test_title,
            *homework_title;
    QGridLayout* message_layout, *button_grid;
    QLineEdit* teacher_message, *class_name;
    QHBoxLayout* class_layout, *detail_info_layout;
    QVBoxLayout* manage_main_layout, *class_detail_layout;
    QPushButton* add_lesson, *delete_lesson, *test_add, *homework_add, *homework_del, *test_del,
                 *material_manage_button;
    QListWidget* test_list, *homework_list;
    addtest* add_test_page;
    addhomework* add_homework_page;
    material_manage_page* material_page;
    void test_add_page();
    void homework_add_page();
    void material_add_page();
};

#endif // MAINWINDOW_H
