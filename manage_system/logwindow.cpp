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
        info->setText("�˺Ż��������");
    }
}

void logwindow::clear()
{
    user -> clear();
    password -> clear();
}

void logwindow::dislogwindow()
{
    setWindowTitle("��¼");
    layout = new QFormLayout();
    user = new QLineEdit();
    user -> setPlaceholderText("������ѧ�Ż����Ա�˺�");
    QIntValidator * pIntVld = new QIntValidator(this);
    user -> setValidator(pIntVld);
    password = new QLineEdit();
    password -> setPlaceholderText("����������");
    password -> setEchoMode(QLineEdit::Password);
    login = new QPushButton();
    login -> setText("��¼");
    cancel = new QPushButton();
    cancel -> setText("���");
    botton = new QHBoxLayout();
    botton -> addWidget(login);
    botton -> addWidget(cancel);
    info = new QLabel();
    info -> setStyleSheet("color:red;");
    info -> setAlignment(Qt::AlignHCenter);
    layout -> addRow("�˺�", user);
    layout -> addRow("����", password);
    layout -> setSpacing(20);
    layout -> addRow(info);
    layout -> addRow(botton);
    setLayout(layout);
    show();
    connect(login, &QPushButton::clicked, this, &logwindow::TryLogin);
    connect(cancel, &QPushButton::clicked, this, &logwindow::clear);
}
