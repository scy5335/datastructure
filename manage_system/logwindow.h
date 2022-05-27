#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include <QTranslator>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>
#include <QStackedLayout>
#include <QComboBox>
#include <QMessageBox>
#include "student.h"
#include "manager.h"
#include <QIntValidator>

namespace Ui {
class logwindow;
}

class logwindow : public QWidget
{
    Q_OBJECT

public:
    void TryLogin();
    void clear();
    explicit logwindow(QWidget *parent = nullptr);
    ~logwindow();
    void dislogwindow();
signals:
    void showmainwindow(int user_id);
    void showmanagewindow();
private:
    Ui::logwindow *ui;
    QFormLayout* layout, *register_layout;
    QLineEdit* user;
    QLineEdit* password, *password1, *password2, *user_id;
    QPushButton* login, *confirm_register;
    QPushButton* cancel, *to_regis_page, *to_login_page;
    QHBoxLayout* botton;
    QLabel *info;
    QStackedLayout *login_stack;
    QComboBox *user_class;
    QWidget *page[2];
    void to_regis();
    void to_login();
    void try_regis();
};

#endif // LOGWINDOW_H
