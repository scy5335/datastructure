#include "addtest.h"
#include "ui_addtest.h"

addtest::addtest(int now_year, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addtest)
{
    ui->setupUi(this);
    setWindowTitle("考试添加");
    this -> now_year = now_year;
    test_name_title = new QLabel();
    test_name_title -> setText("考试名称");
    test_name_edit = new QLineEdit();
    test_time_title = new QLabel();
    test_time_title -> setText("考试时间");
    set_time();
    test_last_title = new QLabel();
    test_last_title -> setText("考试时长/分钟");
    test_last = new QLineEdit();
    QIntValidator * pIntVld = new QIntValidator(this);
    test_last -> setValidator(pIntVld);
    test_place_title = new QLabel();
    test_place_title -> setText("考试地点");
    test_place = new QComboBox();
    main_info_layout = new QGridLayout();
    main_info_layout -> addWidget(test_name_title, 0, 0);
    main_info_layout -> addWidget(test_name_edit, 0, 1);
    main_info_layout -> addWidget(test_time_title, 1, 0);
    main_info_layout -> addLayout(test_time_layout, 1, 1);
    main_info_layout -> addWidget(test_last_title, 2, 0);
    main_info_layout -> addWidget(test_last, 2, 1);
    main_info_layout -> addWidget(test_place_title, 3, 0);
    main_info_layout -> addWidget(test_place, 3, 1);
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
    connect(nian, &QComboBox::currentIndexChanged, this, &addtest::change_day);
    connect(yue, &QComboBox::currentIndexChanged, this, &addtest::change_day);
    connect(complete, &QPushButton::clicked, this, &addtest::try_upload_test);
    connect(cancel, &QPushButton::clicked, this, &addtest::clear_content);
    setLayout(main_layout);
}

void addtest::try_upload_test(){
    if (test_name_edit -> text() == "")
        QMessageBox::critical(this, "添加错误", "请输入考试名称");
    if (ri -> currentIndex() == -1 || shi -> currentIndex() == -1 || fen -> currentIndex() == -1)
        QMessageBox::critical(this, "添加错误", "请输入完整的考试时间");
    if (test_last -> text() == "")
        QMessageBox::critical(this, "添加错误", "请输入考试时长");
    if (test_place -> currentIndex() == -1)
        QMessageBox::critical(this, "添加错误", "请输入考试地点");
    MyTime start_time = MyTime(nian -> currentText().toInt(), yue -> currentText().toInt(),
                               ri -> currentText().toInt(), shi -> currentText().toInt(),
                               fen -> currentText().toInt());
    emit test_upload(test_name_edit -> text(), start_time, test_place -> currentIndex(), test_last -> text().toInt());
}

void addtest::set_time(){
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
    test_time_layout = new QHBoxLayout();
    test_time_layout -> addWidget(nian);
    test_time_layout -> addWidget(nian_name);
    test_time_layout -> addWidget(yue);
    test_time_layout -> addWidget(yue_name);
    test_time_layout -> addWidget(ri);
    test_time_layout -> addWidget(ri_name);
    test_time_layout -> addWidget(shi);
    test_time_layout -> addWidget(shi_name);
    test_time_layout -> addWidget(fen);
    test_time_layout -> addWidget(fen_name);
}

void addtest::change_day(){
    if (nian -> currentIndex() == -1 || yue -> currentIndex() == -1) return;
    QDate date(nian -> currentText().toInt(), yue -> currentText().toInt(), 1);
    ri -> clear();
    int day = date.daysInMonth();
    for (int i = 1; i <= day; i++)
        ri -> addItem(QString::number(i));
    ri -> setCurrentIndex(-1);
}

void addtest::clear_content(){
    test_name_edit -> clear();
    nian -> setCurrentIndex(-1);
    yue -> setCurrentIndex(-1);
    ri -> setCurrentIndex(-1);
    shi -> setCurrentIndex(-1);
    fen -> setCurrentIndex(-1);
    test_place -> setCurrentIndex(-1);
}

void addtest::set_place(QStringList name){
    test_place -> addItems(name);
    test_place -> setCurrentIndex(-1);
}

addtest::~addtest()
{
    delete ui;
}
