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
    if (Student::login(user -> text().toInt(), password -> text().toStdString())){
        this->hide();
        emit showmainwindow(user -> text().toInt());
    }
    else if (user -> text() == "11" || password -> text() == "22"){
        this->hide();
        emit showmanagewindow();
    }
    else {
        info->setText("ÕËºÅ»òÃÜÂë´íÎó");
    }
}

void logwindow::clear()
{
    user -> clear();
    password -> clear();
}

void logwindow::dislogwindow()
{
    setWindowTitle("µÇÂ¼");
    layout = new QFormLayout();
    user = new QLineEdit();
    user -> setPlaceholderText("ÇëÊäÈëÑ§ºÅ»ò¹ÜÀíÔ±ÕËºÅ");
    QIntValidator * pIntVld = new QIntValidator(this);
    user -> setValidator(pIntVld);
    password = new QLineEdit();
    password -> setPlaceholderText("ÇëÊäÈëÃÜÂë");
    password -> setEchoMode(QLineEdit::Password);
    login = new QPushButton();
    login -> setText("µÇÂ¼");
    cancel = new QPushButton();
    cancel -> setText("Çå³ý");
    botton = new QHBoxLayout();
    botton -> addWidget(login);
    botton -> addWidget(cancel);
    info = new QLabel();
    info -> setStyleSheet("color:red;");
    info -> setAlignment(Qt::AlignHCenter);
    layout -> addRow("ÕËºÅ", user);
    layout -> addRow("ÃÜÂë", password);
    layout -> setSpacing(20);
    layout -> addRow(info);
    layout -> addRow(botton);
    setLayout(layout);
    show();
    connect(login, &QPushButton::clicked, this, &logwindow::TryLogin);
    connect(cancel, &QPushButton::clicked, this, &logwindow::clear);
}
