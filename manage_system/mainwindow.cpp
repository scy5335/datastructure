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
    student_homework_page = NULL;
    student_material_page = NULL;
    alarm_set_page = NULL;
}

mainwindow::~mainwindow()
{
    delete ui;
}

void mainwindow::display_student_page(int user_id){
    log_student = new Student(user_id);
    student_class = new Class(log_student -> getClassId(user_id));
    student_page_set();
    this -> showMaximized();
}

void mainwindow::student_page_set(){
    setWindowTitle("学生主页");
    Clock = new MyClock();
    Clock -> start();
    set_lesson_page();
    set_calendar_page();
    set_guide_page();
    place_name = map -> GetVecName();
    calendar_set_place(place_name);
    student_get_course_info();
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
    QFont fttime, ftdate;
    fttime.setPointSize(30);
    timelabel = new QLabel();
    timelabel -> setFont(fttime);
    timelabel -> setText(trans_time(Clock -> getTime()));
    timelabel -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ftdate.setPointSize(18);
    datelabel = new QLabel();
    datelabel -> setFont(ftdate);
    datelabel -> setText(trans_date(Clock -> getTime()));
    datelabel -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    speedlabel = new QLabel();
    speedlabel -> setText("当前速度:360x");
    speedlabel -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    speed = 360;
    alarm_modify = new QPushButton();
    alarm_modify -> setText("闹钟设置");
    accelerate = new QPushButton();
    accelerate -> setText("设置速度");
    speed_change = new QLineEdit();
    QIntValidator * pIntVld = new QIntValidator(1, 3600, this);
    speed_change -> setValidator(pIntVld);
    time_button_layout = new QHBoxLayout();
    time_button_layout -> addWidget(speed_change);
    time_button_layout -> addWidget(accelerate);
    time_clock_layout = new QVBoxLayout();
    time_clock_layout -> addWidget(datelabel);
    time_clock_layout -> addWidget(timelabel);
    time_clock_layout -> addWidget(speedlabel);
    time_clock_layout -> addWidget(alarm_modify);
    time_clock_layout -> addLayout(time_button_layout);
    time_widget = new QWidget();
    time_widget -> setLayout(time_clock_layout);
    time_widget -> setFixedWidth(200);
    layout -> addWidget(time_widget);
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
    connect(Clock, &MyClock::timeChange, this, &mainwindow::time_change);
    connect(Clock, &MyClock::ring, this, &mainwindow::clock_ring);
}

void mainwindow::download_task(QString data_name, QString file_name){
    student_class -> downloadCourseData(lesson_name -> text().toStdString(), data_name.toStdString(), file_name.toLocal8Bit().data());
}

void mainwindow::submit_homework(QString homework_name, QString file_name){
    log_student -> submitHomework(lesson_name -> text().toStdString(), homework_name.toStdString(),
                                  file_name.toLocal8Bit().data());
}

void mainwindow::clock_ring(string description){
    QMessageBox::information(this, "闹钟", QString::fromStdString(description));
    if (alarm_set_page)alarm_flash();
}

void mainwindow::time_change(){
    datelabel -> setText(trans_date(Clock -> getTime()));
    timelabel -> setText(trans_time(Clock -> getTime()));
}

void mainwindow::add_speed(){
    speed = speed_change -> text().toInt();
    speedlabel -> setText("当前速度:" + QString::number(speed) + "x");
    Clock -> setSecsPerSystemHour(3600/speed);
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
    lesson_name -> setText("数据结构");
    lesson_place = new QLabel();
    lesson_place -> setText("N教学楼");
    test_label = new QLabel();
    test_label -> setText("考试信息");
    test_info = new QTableWidget();
    test_info -> setColumnCount(4);
    test_info -> setHorizontalHeaderLabels(QStringList()<<"考试名称"<<"时间"<<"时长"<<"地点");
    homework_label = new QLabel();
    homework_label -> setText("作业信息");
    material_list_button = new QPushButton();
    material_list_button -> setText("查看课程资料");
    homework_submit = new QPushButton();
    homework_submit -> setText("提交作业");
    homework_info = new QTableWidget();
    homework_info -> setColumnCount(3);
    homework_info -> setHorizontalHeaderLabels(QStringList()<<"选择"<<"作业名称"<<"截止时间");
    to_calendar_module1 = new QPushButton();
    to_calendar_module1 -> setText("查看日程表");
    to_guide_module1 = new QPushButton();
    to_guide_module1 -> setText("导航页面");
    lesson_jump_button = new QHBoxLayout();
    lesson_jump_button -> addWidget(to_calendar_module1);
    lesson_jump_button -> addWidget(to_guide_module1);
    lesson_detail_info_layout = new QFormLayout();
    lesson_detail_info_layout -> addRow("课程名称", lesson_name);
    lesson_detail_info_layout -> addRow("上课地点", lesson_place);
    lesson_detail_info_layout -> addRow(test_label, homework_label);
    lesson_detail_info_layout -> addRow(test_info, homework_info);
    lesson_detail_info_layout -> addRow(homework_submit);
    lesson_detail_info_layout -> addRow(material_list_button);
    lesson_detail_info_layout -> addRow(lesson_jump_button);
    lesson_layout = new QHBoxLayout();
    lesson_layout -> addWidget(lessontable);
    lesson_layout -> addLayout(lesson_detail_info_layout);
    connect(homework_submit, &QPushButton::clicked, this, &mainwindow::show_homework_page);
    connect(material_list_button, &QPushButton::clicked, this, &mainwindow::show_material_page);
    connect(lessontable, &QTableWidget::cellClicked, this, &mainwindow::show_lesson_info);
}

void mainwindow::student_get_course_info(){
    QStringList class_list = log_student -> getAllCourseName();
    int len = class_list.length(), course_time[3];
    for (int i = 0; i < len; i++)
        for (int j = 1; j <= 7; j++){
            log_student -> getCourseTime(class_list[i].toStdString(), j, course_time);
            if (!course_time[2]) continue;
            else {
                QString format_min = QString::number(course_time[0]),
                        format_hour = QString::number(course_time[1]),
                        format_time;
                if (course_time[0] <= 9) format_hour = "0" + format_hour;
                if (course_time[1] <= 9) format_min = "0" + format_min;
                format_time = format_hour + ":" +format_min;
                int k;
                for (k = 0; k < 14; k++)
                    if (lessontable -> horizontalHeaderItem(k) -> text().contains(format_time))
                        break;
                lessontable -> setSpan(k, j-1, course_time[2], 1);
                lessontable -> item(k, j-1) -> setText(class_list[i] + "\n" +
                                                       place_name[log_student -> getCoursePlace(class_list[i].toStdString())]);
            }
        }
}

void mainwindow::manager_get_course_info(){
    Class new_class = Class(class_select -> currentText().toInt());
    QStringList class_list = new_class.getAllCourseName();
    int len = class_list.length(), course_time[3];
    for (int i = 0; i < len; i++)
        for (int j = 1; j <= 7; j++){
            new_class.getCourseTime(class_list[i].toStdString(), j, course_time);
            if (!course_time[2]) continue;
            else {
                QString format_min = QString::number(course_time[0]),
                        format_hour = QString::number(course_time[1]),
                        format_time;
                if (course_time[0] <= 9) format_hour = "0" + format_hour;
                if (course_time[1] <= 9) format_min = "0" + format_min;
                format_time = format_hour + ":" +format_min;
                int k;
                for (k = 0; k < 14; k++)
                    if (lessontable -> horizontalHeaderItem(k) -> text().contains(format_time))
                        break;
                lessontable -> setSpan(k, j-1, course_time[2], 1);
                lessontable -> item(k, j-1) -> setText(class_list[i] + "\n" +
                                                       place_name[new_class.getCoursePlace(class_list[i].toStdString())]);
            }
        }
}

void mainwindow::show_lesson_info(int row, int column){
    QStringList lesson_main_info = lessontable -> item(row, column) -> text().split('\n');
    lesson_name -> setText(lesson_main_info[0]);
    lesson_place -> setText(lesson_main_info[1]);
    test_info -> clearContents();
    test_info -> setRowCount(0);
    QStringList now_test_info = log_student -> getExamInfo(lesson_main_info[0].toStdString());
    if (now_test_info.length()){
        test_info -> setRowCount(1);
        test_info -> setItem(0, 0, new QTableWidgetItem(now_test_info[0]));
        test_info -> setItem(0, 1, new QTableWidgetItem(now_test_info[1]));
        test_info -> setItem(0, 2, new QTableWidgetItem(now_test_info[2]+"分钟"));
        test_info -> setItem(0, 3, new QTableWidgetItem(place_name[now_test_info[3].toInt()]));
    }
    homework_info -> clearContents();
    homework_info -> setRowCount(0);
    QStringList now_homework_info = student_class -> getHomework(lesson_main_info[0].toStdString());
    int row_count = homework_info -> rowCount(), len = now_homework_info.length();
    for (int i = 0; i < len; i++){
        homework_info -> setRowCount(row_count + 1);
        QTableWidgetItem *p_check = new QTableWidgetItem();
        p_check -> setCheckState(Qt::Unchecked);
        homework_info -> setItem(0, 0, p_check);
        homework_info -> setItem(0, 1, new QTableWidgetItem(now_homework_info[i++]));
        homework_info -> setItem(0, 2, new QTableWidgetItem(now_homework_info[i++]));
        row_count ++;
    }
}

void mainwindow::show_manager_lesson_info(int row, int column){
    select_row = row;
    select_column = column;
    select_type = 0;
    Class new_class = Class(class_select -> currentText().toInt());
    if (lessontable -> item(row, column) -> text() == "")
        return;
    select_type = 1;
    QStringList lesson_main_info = lessontable -> item(row, column) -> text().split('\n');
    class_name -> setText(lesson_main_info[0]);
    place_message -> setCurrentIndex(place_message -> findText(lesson_main_info[1]));
    test_info -> clearContents();
    test_info -> setRowCount(0);
    QStringList now_test_info = log_manager -> getExamInfo(lesson_main_info[0].toStdString(), class_select -> currentText().toInt());
    if (now_test_info.length()){
        test_list -> setRowCount(1);
        QTableWidgetItem *p_check = new QTableWidgetItem();
        p_check -> setCheckState(Qt::Unchecked);
        test_list -> setItem(0, 0, p_check);
        test_list -> setItem(0, 1, new QTableWidgetItem(now_test_info[0]));
        test_list -> setItem(0, 2, new QTableWidgetItem(now_test_info[1]));
        test_list -> setItem(0, 3, new QTableWidgetItem(now_test_info[2]+"分钟"));
        test_list -> setItem(0, 4, new QTableWidgetItem(place_name[now_test_info[3].toInt()]));
    }
    homework_info -> clearContents();
    homework_info -> setRowCount(0);
    QStringList now_homework_info = log_manager -> getHomework(lesson_main_info[0].toStdString(), class_select -> currentText().toInt());
    int row_count = homework_info -> rowCount(), len = now_homework_info.length();
    for (int i = 0; i < len; i++){
        homework_info -> setRowCount(row_count + 1);
        QTableWidgetItem *p_check = new QTableWidgetItem();
        p_check -> setCheckState(Qt::Unchecked);
        homework_info -> setItem(0, 0, p_check);
        homework_info -> setItem(0, 1, new QTableWidgetItem(now_homework_info[i++]));
        homework_info -> setItem(0, 2, new QTableWidgetItem(now_homework_info[i++]));
        row_count ++;
    }
}

void mainwindow::set_calendar_page(){
    calendar_title = new QLabel();
    calendar_title -> setText("日程表");
    calendar_list = new QTableWidget();
    calendar_list -> setColumnCount(6);
    calendar_list -> setHorizontalHeaderLabels(QStringList()<<"选择"<<"活动名称"<<"活动类型"<<"开始时间"<<"结束时间"<<"地点");
    calendar_list -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
    calendar_display();
    calendar_main_layout = new QVBoxLayout();
    calendar_main_layout -> addWidget(calendar_title);
    calendar_main_layout -> addWidget(calendar_list);
    calendar_description = new QLineEdit();
    set_time();
    //QMessageBox::critical(this, "添加活动出错", "活动与课程或活动冲突");
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
    calendar_layout = new QHBoxLayout();
    calendar_layout -> addLayout(calendar_main_layout);
    calendar_layout -> addLayout(calendar_right);
    connect(s_nian, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &mainwindow::s_change_day);
    connect(s_yue, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &mainwindow::s_change_day);
    connect(e_nian, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &mainwindow::e_change_day);
    connect(e_yue, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &mainwindow::e_change_day);
    connect(calendar_add, &QPushButton::clicked, this, &mainwindow::try_add_calendar);
    connect(calendar_del, &QPushButton::clicked, this, &mainwindow::delete_calendars);
}

void mainwindow::try_add_calendar(){
    if (calendar_description -> text() == "")
        QMessageBox::critical(this, "添加活动出错", "活动名称为空");
    if (s_ri -> currentIndex() == -1 || s_shi -> currentIndex() == -1 || s_fen -> currentIndex() == -1)
        QMessageBox::critical(this, "添加活动出错","请输入完整的开始时间");
    if (e_ri -> currentIndex() == -1 || e_shi -> currentIndex() == -1 || e_fen -> currentIndex() == -1)
        QMessageBox::critical(this, "添加活动出错","请输入完整的结束时间");
    MyTime start_time = MyTime(s_nian -> currentText().toInt(), s_yue -> currentText().toInt(),
                               s_ri -> currentText().toInt(), s_shi -> currentText().toInt(),
                               s_fen -> currentText().toInt());
    MyTime end_time = MyTime(e_nian -> currentText().toInt(), e_yue -> currentText().toInt(),
                             e_ri -> currentText().toInt(), e_shi -> currentText().toInt(),
                             e_fen -> currentText().toInt());
    if (end_time < start_time)
        QMessageBox::critical(this, "添加活动出错", "开始时间晚于结束时间");
    log_student -> insertRecord(calendar_description -> text().toStdString(), start_time, end_time);
    if (log_student -> checkTimeConflict()){
        log_student -> deleteRecord(calendar_description -> text().toStdString());
        QMessageBox::critical(this, "添加活动出错", "活动冲突");
    }
    calendar_display();
}

void mainwindow::delete_calendars(){
    int len = calendar_list -> rowCount();
    for (int i = 0; i < len; i++)
        if (calendar_list -> item(i, 0) -> checkState() == Qt::Checked)
            log_student -> deleteRecord(calendar_list -> item(i, 1) -> text().toStdString());
    calendar_display();
}

void mainwindow::calendar_display(){
    calendar_list -> clearContents();
    QStringList tot_calendar = log_student -> getRecords();
    int len = tot_calendar.length();
    calendar_list -> setRowCount(len/3);
    for (int i = 0, row_count = 0; i < len; row_count++){
        QTableWidgetItem *p_check = new QTableWidgetItem();
        p_check -> setCheckState(Qt::Unchecked);
        calendar_list -> setItem(row_count, 0, p_check);
        calendar_list -> setItem(row_count, 2 ,new QTableWidgetItem("个人活动"));
        calendar_list -> setItem(row_count, 3 ,new QTableWidgetItem(tot_calendar[i++]));
        calendar_list -> setItem(row_count, 4 ,new QTableWidgetItem(tot_calendar[i++]));
        calendar_list -> setItem(row_count, 1 ,new QTableWidgetItem(tot_calendar[i++]));
        calendar_list -> setItem(row_count, 5 ,new QTableWidgetItem("南区食堂"));
    }
    calendar_list -> horizontalHeader() -> setSectionResizeMode(QHeaderView::ResizeToContents);
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
    place_select -> addItems(place_name);
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
    dist_only = new QRadioButton();
    dist_only -> setText("距离优先");
    time_first = new QRadioButton();
    time_first -> setText("时间优先");
    mix = new QRadioButton();
    mix -> setText("交通工具");
    mode_select = new QHBoxLayout();
    mode_select -> addWidget(dist_only);
    mode_select -> addWidget(time_first);
    mode_select -> addWidget(mix);
    mode_group = new QButtonGroup();
    mode_group -> addButton(dist_only, 0);
    mode_group -> addButton(time_first, 1);
    mode_group -> addButton(mix, 2);
    dist_only -> setChecked(true);
    guide_mod_layout -> addWidget(query_label);
    guide_mod_layout -> addWidget(query_list);
    guide_mod_layout -> addWidget(answer_label);
    guide_mod_layout -> addWidget(answer_list);
    guide_mod_layout -> addWidget(guide_time);
    guide_mod_layout -> addWidget(place_select);
    guide_mod_layout -> addLayout(place_layout);
    guide_mod_layout -> addWidget(start_guide);
    guide_mod_layout -> addLayout(mode_select);
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
    answer_list -> addItems(map -> maingraph -> FindPath(qsl, totminutes, mode_group -> checkedId()));
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

void mainwindow::display_manage_page(){
    manage_page_set();
    this -> show();
}

void mainwindow::manage_page_set(){
    setWindowTitle("管理员主页");
    log_manager = new Manager();
    Clock = new MyClock();
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
    for (int i = 2020211301; i <= 2020211310; i++)
        class_select -> addItem(QString::number(i));
    class_select -> setCurrentIndex(-1);
    class_layout = new QHBoxLayout();
    class_layout -> addWidget(ask_class);
    class_layout -> addWidget(class_select);

    class_name_title = new QLabel();
    class_name_title -> setText("课程名");
    class_name = new QLineEdit();
    //teacher_message = new QLineEdit();
    place_message_title = new QLabel();
    place_message_title -> setText("上课地点");
    place_message = new QComboBox();
    class_count_title = new QLabel();
    class_count_title -> setText("连续节数");
    class_count = new QComboBox();
    map = new myGraphView();
    place_message -> addItems(place_name);
    for (int i = 1; i <= 6; i++)
        class_count -> addItem(QString::number(i));
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
    test_list = new QTableWidget();
    test_list -> setColumnCount(5);
    test_list -> setHorizontalHeaderLabels(QStringList()<<"选择"<<"考试名称"<<"时间"<<"时长"<<"地点");
    homework_add = new QPushButton();
    homework_add -> setText("添加作业");
    homework_del = new QPushButton();
    homework_del -> setText("删除作业");
    homework_title = new QLabel();
    homework_title -> setText("作业信息");
    homework_list = new QTableWidget();
    homework_list -> setColumnCount(3);
    homework_list -> setHorizontalHeaderLabels(QStringList()<<"选择"<<"作业名称"<<"截止时间");
    material_manage_button = new QPushButton();
    material_manage_button -> setText("管理课程资料");
    message_layout = new QGridLayout();
    message_layout -> addWidget(class_name_title, 0, 0);
    message_layout -> addWidget(class_name, 0, 1);
    message_layout -> addWidget(place_message_title, 1, 0);
    message_layout -> addWidget(place_message, 1, 1);
    message_layout -> addWidget(class_count_title, 2, 0);
    message_layout -> addWidget(class_count, 2, 1);
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
    connect(add_lesson, &QPushButton::clicked, this, &mainwindow::try_add_lesson);
    connect(delete_lesson, &QPushButton::clicked, this, &mainwindow::delete_this_lesson);
    connect(test_del, &QPushButton::clicked, this, &mainwindow::test_delete);
    connect(test_add, &QPushButton::clicked, this, &mainwindow::test_add_page);
    connect(homework_add, &QPushButton::clicked, this, &mainwindow::homework_add_page);
    connect(homework_del, &QPushButton::clicked, this, &mainwindow::homework_delete);
    connect(material_manage_button, &QPushButton::clicked, this, &mainwindow::material_add_page);
    connect(class_select, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &mainwindow::manager_get_course_info);
    connect(lessontable, &QTableWidget::cellClicked, this, &mainwindow::show_manager_lesson_info);
}

void mainwindow::test_delete(){
    if (test_list -> rowCount() == 1 && test_list -> item(0, 0) -> checkState() == Qt::Checked)
        log_manager -> deleteExam(class_name -> text().toStdString(), class_select -> currentText().toInt());
    show_manager_lesson_info(select_row, select_column);
}

void mainwindow::test_add_page(){
    if (add_test_page != NULL) delete add_test_page;
    add_test_page = new addtest(Clock -> getTime().getYear());
    add_test_page -> set_place(place_name);
    add_test_page -> show();
    connect(add_test_page, &addtest::test_upload, this, &mainwindow::test_upload);
}

void mainwindow::trans_hour_min(int row, int &hour, int &min){
    switch (row){
    case 0: hour = 8;
            min = 0;
    case 1: hour = 8;
            min = 50;
    case 2: hour = 9;
            min = 50;
    case 3: hour = 10;
            min = 40;
    case 4: hour = 11;
            min = 30;
    case 5: hour = 13;
            min = 0;
    case 6: hour = 13;
            min = 50;
    case 7: hour = 14;
            min = 45;
    case 8: hour = 15;
            min = 40;
    case 9: hour = 16;
            min = 35;
    case 10: hour = 17;
            min = 25;
    case 11: hour = 18;
            min = 30;
    case 12: hour = 19;
            min = 20;
    default: hour = 20;
            min = 10;
    }
}

void mainwindow::delete_this_lesson(){
    if (class_name -> text() == "")
        return;
    log_manager -> deleteCoure(class_name -> text().toStdString(), class_select -> currentText().toInt());
    manager_get_course_info();
}

void mainwindow::try_add_lesson(){
    if (class_name -> text() == "")
        QMessageBox::critical(this, "添加课程错误", "请输入课程名称");
    if (place_message -> currentIndex() == -1)
        QMessageBox::critical(this, "添加课程错误", "请输入上课地点");
    if (class_count -> currentIndex() == -1)
        QMessageBox::critical(this, "添加课程错误", "请输入课程节数");
    if (class_count -> currentIndex() + select_row > 14)
        QMessageBox::critical(this, "添加课程错误", "课程结束时间超过最晚的课程");
    if (select_type)
        delete_this_lesson();
    log_manager -> addCourse(class_name -> text().toStdString(), place_message -> currentIndex(),
                        class_select -> currentText().toInt());
    int hour, min;
    trans_hour_min(select_row, hour, min);
    log_manager -> setCourseTime(class_name -> text().toStdString(), select_column + 1, hour, min,
                                 class_count -> currentText().toInt(), class_select -> currentText().toInt());
    manager_get_course_info();
}

void mainwindow::test_upload(QString test_name, MyTime start_time, int place, int last_time){
    log_manager -> uploadExam(class_name -> text().toStdString(),
                               test_name.toStdString(), start_time, place,
                               last_time, class_select -> currentText().toInt());
}

void mainwindow::homework_delete(){
    int len = homework_list -> rowCount();
    for (int i = 0; i < len; i++)
        if (homework_list -> item(i, 0) -> checkState() == Qt::Checked)
            log_manager -> deleteHomework(class_name -> text().toStdString(),
                                       homework_list -> item(i, 1) -> text().toStdString(),
                                       class_select -> currentText().toInt());
    show_manager_lesson_info(select_row, select_column);
}

void mainwindow::homework_add_page(){
    if (add_homework_page != NULL) delete add_homework_page;
    add_homework_page = new addhomework(Clock -> getTime().getYear());
    add_homework_page -> show();
    connect(add_homework_page, &addhomework::homework_upload, this, &mainwindow::homework_upload);
}

void mainwindow::homework_upload(QString homework_name, MyTime ddl, QString homework_description){
    log_manager -> uploadHomework(class_name -> text().toStdString(), homework_name.toStdString(),
                             ddl, homework_description.toStdString(), class_select -> currentText().toInt());
}

void mainwindow::material_add_page(){
    if (material_page != NULL) delete material_page;
    material_page = new material_manage_page();
    material_page -> show();
    connect(material_page, &material_manage_page::delete_material, this, &mainwindow::delete_material);
    connect(material_page, &material_manage_page::get_all_material, this, &mainwindow::get_all_material);
    connect(material_page, &material_manage_page::add_new_material, this, &mainwindow::add_new_material);
}

void mainwindow::show_material_page(){
    if (student_material_page != NULL) delete student_material_page;
    student_material_page = new material_detail(log_student -> getCourseDataName(lesson_name -> text().toStdString()));
    student_material_page -> show();
    connect(student_material_page, &material_detail::download, this, &mainwindow::download_task);
}

void mainwindow::get_all_material(){
    material_page -> set_all_material(log_manager -> getCourseDataInfo(class_name -> text().toStdString(),
                                                                       class_select -> currentText().toInt()));
}

void mainwindow::delete_material(QString description){
    log_manager -> removeCourseData(class_name -> text().toStdString(), description.toStdString(),
                                    class_select -> currentText().toInt());
}

void mainwindow::add_new_material(QString description, QString file_path){
    log_manager -> uploadCourseData(class_name -> text().toStdString(),description.toStdString(),
                                    file_path.toLocal8Bit().data(), class_select -> currentText().toInt());
}

void mainwindow::show_homework_page(){
    int id = -1, row_count = homework_info -> rowCount();
    for (int i = 0; i < row_count; i++)
        if (homework_info -> item(i, 0) -> checkState() == Qt::Checked){
            if (id == -1)
                id = i;
            else {
                QMessageBox::critical(this, "选择错误", "一次只能选择一个作业提交");
                return;
            }
        }
    if (id == -1) return;
    if (student_homework_page != NULL) delete student_homework_page;
    QStringList homework_total_info, now_homework_info = student_class -> getHomework(lesson_name->text().toStdString());
    homework_total_info << now_homework_info[id * 3] << now_homework_info[id * 3 + 1]
                        << now_homework_info[id * 3 + 2];
    student_homework_page = new homework_submit_page(homework_total_info);
    student_homework_page -> show();
    connect(student_homework_page, &homework_submit_page::submit_homework, this, &mainwindow::submit_homework);
}

void mainwindow::show_alarm_page(){
    if (alarm_set_page != NULL) delete alarm_set_page;
    alarm_set_page = new alarm_page();
    alarm_set_page -> set_alarm_list(Clock);
    alarm_set_page -> show();
    connect(alarm_set_page, &alarm_page::create_new_alarm, this, &mainwindow::add_alarm);
    connect(alarm_set_page, &alarm_page::create_new_alarm, this, &mainwindow::alarm_flash);
    connect(alarm_set_page, &alarm_page::alarm_type_changed, this, &mainwindow::alarm_type_modify);
    connect(alarm_set_page, &alarm_page::delete_signal, this, &mainwindow::delete_alarm);
}

void mainwindow::alarm_type_modify(int row){
    Clock -> alarms ->  arr[row].setState(3 - Clock -> alarms -> arr[row].getState());
}

void mainwindow::alarm_flash(){
    alarm_set_page -> set_alarm_list(Clock);
}

void mainwindow::add_alarm(Alarm a){
    if (Clock -> addAlarm(a) == NULL)
        QMessageBox::critical(this, "加入闹钟出错", "闹钟数量过多，删掉一些吧！");
}

void mainwindow::delete_alarm(int id){
    Clock -> rmAlarm(&Clock -> alarms -> arr[id]);
    alarm_flash();
}

void mainwindow::set_time(){
    int now_year = Clock -> getTime().getYear();
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

QString mainwindow::trans_time(MyTime now_time){
    QString Str1, Str2;
    if (now_time.getHour()<=9) Str1 = "0" + QString::number(now_time.getHour());
    else Str1 = QString::number(now_time.getHour());
    if (now_time.getMin()<=9) Str2 = "0" + QString::number(now_time.getMin());
    else Str2 = QString::number(now_time.getMin());
    return Str1+":"+Str2;
}

QString mainwindow::trans_date(MyTime now_time){
    QString Str1, Str2, Str3;
    Str1 = QString::number(now_time.getYear());
    if (now_time.getMonth()<=9) Str2 = "0" + QString::number(now_time.getMonth());
    else Str2 = QString::number(now_time.getMonth());
    if (now_time.getDay()<=9) Str3 = "0" + QString::number(now_time.getDay());
    else Str3 = QString::number(now_time.getDay());
    return Str1+"年"+Str2+"月"+Str3+"日";
}

material_detail::material_detail(QStringList task_list, QWidget *parent){
    setWindowTitle("课程资料");
    material_list = new QTableWidget();
    material_list -> setColumnCount(2);
    material_list -> setHorizontalHeaderLabels(QStringList()<<"资料名"<<"下载");
    material_list -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
    int len = task_list.length();
    material_list -> setRowCount(len);
    for (int i = 0; i < len; i++){
        QPushButton *download = new QPushButton();
        download -> setText("下载");
        material_list -> setItem(i, 0, new QTableWidgetItem(task_list[i]));
        material_list -> setCellWidget(i, 1, download);
    }
    layout = new QHBoxLayout();
    layout -> addWidget(material_list);
    setLayout(layout);
    connect(material_list, &QTableWidget::cellClicked, this, &material_detail::try_download);
}

void material_detail::try_download(int row, int column){
    if (column == 1){
        QString file_path_name = QFileDialog::getExistingDirectory(this, tr("选择文件夹"),QDir::currentPath());
        if (file_path_name.isEmpty())
            return;
        file_path_name += "\\" + material_list -> item(row, 0) -> text() + ".data";
        emit download(material_list -> item(row, 0) -> text(), file_path_name);
    }
}

homework_submit_page::homework_submit_page(QStringList info, QWidget *parent){
    setWindowTitle("作业提交");
    title = new QLabel();
    title -> setText(info[0]);
    ddl = new QLabel();
    ddl -> setText(info[1]);
    description = new QLabel();
    description -> setText(info[2]);
    file_select = new QPushButton();
    file_select -> setText("选择文件");
    submit = new QPushButton();
    submit -> setText("提交");
    file_path = new QLabel();
    layout = new QFormLayout();
    layout -> addRow("作业名称", title);
    layout -> addRow("作业截至时间", ddl);
    layout -> addRow("提交状态", description);
    layout -> addRow(file_select, file_path);
    layout -> addRow(submit);
    setLayout(layout);
    connect(file_select, &QPushButton::clicked, this, &homework_submit_page::file_select_page);
}

void homework_submit_page::file_select_page(){
    QString filename = QFileDialog::getOpenFileName(this, tr("选择文件"), "C:/", tr("All files(*.*)"));
    file_path -> setText(filename);
    emit submit_homework(title -> text(), filename);
}

alarm_page::alarm_page(QWidget *parent){
    setWindowTitle("闹钟设置");
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
    times_group = new QButtonGroup();
    times_group ->addButton(only_once, 0);
    times_group ->addButton(every_day, 1);
    times_group ->addButton(every_week, 2);
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
    new_alarm_layout -> addRow("频率", radio_layout);
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
    alarm_list -> setColumnCount(5);
    alarm_list -> setHorizontalHeaderLabels(QStringList()<<"选择"<<"描述"<<"是否开启"<<"时间"<<"频率");
    alarm_list -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
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
    connect(add_alarm, &QPushButton::clicked, this, &alarm_page::get_new_alarm);
    connect(del_alarm, &QPushButton::clicked, this, &alarm_page::deletealarm);
}

void alarm_page::deletealarm(){
    int row = alarm_list -> rowCount();
    int backet[maxLen], cnt = 0;
    for (int i = 0; i < row; i++)
        if (alarm_list -> item(i, 0) -> checkState() == Qt::Checked)
            backet[cnt++] = alarm_id[i];
    for (int i = 0; i < cnt; i++)
        emit delete_signal(backet[i]);
}

void alarm_page::hide_day(){
    day_widget -> setCurrentIndex(0);
}

void alarm_page::display_day(){
    day_widget -> setCurrentIndex(1);
}

void alarm_page::get_new_alarm(){
    int state = 0;
    if (times_group -> checkedId() == 1) state = 0x7F;
    else if (times_group -> checkedId() == 2){
        for (int i = 0; i < 7 ;i++)
            state |= (day[i] -> checkState() == Qt::Checked) << i;
        qDebug() << state;
        if (!state)
            QMessageBox::critical(this, "错误", "请选择至少一天");
    }

    Alarm new_alarm = Alarm(hour -> currentIndex(), minute -> currentIndex(), state, 1,
                            alarm_description -> text().toStdString());
    emit create_new_alarm(new_alarm);
}

void alarm_page::set_alarm_list(MyClock *Clock){
    alarm_list -> clearContents();
    alarm_list -> setRowCount(0);
    alarm_count = 0;
    disconnect(alarm_list, &QTableWidget::cellChanged, this, &alarm_page::set_type);
    int len = Clock -> alarms -> getLen();
    int row_count = alarm_list -> rowCount();
    for (int i = 0; i < len; i++)
        if (Clock -> alarms -> arr[i].getState() != -1){
            alarm_list -> setRowCount(row_count + 1);
            QTableWidgetItem* p_check = new QTableWidgetItem(), *sel_check = new QTableWidgetItem();
            if (Clock -> alarms -> arr[i].getState() == 1)
                p_check -> setCheckState(Qt::Checked);
            else
                p_check -> setCheckState(Qt::Unchecked);
            sel_check -> setCheckState(Qt::Unchecked);
            alarm_list -> setItem(row_count, 0, sel_check);
            alarm_list -> setItem(row_count, 1,new QTableWidgetItem(QString::fromStdString(
                                      Clock -> alarms -> arr[i].getTip())));
            alarm_list -> setItem(row_count, 2, p_check);
            QString Str1, Str2;
            int hour = Clock -> alarms -> arr[i].getHour(),
                minute = Clock -> alarms -> arr[i].getMinute();
            if (hour <= 9) Str1 = "0" + QString::number(hour);
            else Str1 = QString::number(hour);
            if (minute <= 9) Str2 = "0" + QString::number(minute);
            else Str2 = QString::number(minute);
            alarm_list -> setItem(row_count, 3, new QTableWidgetItem(Str1 + ":" + Str2));
            Str1 = "";
            if (Clock -> alarms -> arr[i].getType() == 0)
                Str1 = "仅一次";
            else if (Clock -> alarms -> arr[i].getType() == 0x7f)
                Str1 = "每周一次";
            else for (int j = 0; j < 7; j++)
                if (Clock -> alarms -> arr[i].getType() & (1<<j)){
                    switch (j){
                        case 0 : Str1 += "星期一";
                                break;
                        case 1 : Str1 += "星期二";
                                break;
                        case 2 : Str1 += "星期三";
                                break;
                        case 3 : Str1 += "星期四";
                                break;
                        case 4 : Str1 += "星期五";
                                break;
                        case 5 : Str1 += "星期六";
                                 break;
                        default : Str1 += "星期日";
                    }
                }
            alarm_list -> setItem(row_count, 4, new QTableWidgetItem(Str1));
            alarm_id[alarm_count++] = i;
            row_count ++;
        }
    connect(alarm_list, &QTableWidget::cellChanged, this, &alarm_page::set_type);
}

void alarm_page::set_type(int row, int column){
    if (column == 2)
        emit alarm_type_changed(alarm_id[row]);
}
