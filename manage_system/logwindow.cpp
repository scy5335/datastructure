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
    if (Student::login(user -> text().toInt(), password -> text().toLocal8Bit().data())){
        this->hide();
        emit showmainwindow(user -> text().toInt());
    }
    else if (user -> text() == "0" && Manager::login(password -> text().toLocal8Bit().data())){
        this->hide();
        emit showmanagewindow();
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
    user -> setPlaceholderText("请输入学号或管理员账号");
    QIntValidator * pIntVld = new QIntValidator(this);
    user -> setValidator(pIntVld);
    password = new QLineEdit();
    password -> setPlaceholderText("请输入密码");
    password -> setEchoMode(QLineEdit::Password);
    login = new QPushButton();
    login -> setText("登录");
    cancel = new QPushButton();
    cancel -> setText("清除");
    to_regis_page = new QPushButton();
    to_regis_page -> setText("注册");
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
    layout -> addRow(to_regis_page);
    login_stack = new QStackedLayout();
    page[0] = new QWidget();
    page[0]->setLayout(layout);
    login_stack -> addWidget(page[0]);
    user_id = new QLineEdit();
    user_id -> setPlaceholderText("请输入学号");
    user_id -> setValidator(pIntVld);
    password1 = new QLineEdit();
    password1 -> setPlaceholderText("请输入密码");
    password1 -> setEchoMode(QLineEdit::Password);
    password2 = new QLineEdit();
    password2 -> setPlaceholderText("请输入密码");
    password2 -> setEchoMode(QLineEdit::Password);
    user_class = new QComboBox();
    for (int i = 2020211301; i<= 2020211310; i++)
        user_class -> addItem(QString::number(i));
    confirm_register = new QPushButton();
    confirm_register -> setText("确认注册");
    to_login_page = new QPushButton();
    to_login_page -> setText("返回");
    register_layout = new QFormLayout();
    register_layout -> addRow("账号", user_id);
    register_layout -> addRow("密码", password1);
    register_layout -> addRow("确认密码", password2);
    register_layout -> addRow("班级", user_class);
    register_layout -> addRow(confirm_register);
    register_layout -> addRow(to_login_page);
    page[1] = new QWidget();
    page[1] -> setLayout(register_layout);
    login_stack -> addWidget(page[1]);
    login_stack -> setCurrentIndex(0);
    setLayout(login_stack);
    connect(confirm_register, &QPushButton::clicked, this, &logwindow::try_regis);
    connect(to_regis_page, &QPushButton::clicked, this, &logwindow::to_regis);
    connect(to_login_page, &QPushButton::clicked, this, &logwindow::to_login);
    connect(login, &QPushButton::clicked, this, &logwindow::TryLogin);
    connect(cancel, &QPushButton::clicked, this, &logwindow::clear);
}

void logwindow::try_regis(){
    if (user_id -> text() == ""){
        QMessageBox::critical(this, "注册错误", "请输入学号");
        return;
    }
    if (password1 -> text() == ""){
        QMessageBox::critical(this, "注册错误", "请输入密码");
        return;
    }
    if (password2 -> text() == ""){
        QMessageBox::critical(this, "注册错误", "请再次输入密码");
        return;
    }
    if (password1 -> text() != password2 -> text()){
        QMessageBox::critical(this, "注册错误", "两次密码输入不一致");
        return;
    }
    if (user_class->currentIndex() == -1){
        QMessageBox::critical(this, "注册错误", "请选择班级");
        return;
    }
    if (Student::enroll(user_id -> text().toInt(), password1 -> text().toLocal8Bit().data(), user_class -> currentText().toInt())){
        QMessageBox::information(this, "注册成功", "注册成功");
        to_login();
    }
    else
        QMessageBox::critical(this, "注册错误", "注册失败");
}

void logwindow::to_regis(){
    setWindowTitle("注册");
    user_id -> clear();
    password1 -> clear();
    password2 -> clear();
    user_class -> setCurrentIndex(-1);
    login_stack -> setCurrentIndex(1);
}

void logwindow::to_login(){
    setWindowTitle("登录");
    user -> clear();
    password -> clear();
    info -> clear();
    login_stack ->setCurrentIndex(0);
}
