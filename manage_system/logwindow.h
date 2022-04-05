#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QWidget>
#include <QTranslator>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>

namespace Ui {
class logwindow;
}

class logwindow : public QWidget
{
    Q_OBJECT

public:
    void TryLogin();
    explicit logwindow(QWidget *parent = nullptr);
    ~logwindow();
    void dislogwindow();
private:
    Ui::logwindow *ui;
    QFormLayout* layout;
    QLineEdit* user;
    QLineEdit* password;
    QPushButton* login;
    QPushButton* cancel;
    QHBoxLayout* botton;
};

#endif // LOGWINDOW_H
