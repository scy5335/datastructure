#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFont>

mainwindow::mainwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwindow)
{
    ui->setupUi(this);
    add_test_page = NULL;
    add_homework_page = NULL;
}

mainwindow::~mainwindow()
{
    delete ui;
}

QTime time_form::program_time = QTime::currentTime();

void mainwindow::display_student_page(){
    student_page_set();
    this -> showMaximized();
}

void mainwindow::student_page_set(){
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

    lesson_name = new QLabel();
    lesson_teacher = new QLabel();
    lesson_place = new QLabel();
    test_label = new QLabel();
    test_label -> setText("考试信息");
    test_info = new QListWidget();
    homework_label = new QLabel();
    homework_label -> setText("作业信息");
    homework_submit = new QPushButton();
    homework_submit -> setText("提交作业");
    homework_info = new QListWidget();
    to_calendar_module1 = new QPushButton();
    to_calendar_module1 -> setText("查看日程表");
    to_guide_module1 = new QPushButton();
    to_guide_module1 -> setText("导航页面");
    lesson_jump_button = new QHBoxLayout();
    lesson_jump_button -> addWidget(to_calendar_module1);
    lesson_jump_button -> addWidget(to_guide_module1);
    lesson_detail_info_layout = new QFormLayout();
    lesson_detail_info_layout -> addRow("课程名称", lesson_name);
    lesson_detail_info_layout -> addRow("授课教师", lesson_teacher);
    lesson_detail_info_layout -> addRow("上课地点", lesson_place);
    lesson_detail_info_layout -> addRow(homework_submit);
    lesson_detail_info_layout -> addRow(test_label, homework_label);
    lesson_detail_info_layout -> addRow(test_info, homework_info);
    lesson_detail_info_layout -> addRow(lesson_jump_button);
    lesson_layout = new QHBoxLayout();
    lesson_layout -> addWidget(lessontable);
    lesson_layout -> addLayout(lesson_detail_info_layout);
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
    query_label = new QLabel();
    query_label -> setText("导航地点");
    query_list = new QListWidget();
    query_list -> setFixedWidth(200);
    answer_label = new QLabel();
    answer_label -> setText("导航结果");
    answer_list = new QListWidget();
    answer_list -> setFixedWidth(200);
    guide_time = new QLabel();
    start_guide = new QPushButton();
    start_guide -> setText("开始导航");
    guide_mod_layout -> addWidget(query_label);
    guide_mod_layout -> addWidget(query_list);
    guide_mod_layout -> addWidget(answer_label);
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

void mainwindow::display_manage_page(){
    manage_page_set();
    this -> show();
}

void mainwindow::manage_page_set(){
    setWindowTitle("管理员主页");
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
    ask_class = new QLabel();
    ask_class -> setText("请选择要进行操作的班级");
    class_select = new QComboBox();
    class_layout = new QHBoxLayout();
    class_layout -> addWidget(ask_class);
    class_layout -> addWidget(class_select);

    class_name_title = new QLabel();
    class_name_title -> setText("课程名");
    class_name = new QLineEdit();
    teacher_name_title = new QLabel();
    teacher_name_title -> setText("任课教师");
    teacher_message = new QLineEdit();
    place_message_title = new QLabel();
    place_message_title -> setText("上课地点");
    place_message = new QComboBox();
    map = new myGraphView();
    place_message -> addItems(map -> GetVecName());
    place_message -> setCurrentIndex(-1);
    add_lesson = new QPushButton();
    add_lesson -> setText("添加此课");
    delete_lesson = new QPushButton();
    delete_lesson -> setText("删除此课");
    test_add = new QPushButton();
    test_add -> setText("添加考试");
    test_del = new QPushButton();
    test_del -> setText("删除考试");
    test_title = new QLabel();
    test_title -> setText("考试信息");
    test_list = new QListWidget();
    homework_add = new QPushButton();
    homework_add -> setText("添加作业");
    homework_del = new QPushButton();
    homework_del -> setText("删除作业");
    homework_title = new QLabel();
    homework_title -> setText("作业信息");
    homework_list = new QListWidget();

    message_layout = new QGridLayout();
    message_layout -> addWidget(class_name_title, 0, 0);
    message_layout -> addWidget(class_name, 0, 1);
    message_layout -> addWidget(teacher_name_title, 1, 0);
    message_layout -> addWidget(teacher_message, 1, 1);
    message_layout -> addWidget(place_message_title, 2, 0);
    message_layout -> addWidget(place_message, 2, 1);
    button_grid = new QGridLayout();
    button_grid -> addWidget(add_lesson, 0, 0);
    button_grid -> addWidget(delete_lesson, 0, 1);
    button_grid -> addWidget(test_add, 1, 0);
    button_grid -> addWidget(homework_add, 1, 1);
    button_grid -> addWidget(test_del, 2, 0);
    button_grid -> addWidget(homework_del, 2, 1);
    button_grid -> addWidget(test_title, 3, 0);
    button_grid -> addWidget(homework_title, 3, 1);
    button_grid -> addWidget(test_list, 4, 0);
    button_grid -> addWidget(homework_list, 4, 1);
    class_detail_layout = new QVBoxLayout();
    class_detail_layout -> addLayout(message_layout);
    class_detail_layout -> addLayout(button_grid);
    detail_info_layout = new QHBoxLayout();
    detail_info_layout -> addWidget(lessontable);
    detail_info_layout -> addLayout(class_detail_layout);
    manage_main_layout = new QVBoxLayout();
    manage_main_layout -> addLayout(class_layout);
    manage_main_layout -> addLayout(detail_info_layout);
    setLayout(manage_main_layout);
    connect(test_add, &QPushButton::clicked, this, &mainwindow::test_add_page);
    connect(homework_add, &QPushButton::clicked, this, &mainwindow::homework_add_page);
}

void mainwindow::test_add_page(){
    if (add_test_page != NULL) delete add_test_page;
    add_test_page = new addtest();
    add_test_page -> set_place(map -> GetVecName());
    add_test_page -> show();
}

void mainwindow::homework_add_page(){
    if (add_homework_page != NULL) delete add_homework_page;
    add_homework_page = new addhomework();
    //map -> GetVecName()
    add_homework_page -> show();
}

QTime time_form::get_time(){
    return program_time;
}
