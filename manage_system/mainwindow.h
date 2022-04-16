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
    void set_lesson_page();
    void set_calendar_page();
    void switch_to_calendar_page();
    void switch_to_lesson_page();

private:
    Ui::mainwindow *ui;
    void pageset();
    QHBoxLayout* layout, *time_button_layout, *lesson_layout, *calendar_layout;
    QVBoxLayout* time_clock_layout, *calendar_main_layout;
    QPushButton* accelerate, *slow_down, *to_calendar_module1, *to_calendar_module2,
                *to_guide_module1, *to_guide_module2, *to_lesson_module1, *to_lesson_module2;
    QLabel* timelabel, *speedlabel, *calendar_title;
    QListWidget* calendar_list;
    QTableWidget* lessontable;
    QWidget* page[3];
    time_form* main_time_form;
    QStackedWidget* stackwidget;
};

#endif // MAINWINDOW_H
