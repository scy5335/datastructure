#ifndef ADDHOMEWORK_H
#define ADDHOMEWORK_H

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
class addhomework;
}

class addhomework : public QWidget
{
    Q_OBJECT

public:
    explicit addhomework(int now_year, QWidget *parent = nullptr);
    ~addhomework();

private:
    Ui::addhomework *ui;
    QLabel* homework_name_title, *homework_time_title, *nian_name, *yue_name, *homework_detail,
            *ri_name, *shi_name, *fen_name, *state;
    QLineEdit* homework_name_edit, *homework_describption;
    QComboBox* nian, *yue, *ri, *shi, *fen;
    QPushButton* complete, *cancel;
    QGridLayout* main_info_layout;
    QHBoxLayout* homework_time_layout, *button_layout;
    QVBoxLayout* main_layout;
    int now_year;
    void set_time();
    void change_day();
    void clear_content();
};

#endif // ADDHOMEWORK_H
