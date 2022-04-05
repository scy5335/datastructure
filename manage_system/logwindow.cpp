#include "logwindow.h"
#include "ui_logwindow.h"

logwindow::logwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::logwindow)
{
    ui->setupUi(this);
}

logwindow::~logwindow()
{
    delete ui;
}

void logwindow::TryLogin()
{
    if (user -> text() == password -> text()){
        this->hide();
        emit showmainwindow();
    }
    else {
        info->setText("账号或密码错误");
    }
}

void logwindow::clear()
{
    user -> clear();
    password -> clear();
}

void logwindow::dislogwindow()
{
    setWindowTitle("登录");
    layout = new QFormLayout();
    user = new QLineEdit();
    user -> setPlaceholderText("请输入账号");
    password = new QLineEdit();
    password -> setPlaceholderText("请输入密码");
    password -> setEchoMode(QLineEdit::Password);
    login = new QPushButton();
    login -> setText("登录");
    cancel = new QPushButton();
    cancel -> setText("清除");
    botton = new QHBoxLayout();
    botton -> addWidget(login);
    botton -> addWidget(cancel);
    info = new QLabel();
    info -> setStyleSheet("color:red;");
    info -> setAlignment(Qt::AlignHCenter);
    layout -> addRow("账号", user);
    layout -> addRow("密码", password);
    layout -> setSpacing(20);
    layout -> addRow(info);
    layout -> addRow(botton);
    setLayout(layout);
    show();
    connect(login, &QPushButton::clicked, this, &logwindow::TryLogin);
    connect(cancel, &QPushButton::clicked, this, &logwindow::clear);
}