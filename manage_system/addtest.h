#ifndef ADDTEST_H
#define ADDTEST_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QDate>

namespace Ui {
class addtest;
}

class addtest : public QWidget
{
    Q_OBJECT

public:
    explicit addtest(int now_year, QWidget *parent = nullptr);
    ~addtest();
    void set_place(QStringList name);

private:
    Ui::addtest *ui;
    QLabel* test_name_title, *test_time_title, *test_place_title, *nian_name, *yue_name,
            *ri_name, *shi_name, *fen_name, *state, *test_last_title;
    QLineEdit* test_name_edit, *test_last;
    QComboBox* nian, *yue, *ri, *shi, *fen, *test_place;
    QPushButton* complete, *cancel;
    QGridLayout* main_info_layout;
    QHBoxLayout* test_time_layout, *button_layout;
    QVBoxLayout* main_layout;
    int now_year;
    void set_time();
    void change_day();
    void clear_content();
};

#endif // ADDTEST_H
