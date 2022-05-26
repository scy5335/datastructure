#include "addhomework.h"
#include "ui_addhomework.h"

addhomework::addhomework(int now_year, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addhomework)
{
    ui->setupUi(this);
    setWindowTitle("作业添加");
    this -> now_year = now_year;
    homework_name_title = new QLabel();
    homework_name_title -> setText("作业名称");
    homework_name_edit = new QLineEdit();
    homework_time_title = new QLabel();
    homework_time_title -> setText("截至时间");
    homework_detail = new QLabel();
    homework_detail -> setText("作业详情");
    homework_describption = new QLineEdit();
    set_time();
    main_info_layout = new QGridLayout();
    main_info_layout -> addWidget(homework_name_title, 0, 0);
    main_info_layout -> addWidget(homework_name_edit, 0, 1);
    main_info_layout -> addWidget(homework_detail, 1, 0);
    main_info_layout -> addWidget(homework_describption, 1, 1);
    main_info_layout -> addWidget(homework_time_title, 2, 0);
    main_info_layout -> addLayout(homework_time_layout, 2, 1);
    complete = new QPushButton();
    complete -> setText("确定");
    cancel = new QPushButton();
    cancel -> setText("重置");
    button_layout = new QHBoxLayout();
    button_layout -> addWidget(complete);
    button_layout -> addWidget(cancel);
    state = new QLabel();
    state -> setFixedHeight(60);
    main_layout = new QVBoxLayout();
    main_layout -> addLayout(main_info_layout);
    main_layout -> addWidget(state);
    main_layout -> addLayout(button_layout);
    connect(nian, QOverload<const QString&>::of(&QComboBox::currentIndexChanged), this, &addhomework::change_day);
    connect(yue, QOverload<const QString&>::of(&QComboBox::currentIndexChanged), this, &addhomework::change_day);
    connect(cancel, &QPushButton::clicked, this, &addhomework::clear_content);
    setLayout(main_layout);
}

addhomework::~addhomework()
{
    delete ui;
}

void addhomework::set_time(){
    nian = new QComboBox();
    for (int i = now_year; i <= now_year + 5; i++)
        nian -> addItem(QString::number(i));
    nian -> setCurrentIndex(-1);
    nian_name = new QLabel();
    nian_name -> setText("年");
    yue = new QComboBox();
    for (int i = 1; i <= 12; i++)
        yue -> addItem(QString::number(i));
    yue -> setCurrentIndex(-1);
    yue_name = new QLabel();
    yue_name -> setText("月");
    ri = new QComboBox();
    ri_name = new QLabel();
    ri_name -> setText("日");
    shi = new QComboBox();
    for (int i = 0; i <= 23; i++)
        shi -> addItem(QString::number(i));
    shi -> setCurrentIndex(-1);
    shi_name = new QLabel();
    shi_name -> setText("时");
    fen = new QComboBox();
    for (int i = 0; i <= 59; i++)
        fen -> addItem(QString::number(i));
    fen -> setCurrentIndex(-1);
    fen_name = new QLabel();
    fen_name -> setText("分");
    homework_time_layout = new QHBoxLayout();
    homework_time_layout -> addWidget(nian);
    homework_time_layout -> addWidget(nian_name);
    homework_time_layout -> addWidget(yue);
    homework_time_layout -> addWidget(yue_name);
    homework_time_layout -> addWidget(ri);
    homework_time_layout -> addWidget(ri_name);
    homework_time_layout -> addWidget(shi);
    homework_time_layout -> addWidget(shi_name);
    homework_time_layout -> addWidget(fen);
    homework_time_layout -> addWidget(fen_name);
}

void addhomework::change_day(){
    if (nian -> currentIndex() == -1 || yue -> currentIndex() == -1) return;
    QDate date(nian -> currentText().toInt(), yue -> currentText().toInt(), 1);
    ri -> clear();
    int day = date.daysInMonth();
    for (int i = 1; i <= day; i++)
        ri -> addItem(QString::number(i));
    ri -> setCurrentIndex(-1);
}

void addhomework::clear_content(){
    homework_name_edit -> clear();
    nian -> setCurrentIndex(-1);
    yue -> setCurrentIndex(-1);
    ri -> setCurrentIndex(-1);
    shi -> setCurrentIndex(-1);
    fen -> setCurrentIndex(-1);
}
