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
    material_page = NULL;
    student_material_page = NULL;
    alarm_set_page = NULL;
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
    calendar_set_place(map -> GetVecName());
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
    speed = 10;
    alarm_modify = new QPushButton();
    alarm_modify -> setText("闹钟设置");
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
    time_clock_layout -> addWidget(alarm_modify);
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
    connect(alarm_modify, &QPushButton::clicked, this, &mainwindow::show_alarm_page);
    connect(accelerate, &QPushButton::clicked, this, &mainwindow::add_speed);
    connect(slow_down, &QPushButton::clicked, this, &mainwindow::dec_speed);
}

void mainwindow::add_speed(){
    speed++;
    speedlabel -> setText("当前速度:" + QString::number(speed) + "x");
}

void mainwindow::dec_speed(){
    if (!speed)
        QMessageBox::critical(this, "减速出错", "时间已停止");
    speed--;
    speedlabel -> setText("当前速度:" + QString::number(speed) + "x");
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
    material_list_button = new QPushButton();
    material_list_button -> setText("查看课程资料");
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
    lesson_detail_info_layout -> addRow(test_label, homework_label);
    lesson_detail_info_layout -> addRow(test_info, homework_info);
    lesson_detail_info_layout -> addRow(homework_submit);
    lesson_detail_info_layout -> addRow(material_list_button);
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
    calendar_description = new QLineEdit();
    set_time();
    single_activity = new QRadioButton();
    single_activity -> setText("个人活动");
    group_activity = new QRadioButton();
    group_activity -> setText("集体活动");
    single_activity -> setChecked(true);
    activity_radio = new QHBoxLayout();
    activity_radio -> addWidget(single_activity);
    activity_radio -> addWidget(group_activity);
    calendar_place = new QComboBox();
    calendar_info_layout = new QFormLayout();
    calendar_info_layout -> addRow("活动名称", calendar_description);
    calendar_info_layout -> addRow("活动类型", activity_radio);
    calendar_info_layout -> addRow("活动开始时间",s_calendar_time_layout);
    calendar_info_layout -> addRow("活动结束时间",e_calendar_time_layout);
    calendar_info_layout -> addRow("活动地点",calendar_place);
    calendar_add = new QPushButton();
    calendar_add -> setText("添加活动");
    calendar_del = new QPushButton();
    calendar_del -> setText("删除活动");
    calendar_info_layout -> addRow(calendar_add);
    calendar_info_layout -> addRow(calendar_del);
    to_lesson_module1 = new QPushButton();
    to_lesson_module1 -> setText("查看课程表");
    to_guide_module2 = new QPushButton();
    to_guide_module2 -> setText("导航页面");
    calendar_change_button = new QHBoxLayout();
    calendar_change_button -> addWidget(to_lesson_module1);
    calendar_change_button -> addWidget(to_guide_module2);
    calendar_right = new QVBoxLayout();
    calendar_right -> addLayout(calendar_info_layout);
    calendar_right -> addLayout(calendar_change_button);
    //calendar_info_layout -> addRow(calendar_change_button);
    calendar_layout = new QHBoxLayout();
    calendar_layout -> addLayout(calendar_main_layout);
    calendar_layout -> addLayout(calendar_right);
    connect(s_nian, &QComboBox::currentIndexChanged, this, &mainwindow::s_change_day);
    connect(s_yue, &QComboBox::currentIndexChanged, this, &mainwindow::s_change_day);
    connect(e_nian, &QComboBox::currentIndexChanged, this, &mainwindow::e_change_day);
    connect(e_yue, &QComboBox::currentIndexChanged, this, &mainwindow::e_change_day);
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
    material_manage_button = new QPushButton();
    material_manage_button -> setText("管理课程资料");
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
    button_grid -> addWidget(material_manage_button, 3, 0, 1, 2);
    button_grid -> addWidget(test_title, 4, 0);
    button_grid -> addWidget(homework_title, 4, 1);
    button_grid -> addWidget(test_list, 5, 0);
    button_grid -> addWidget(homework_list, 5, 1);
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
    connect(material_manage_button, &QPushButton::clicked, this, &mainwindow::material_add_page);
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
    add_homework_page -> show();
}

void mainwindow::material_add_page(){
    if (material_page != NULL) delete material_page;
    material_page = new material_manage_page();
    material_page -> show();
}

void mainwindow::show_material_page(){
    if (student_material_page != NULL) delete student_material_page;
    student_material_page = new material_detail();
    student_material_page -> show();
}

void mainwindow::show_alarm_page(){
    if (alarm_set_page != NULL) delete alarm_set_page;
    alarm_set_page = new alarm_page();
    alarm_set_page -> show();
}

void mainwindow::set_time(){
    int now_year = 2022;
    s_nian = new QComboBox();
    for (int i = now_year; i <= now_year + 5; i++)
        s_nian -> addItem(QString::number(i));
    s_nian -> setCurrentIndex(-1);
    s_nian_name = new QLabel();
    s_nian_name -> setText("年");
    s_yue = new QComboBox();
    for (int i = 1; i <= 12; i++)
        s_yue -> addItem(QString::number(i));
    s_yue -> setCurrentIndex(-1);
    s_yue_name = new QLabel();
    s_yue_name -> setText("月");
    s_ri = new QComboBox();
    s_ri_name = new QLabel();
    s_ri_name -> setText("日");
    s_shi = new QComboBox();
    for (int i = 0; i <= 23; i++)
        s_shi -> addItem(QString::number(i));
    s_shi -> setCurrentIndex(-1);
    s_shi_name = new QLabel();
    s_shi_name -> setText("时");
    s_fen = new QComboBox();
    for (int i = 0; i <= 59; i++)
        s_fen -> addItem(QString::number(i));
    s_fen -> setCurrentIndex(-1);
    s_fen_name = new QLabel();
    s_fen_name -> setText("分");
    s_calendar_time_layout = new QHBoxLayout();
    s_calendar_time_layout -> addWidget(s_nian);
    s_calendar_time_layout -> addWidget(s_nian_name);
    s_calendar_time_layout -> addWidget(s_yue);
    s_calendar_time_layout -> addWidget(s_yue_name);
    s_calendar_time_layout -> addWidget(s_ri);
    s_calendar_time_layout -> addWidget(s_ri_name);
    s_calendar_time_layout -> addWidget(s_shi);
    s_calendar_time_layout -> addWidget(s_shi_name);
    s_calendar_time_layout -> addWidget(s_fen);
    s_calendar_time_layout -> addWidget(s_fen_name);
    e_nian = new QComboBox();
    for (int i = now_year; i <= now_year + 5; i++)
        e_nian -> addItem(QString::number(i));
    e_nian -> setCurrentIndex(-1);
    e_nian_name = new QLabel();
    e_nian_name -> setText("年");
    e_yue = new QComboBox();
    for (int i = 1; i <= 12; i++)
        e_yue -> addItem(QString::number(i));
    e_yue -> setCurrentIndex(-1);
    e_yue_name = new QLabel();
    e_yue_name -> setText("月");
    e_ri = new QComboBox();
    e_ri_name = new QLabel();
    e_ri_name -> setText("日");
    e_shi = new QComboBox();
    for (int i = 0; i <= 23; i++)
        e_shi -> addItem(QString::number(i));
    e_shi -> setCurrentIndex(-1);
    e_shi_name = new QLabel();
    e_shi_name -> setText("时");
    e_fen = new QComboBox();
    for (int i = 0; i <= 59; i++)
        e_fen -> addItem(QString::number(i));
    e_fen -> setCurrentIndex(-1);
    e_fen_name = new QLabel();
    e_fen_name -> setText("分");
    e_calendar_time_layout = new QHBoxLayout();
    e_calendar_time_layout -> addWidget(e_nian);
    e_calendar_time_layout -> addWidget(e_nian_name);
    e_calendar_time_layout -> addWidget(e_yue);
    e_calendar_time_layout -> addWidget(e_yue_name);
    e_calendar_time_layout -> addWidget(e_ri);
    e_calendar_time_layout -> addWidget(e_ri_name);
    e_calendar_time_layout -> addWidget(e_shi);
    e_calendar_time_layout -> addWidget(e_shi_name);
    e_calendar_time_layout -> addWidget(e_fen);
    e_calendar_time_layout -> addWidget(e_fen_name);
}

void mainwindow::s_change_day(){
    if (s_nian -> currentIndex() == -1 || s_yue -> currentIndex() == -1) return;
    QDate date(s_nian -> currentText().toInt(), s_yue -> currentText().toInt(), 1);
    s_ri -> clear();
    int day = date.daysInMonth();
    for (int i = 1; i <= day; i++)
        s_ri -> addItem(QString::number(i));
    s_ri -> setCurrentIndex(-1);
}

void mainwindow::e_change_day(){
    if (e_nian -> currentIndex() == -1 || e_yue -> currentIndex() == -1) return;
    QDate date(e_nian -> currentText().toInt(), e_yue -> currentText().toInt(), 1);
    e_ri -> clear();
    int day = date.daysInMonth();
    for (int i = 1; i <= day; i++)
        e_ri -> addItem(QString::number(i));
    e_ri -> setCurrentIndex(-1);
}

void mainwindow::calendar_set_place(QStringList name){
    calendar_place -> addItems(name);
    calendar_place -> setCurrentIndex(-1);
}

QTime time_form::get_time(){
    return program_time;
}

material_detail::material_detail(QWidget *parent){
    material_list = new QListWidget();
    layout = new QHBoxLayout();
    layout -> addWidget(material_list);
    setLayout(layout);
}

alarm_page::alarm_page(QWidget *parent){
    alarm_description = new QLineEdit();
    hour_minute = new QLabel();
    hour_minute -> setText(":");
    hour = new QComboBox();
    for (int i=0; i < 24; i++)
        hour -> addItem(QString::number(i));
    minute = new QComboBox();
    for (int i=0; i < 60; i++)
        minute -> addItem(QString::number(i));
    time_layout = new QHBoxLayout();
    time_layout -> addWidget(hour);
    time_layout -> addWidget(hour_minute);
    time_layout -> addWidget(minute);
    only_once = new QRadioButton();
    only_once -> setText("仅一次");
    every_day = new QRadioButton();
    every_day -> setText("每天一次");
    every_week = new QRadioButton();
    every_week -> setText("每周一次");
    radio_layout = new QHBoxLayout();
    radio_layout -> addWidget(only_once);
    radio_layout -> addWidget(every_day);
    radio_layout -> addWidget(every_week);
    only_once -> setChecked(true);
    add_alarm = new QPushButton();
    add_alarm -> setText("添加闹钟");
    new_alarm_layout = new QFormLayout();
    new_alarm_layout -> addRow("闹钟描述", alarm_description);
    new_alarm_layout -> addRow("时间", time_layout);
    new_alarm_layout -> addRow("重复频次", radio_layout);
    page[0] = new QWidget();
    day_layout = new QHBoxLayout();
    page[1] = new QWidget();
    for (int i = 0; i < 7; i++){
        day[i] = new QCheckBox();
        QString day_name;
        switch (i){
            case 0 : day_name = "星期一";
                     break;
            case 1 : day_name = "星期二";
                     break;
            case 2 : day_name = "星期三";
                     break;
            case 3 : day_name = "星期四";
                     break;
            case 4 : day_name = "星期五";
                     break;
            case 5 : day_name = "星期六";
                     break;
            default : day_name = "星期日";
        }
        day[i] -> setText(day_name);
        day_layout -> addWidget(day[i]);
    }
    page[1] -> setLayout(day_layout);
    day_widget = new QStackedWidget();
    day_widget -> addWidget(page[0]);
    day_widget -> addWidget(page[1]);
    day_widget -> setCurrentIndex(0);
    new_alarm_layout -> addRow(day_widget);
    new_alarm_layout -> addRow(add_alarm);
    alarm_list = new QTableWidget();
    alarm_list_title = new QLabel();
    alarm_list_title -> setText("闹钟列表");
    del_alarm = new QPushButton();
    del_alarm -> setText("删除闹钟");
    new_alarm_layout -> addRow(alarm_list_title);
    new_alarm_layout -> addRow(alarm_list);
    new_alarm_layout -> addRow(del_alarm);
    setLayout(new_alarm_layout);
    connect(only_once, &QAbstractButton::clicked, this, &alarm_page::hide_day);
    connect(every_day, &QAbstractButton::clicked, this, &alarm_page::hide_day);
    connect(every_week, &QAbstractButton::clicked, this, &alarm_page::display_day);
}

void alarm_page::hide_day(){
    day_widget -> setCurrentIndex(0);
}

void alarm_page::display_day(){
    day_widget -> setCurrentIndex(1);
}
