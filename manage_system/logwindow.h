#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include <QTranslator>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

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
    void showmainwindow();
private:
    Ui::logwindow *ui;
    QFormLayout* layout;
    QLineEdit* user;
    QLineEdit* password;
    QPushButton* login;
    QPushButton* cancel;
    QHBoxLayout* botton;
    QLabel *info;
};

#endif // LOGWINDOW_H
