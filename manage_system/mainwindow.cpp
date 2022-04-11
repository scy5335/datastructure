#include "mainwindow.h"
#include "ui_mainwindow.h"

mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
}

mainwindow::~mainwindow()
{
    delete ui;
}

QTime time_form::pro_time = QTime::currentTime();

void mainwindow::display(){
    pageset();
    this -> show();
}

void mainwindow::pageset(){
    setWindowTitle("学生主页");
    lessontable = new QTableWidget(14,7);
    //lessontable -> horizontalHeader() -> setSectionResizeMode(QHeaderView::ResizeToContents);
    lessontable -> setHorizontalHeaderLabels(QStringList()<<"星期一"<<"星期二"<<"星期三"<<
                                             "星期四"<<"星期五"<<"星期六"<<"星期天");
    lessontable -> setVerticalHeaderLabels(QStringList()<<"1\n08:00\n08:45"<<
                                           "2\n08:50\n09:35"<<"3\n09:50\n10:35"<<
                                           "4\n10:40\n11:25"<<"5\n11:30\n12:15"<<
                                           "6\n13:00\n13:45"<<"7\n13:50\n14:35"<<
                                           "8\n14:45\n15:30"<<"9\n15:40\n16:25"<<
                                           "10\n16:35\n17:20"<<"11\n17:25\n18:10"<<
                                           "12\n18:30\n19:15"<<"13\n19:20\n20:05"<<
                                           "14\n20:10\n20:55");
    for (int i=0;i<lessontable -> rowCount();i++)
        lessontable -> setRowHeight(i, 60);
    main_time_form = new time_form();
    main_time_form -> set_time();
    layout = new QHBoxLayout();
    timelabel = new QLabel();
    timelabel -> setText(main_time_form -> get_time(). toString("HH:mm"));
    layout -> addWidget(timelabel);
    layout -> addWidget(lessontable);
    setLayout(layout);
}

void time_form::set_time(){
    pro_time = QTime::currentTime();
}

QTime time_form::get_time(){
    return pro_time;
}
