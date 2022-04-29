#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>

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

QTime time_form::program_time = QTime::currentTime();

void mainwindow::display(){
    pageset();
    this -> show();
}

void mainwindow::pageset(){
    setWindowTitle("学生主页");
    main_time_form = new time_form();
    main_time_form -> set_time();
    set_lesson_page();
    set_calendar_page();
    set_guide_page();
    page[0] = new QWidget();
    page[0] -> setLayout(lesson_layout);
    page[1] = new QWidget();
    page[1] -> setLayout(calendar_layout);
    page[2] = new QWidget();
    page[2] -> setLayout(guide_layout);
    stackwidget = new QStackedWidget();
    stackwidget -> addWidget(page[0]);
    stackwidget -> addWidget(page[1]);
    stackwidget -> addWidget(page[2]);
    layout = new QHBoxLayout();
    QFont ft;
    ft.setPointSize(30);
    timelabel = new QLabel();
    speedlabel = new QLabel();
    timelabel -> setFont(ft);
    timelabel -> setText(main_time_form -> get_time(). toString("HH:mm")); 
    timelabel -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    speedlabel -> setText("当前速度:10x");
    speedlabel -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    accelerate = new QPushButton();
    accelerate -> setText("加速");
    slow_down = new QPushButton();
    slow_down -> setText("减速");
    time_button_layout = new QHBoxLayout();
    time_button_layout -> addWidget(accelerate);
    time_button_layout -> addWidget(slow_down);
    time_clock_layout = new QVBoxLayout();
    time_clock_layout -> addWidget(timelabel);
    time_clock_layout -> addWidget(speedlabel);
    time_clock_layout -> addLayout(time_button_layout);
    layout -> addLayout(time_clock_layout);
    layout -> addWidget(stackwidget);
    setLayout(layout);
    connect(to_lesson_module1, &QPushButton::clicked, this, &mainwindow::switch_to_lesson_page);
    connect(to_lesson_module2, &QPushButton::clicked, this, &mainwindow::switch_to_lesson_page);
    connect(to_calendar_module1, &QPushButton::clicked, this, &mainwindow::switch_to_calendar_page);
    connect(to_calendar_module2, &QPushButton::clicked, this, &mainwindow::switch_to_calendar_page);
    connect(to_guide_module1, &QPushButton::clicked, this, &mainwindow::switch_to_guide_page);
    connect(to_guide_module2, &QPushButton::clicked, this, &mainwindow::switch_to_guide_page);
}

void mainwindow::set_lesson_page(){
    lessontable = new QTableWidget(14,7);
    lessontable -> setHorizontalHeaderLabels(QStringList()<<"星期一"<<"星期二"<<"星期三"<<
                                             "星期四"<<"星期五"<<"星期六"<<"星期天");
    lessontable -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
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
    to_calendar_module1 = new QPushButton();
    to_calendar_module1 -> setText("查看日程表");
    to_guide_module1 = new QPushButton();
    to_guide_module1 -> setText("导航页面");
    lesson_layout = new QHBoxLayout();
    lesson_layout -> addWidget(lessontable);
    lesson_layout -> addWidget(to_calendar_module1);
    lesson_layout -> addWidget(to_guide_module1);
}

void mainwindow::set_calendar_page(){
    calendar_title = new QLabel();
    calendar_title -> setText("日程表");
    calendar_list = new QListWidget();
    calendar_main_layout = new QVBoxLayout();
    calendar_main_layout -> addWidget(calendar_title);
    calendar_main_layout -> addWidget(calendar_list);
    to_lesson_module1 = new QPushButton();
    to_lesson_module1 -> setText("查看课程表");
    to_guide_module2 = new QPushButton();
    to_guide_module2 -> setText("导航页面");
    calendar_layout = new QHBoxLayout();
    calendar_layout -> addLayout(calendar_main_layout);
    calendar_layout -> addWidget(to_lesson_module1);
    calendar_layout -> addWidget(to_guide_module2);
}

void mainwindow::set_guide_page(){
    map = new myGraphView();
    map -> setSceneRect(map -> rect());
    to_lesson_module2 = new QPushButton();
    to_lesson_module2 -> setText("查看课程表");
    to_calendar_module2 = new QPushButton();
    to_calendar_module2 -> setText("查看日程表");

    guide_button_layout =new QHBoxLayout();
    guide_button_layout -> addWidget(to_lesson_module2);
    guide_button_layout -> addWidget(to_calendar_module2);

    place_select = new QComboBox();
    place_select -> addItems(map -> GetVecName());
    place_select -> setCurrentIndex(-1);
    place_select_button = new QPushButton();
    place_select_button -> setText("确认");
    place_clear_button = new QPushButton();
    place_clear_button -> setText("清除");
    place_layout =new QHBoxLayout();
    place_layout -> addWidget(place_select_button);
    place_layout -> addWidget(place_clear_button);

    guide_mod_layout = new QVBoxLayout();
    query_list = new QListWidget();
    query_list -> setFixedWidth(200);
    answer_list = new QListWidget();
    answer_list -> setFixedWidth(200);
    guide_time = new QLabel();
    start_guide = new QPushButton();
    start_guide -> setText("开始导航");
    guide_mod_layout -> addWidget(query_list);
    guide_mod_layout -> addWidget(answer_list);
    guide_mod_layout -> addWidget(guide_time);
    guide_mod_layout -> addWidget(place_select);
    guide_mod_layout -> addLayout(place_layout);
    guide_mod_layout -> addWidget(start_guide);
    guide_mod_layout -> addLayout(guide_button_layout);

    guide_layout = new QHBoxLayout();
    guide_layout -> addWidget(map);
    guide_layout -> addLayout(guide_mod_layout);
    connect(place_select_button, &QPushButton::clicked, this, &mainwindow::send_place_info);
    connect(start_guide, &QPushButton::clicked, this, &mainwindow::get_guide_result);
    connect(place_clear_button, &QPushButton::clicked, this, &mainwindow::clear_guide_list);
    connect(map, &myGraphView::selected, this, &mainwindow::set_place_info);
}

void mainwindow::send_place_info(){
    if (place_select -> currentIndex() == -1)
        return;
    query_list -> addItem(place_select->currentText());
}

void mainwindow::get_guide_result(){
    QStringList qsl;
    int cnt = query_list -> count();
    for (int i = 0; i < cnt; i++){
        qsl.append((query_list->item(i))->text());
    }
    answer_list -> clear();
    double totminutes = 0;
    answer_list -> addItems(map -> maingraph -> FindPath(qsl, totminutes));
    QString estimate_time = "预计用时 " + QString::number(ceil(totminutes))+" 分钟";
    guide_time -> setText(estimate_time);
}

void mainwindow::clear_guide_list(){
    query_list -> clear();
    guide_time -> clear();
}

void mainwindow::set_place_info(int id){
    place_select -> setCurrentIndex(id);
}

void mainwindow::switch_to_guide_page(){
    stackwidget -> setCurrentIndex(2);
}

void mainwindow::switch_to_calendar_page(){
    stackwidget -> setCurrentIndex(1);
}

void mainwindow::switch_to_lesson_page(){
    stackwidget -> setCurrentIndex(0);
}

void time_form::set_time(){
    program_time = QTime::currentTime();
}


QTime time_form::get_time(){
    return program_time;
}
