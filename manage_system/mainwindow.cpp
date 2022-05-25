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
    setWindowTitle("ѧ����ҳ");
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
    speedlabel -> setText("��ǰ�ٶ�:360x");
    speedlabel -> setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    speed = 360;
    alarm_modify = new QPushButton();
    alarm_modify -> setText("��������");
    accelerate = new QPushButton();
    accelerate -> setText("�����ٶ�");
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
    connect(student_homework_page, &homework_submit_page::submit_homework, this, &mainwindow::submit_homework);
    connect(student_material_page, &material_detail::download, this, &mainwindow::download_task);
}

void mainwindow::download_task(QString data_name, QString file_name){
    student_class -> downloadCourseData(lesson_name -> text().toStdString(), data_name.toStdString(), file_name.toStdString());
}

void mainwindow::submit_homework(QString homework_name, QString file_name){
    log_student -> submitHomework(lesson_name -> text().toStdString(), homework_name.toStdString(),
                                  file_name.toStdString());
}

void mainwindow::clock_ring(string description){
    QMessageBox::information(this, "����", QString::fromStdString(description));
    if (alarm_set_page)alarm_flash();
}

void mainwindow::time_change(){
    datelabel -> setText(trans_date(Clock -> getTime()));
    timelabel -> setText(trans_time(Clock -> getTime()));
}

void mainwindow::add_speed(){
    speed = speed_change -> text().toInt();
    speedlabel -> setText("��ǰ�ٶ�:" + QString::number(speed) + "x");
    Clock -> setSecsPerSystemHour(3600/speed);
}

void mainwindow::set_lesson_page(){
    lessontable = new QTableWidget(14,7);
    lessontable -> setHorizontalHeaderLabels(QStringList()<<"����һ"<<"���ڶ�"<<"������"<<
                                             "������"<<"������"<<"������"<<"������");
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
    qDebug() << lessontable -> rowCount();
    lesson_name = new QLabel();
    lesson_name -> setText("���ݽṹ");
    lesson_place = new QLabel();
    lesson_place -> setText("N��ѧ¥");
    test_label = new QLabel();
    test_label -> setText("������Ϣ");
    test_info = new QTableWidget();
    test_info -> setColumnCount(4);
    test_info -> setHorizontalHeaderLabels(QStringList()<<"��������"<<"ʱ��"<<"ʱ��"<<"�ص�");
    homework_label = new QLabel();
    homework_label -> setText("��ҵ��Ϣ");
    material_list_button = new QPushButton();
    material_list_button -> setText("�鿴�γ�����");
    homework_submit = new QPushButton();
    homework_submit -> setText("�ύ��ҵ");
    homework_info = new QTableWidget();
    homework_info -> setColumnCount(3);
    homework_info -> setHorizontalHeaderLabels(QStringList()<<"ѡ��"<<"��ҵ����"<<"��ֹʱ��");
    to_calendar_module1 = new QPushButton();
    to_calendar_module1 -> setText("�鿴�ճ̱�");
    to_guide_module1 = new QPushButton();
    to_guide_module1 -> setText("����ҳ��");
    lesson_jump_button = new QHBoxLayout();
    lesson_jump_button -> addWidget(to_calendar_module1);
    lesson_jump_button -> addWidget(to_guide_module1);
    lesson_detail_info_layout = new QFormLayout();
    lesson_detail_info_layout -> addRow("�γ�����", lesson_name);
    lesson_detail_info_layout -> addRow("�Ͽεص�", lesson_place);
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
    QStringList class_list = student_class -> getAllCourseName();
    int len = class_list.length(), course_time[3];
    for (int i = 0; i < len; i++)
        for (int j = 1; j <= 7; j++){
            student_class -> getCourseTime(class_list[i].toStdString(), j, course_time);
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
                                                       place_name[student_class -> getCoursePlace(class_list[i].toStdString())]);
            }
        }
}

void mainwindow::show_lesson_info(int row, int column){
    QStringList lesson_main_info = lessontable -> item(row, column) -> text().split('\n');
    lesson_name -> setText(lesson_main_info[0]);
    lesson_place -> setText(lesson_main_info[1]);
    test_info -> clearContents();
    test_info -> setRowCount(0);
    QStringList now_test_info = student_class -> getExamInfo(lesson_main_info[0].toStdString());
    if (now_test_info.length()){
        test_info -> setRowCount(1);
        test_info -> setItem(0, 0, new QTableWidgetItem(now_test_info[0]));
        test_info -> setItem(0, 1, new QTableWidgetItem(now_test_info[1]));
        test_info -> setItem(0, 2, new QTableWidgetItem(now_test_info[2]+"����"));
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

void mainwindow::set_calendar_page(){
    calendar_title = new QLabel();
    calendar_title -> setText("�ճ̱�");
    calendar_list = new QTableWidget();
    calendar_list -> setColumnCount(6);
    calendar_list -> setHorizontalHeaderLabels(QStringList()<<"ѡ��"<<"�����"<<"�����"<<"��ʼʱ��"<<"����ʱ��"<<"�ص�");
    calendar_list -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
    calendar_list -> setRowCount(1);
    QTableWidgetItem *p_check = new QTableWidgetItem();
    p_check -> setCheckState(Qt::Unchecked);
    calendar_list -> setItem(0, 0, p_check);
    calendar_list -> setItem(0 ,1 ,new QTableWidgetItem("�۲�"));
    calendar_list -> setItem(0 ,2 ,new QTableWidgetItem("���˻"));
    calendar_list -> setItem(0 ,3 ,new QTableWidgetItem("2000��3��2��19:00"));
    calendar_list -> setItem(0 ,4 ,new QTableWidgetItem("2000��3��2��21:00"));
    calendar_list -> setItem(0 ,5 ,new QTableWidgetItem("����ʳ��"));
    calendar_list -> resizeColumnsToContents();
    calendar_main_layout = new QVBoxLayout();
    calendar_main_layout -> addWidget(calendar_title);
    calendar_main_layout -> addWidget(calendar_list);
    calendar_description = new QLineEdit();
    set_time();
    //QMessageBox::critical(this, "��ӻ����", "���γ̻���ͻ");
    single_activity = new QRadioButton();
    single_activity -> setText("���˻");
    group_activity = new QRadioButton();
    group_activity -> setText("����");
    single_activity -> setChecked(true);
    activity_radio = new QHBoxLayout();
    activity_radio -> addWidget(single_activity);
    activity_radio -> addWidget(group_activity);
    calendar_place = new QComboBox();
    calendar_info_layout = new QFormLayout();
    calendar_info_layout -> addRow("�����", calendar_description);
    calendar_info_layout -> addRow("�����", activity_radio);
    calendar_info_layout -> addRow("���ʼʱ��",s_calendar_time_layout);
    calendar_info_layout -> addRow("�����ʱ��",e_calendar_time_layout);
    calendar_info_layout -> addRow("��ص�",calendar_place);
    calendar_add = new QPushButton();
    calendar_add -> setText("��ӻ");
    calendar_del = new QPushButton();
    calendar_del -> setText("ɾ���");
    calendar_info_layout -> addRow(calendar_add);
    calendar_info_layout -> addRow(calendar_del);
    to_lesson_module1 = new QPushButton();
    to_lesson_module1 -> setText("�鿴�γ̱�");
    to_guide_module2 = new QPushButton();
    to_guide_module2 -> setText("����ҳ��");
    calendar_change_button = new QHBoxLayout();
    calendar_change_button -> addWidget(to_lesson_module1);
    calendar_change_button -> addWidget(to_guide_module2);
    calendar_right = new QVBoxLayout();
    calendar_right -> addLayout(calendar_info_layout);
    calendar_right -> addLayout(calendar_change_button);
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
    to_lesson_module2 -> setText("�鿴�γ̱�");
    to_calendar_module2 = new QPushButton();
    to_calendar_module2 -> setText("�鿴�ճ̱�");

    guide_button_layout =new QHBoxLayout();
    guide_button_layout -> addWidget(to_lesson_module2);
    guide_button_layout -> addWidget(to_calendar_module2);

    place_select = new QComboBox();
    place_select -> addItems(place_name);
    place_select -> setCurrentIndex(-1);
    place_select_button = new QPushButton();
    place_select_button -> setText("ȷ��");
    place_clear_button = new QPushButton();
    place_clear_button -> setText("���");
    place_layout =new QHBoxLayout();
    place_layout -> addWidget(place_select_button);
    place_layout -> addWidget(place_clear_button);

    guide_mod_layout = new QVBoxLayout();
    query_label = new QLabel();
    query_label -> setText("�����ص�");
    query_list = new QListWidget();
    query_list -> setFixedWidth(200);
    answer_label = new QLabel();
    answer_label -> setText("�������");
    answer_list = new QListWidget();
    answer_list -> setFixedWidth(200);
    guide_time = new QLabel();
    start_guide = new QPushButton();
    start_guide -> setText("��ʼ����");
    dist_only = new QRadioButton();
    dist_only -> setText("��������");
    time_first = new QRadioButton();
    time_first -> setText("ʱ������");
    mix = new QRadioButton();
    mix -> setText("��ͨ����");
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
    QString estimate_time = "Ԥ����ʱ " + QString::number(ceil(totminutes))+" ����";
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
    setWindowTitle("����Ա��ҳ");
    Clock = new MyClock();
    lessontable = new QTableWidget(14,7);
    lessontable -> setHorizontalHeaderLabels(QStringList()<<"����һ"<<"���ڶ�"<<"������"<<
                                             "������"<<"������"<<"������"<<"������");
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
    ask_class -> setText("��ѡ��Ҫ���в����İ༶");
    class_select = new QComboBox();
    class_select -> addItem("2020211302");
    class_layout = new QHBoxLayout();
    class_layout -> addWidget(ask_class);
    class_layout -> addWidget(class_select);

    class_name_title = new QLabel();
    class_name_title -> setText("�γ���");
    class_name = new QLineEdit();
    //teacher_name_title = new QLabel();
    //teacher_name_title -> setText("�ον�ʦ");
    teacher_message = new QLineEdit();
    place_message_title = new QLabel();
    place_message_title -> setText("�Ͽεص�");
    place_message = new QComboBox();
    map = new myGraphView();
    place_message -> addItems(place_name);
    place_message -> setCurrentIndex(-1);
    add_lesson = new QPushButton();
    add_lesson -> setText("��Ӵ˿�");
    delete_lesson = new QPushButton();
    delete_lesson -> setText("ɾ���˿�");
    test_add = new QPushButton();
    test_add -> setText("��ӿ���");
    test_del = new QPushButton();
    test_del -> setText("ɾ������");
    test_title = new QLabel();
    test_title -> setText("������Ϣ");
    test_list = new QTableWidget();
    test_list -> setColumnCount(5);
    test_list -> setHorizontalHeaderLabels(QStringList()<<"ѡ��"<<"��������"<<"ʱ��"<<"ʱ��"<<"�ص�");
    test_list -> setRowCount(1);
    QTableWidgetItem *p_check = new QTableWidgetItem();
    p_check -> setCheckState(Qt::Unchecked);
    test_list -> setItem(0, 0, p_check);
    test_list -> setItem(0, 1, new QTableWidgetItem("���п�"));
    test_list -> setItem(0, 2, new QTableWidgetItem("2000��4��25��"));
    test_list -> setItem(0, 3, new QTableWidgetItem("90����"));
    test_list -> setItem(0, 4, new QTableWidgetItem("S��ѧ¥"));
    homework_add = new QPushButton();
    homework_add -> setText("�����ҵ");
    homework_del = new QPushButton();
    homework_del -> setText("ɾ����ҵ");
    homework_title = new QLabel();
    homework_title -> setText("��ҵ��Ϣ");
    homework_list = new QTableWidget();
    homework_list -> setColumnCount(3);
    homework_list -> setHorizontalHeaderLabels(QStringList()<<"ѡ��"<<"��ҵ����"<<"��ֹʱ��");
    homework_list -> setRowCount(1);
    QTableWidgetItem *p_check1 = new QTableWidgetItem();
    p_check1 -> setCheckState(Qt::Unchecked);
    homework_list -> setItem(0, 0, p_check1);
    homework_list -> setItem(0, 1, new QTableWidgetItem("��һ����ҵ"));
    homework_list -> setItem(0, 2, new QTableWidgetItem("2000��3��5��"));
    material_manage_button = new QPushButton();
    material_manage_button -> setText("����γ�����");
    message_layout = new QGridLayout();
    message_layout -> addWidget(class_name_title, 0, 0);
    message_layout -> addWidget(class_name, 0, 1);
    //message_layout -> addWidget(teacher_name_title, 1, 0);
    //message_layout -> addWidget(teacher_message, 1, 1);
    message_layout -> addWidget(place_message_title, 1, 0);
    message_layout -> addWidget(place_message, 1, 1);
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
    add_test_page = new addtest(Clock -> getTime().getYear());
    add_test_page -> set_place(place_name);
    add_test_page -> show();
}

void mainwindow::homework_add_page(){
    if (add_homework_page != NULL) delete add_homework_page;
    add_homework_page = new addhomework(Clock -> getTime().getYear());
    add_homework_page -> show();
}

void mainwindow::material_add_page(){
    if (material_page != NULL) delete material_page;
    material_page = new material_manage_page();
    material_page -> show();
}

void mainwindow::show_material_page(){
    if (student_material_page != NULL) delete student_material_page;
    student_material_page = new material_detail(student_class -> getCourseDataInfo(lesson_name -> text().toStdString()));
    student_material_page -> show();
}

void mainwindow::show_homework_page(){
    int id = -1, row_count = homework_info -> rowCount();
    for (int i = 0; i < row_count; i++)
        if (homework_info -> item(i, 0) -> checkState() == Qt::Checked){
            if (id == -1)
                id = i;
            else {
                QMessageBox::critical(this, "ѡ�����", "һ��ֻ��ѡ��һ����ҵ�ύ");
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
        QMessageBox::critical(this, "�������ӳ���", "�����������࣬ɾ��һЩ�ɣ�");
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
    s_nian_name -> setText("��");
    s_yue = new QComboBox();
    for (int i = 1; i <= 12; i++)
        s_yue -> addItem(QString::number(i));
    s_yue -> setCurrentIndex(-1);
    s_yue_name = new QLabel();
    s_yue_name -> setText("��");
    s_ri = new QComboBox();
    s_ri_name = new QLabel();
    s_ri_name -> setText("��");
    s_shi = new QComboBox();
    for (int i = 0; i <= 23; i++)
        s_shi -> addItem(QString::number(i));
    s_shi -> setCurrentIndex(-1);
    s_shi_name = new QLabel();
    s_shi_name -> setText("ʱ");
    s_fen = new QComboBox();
    for (int i = 0; i <= 59; i++)
        s_fen -> addItem(QString::number(i));
    s_fen -> setCurrentIndex(-1);
    s_fen_name = new QLabel();
    s_fen_name -> setText("��");
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
    e_nian_name -> setText("��");
    e_yue = new QComboBox();
    for (int i = 1; i <= 12; i++)
        e_yue -> addItem(QString::number(i));
    e_yue -> setCurrentIndex(-1);
    e_yue_name = new QLabel();
    e_yue_name -> setText("��");
    e_ri = new QComboBox();
    e_ri_name = new QLabel();
    e_ri_name -> setText("��");
    e_shi = new QComboBox();
    for (int i = 0; i <= 23; i++)
        e_shi -> addItem(QString::number(i));
    e_shi -> setCurrentIndex(-1);
    e_shi_name = new QLabel();
    e_shi_name -> setText("ʱ");
    e_fen = new QComboBox();
    for (int i = 0; i <= 59; i++)
        e_fen -> addItem(QString::number(i));
    e_fen -> setCurrentIndex(-1);
    e_fen_name = new QLabel();
    e_fen_name -> setText("��");
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
    return Str1+"��"+Str2+"��"+Str3+"��";
}

material_detail::material_detail(QStringList task_list, QWidget *parent){
    setWindowTitle("�γ�����");
    material_list = new QTableWidget();
    material_list -> setColumnCount(2);
    material_list -> setHorizontalHeaderLabels(QStringList()<<"������"<<"����");
    material_list -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
    int len = task_list.length();
    material_list -> setRowCount(len);
    for (int i = 0; i < len; i++){
        QPushButton *download = new QPushButton();
        download -> setText("����");
        material_list -> setItem(i, 0, new QTableWidgetItem(task_list[i]));
        material_list -> setCellWidget(i, 1, download);
    }
    layout = new QHBoxLayout();
    layout -> addWidget(material_list);
    setLayout(layout);
    connect(material_list, &QTableWidget::clicked, this, &material_detail::try_download);
}

void material_detail::try_download(int row, int column){
    if (column == 1){
        QString file_path_name = QFileDialog::getExistingDirectory(this, tr("ѡ���ļ���"),QDir::currentPath());
        if (file_path_name.isEmpty())
            return;
        file_path_name += "\\" + material_list -> item(row, 0) -> text() + ".data";
        emit download(material_list -> item(row, 0) -> text(), file_path_name);
    }
}

homework_submit_page::homework_submit_page(QStringList info, QWidget *parent){
    setWindowTitle("��ҵ�ύ");
    title = new QLabel();
    title -> setText(info[0]);
    ddl = new QLabel();
    ddl -> setText(info[1]);
    description = new QLabel();
    description -> setText(info[2]);
    //state = new QLabel();
    //state -> setText(info[1]);
    file_select = new QPushButton();
    file_select -> setText("ѡ���ļ�");
    submit = new QPushButton();
    submit -> setText("�ύ");
    file_path = new QLabel();
    layout = new QFormLayout();
    layout -> addRow("��ҵ����", title);
    layout -> addRow("��ҵ����ʱ��", ddl);
    layout -> addRow("�ύ״̬", description);
    layout -> addRow(file_select, file_path);
    layout -> addRow(submit);
    setLayout(layout);
    connect(file_select, &QPushButton::clicked, this, &homework_submit_page::file_select_page);
}

void homework_submit_page::file_select_page(){
    QString filename = QFileDialog::getOpenFileName(this, tr("ѡ���ļ�"), "C:/", tr("All files(*.*)"));
    file_path -> setText(filename);
    emit submit_homework(title -> text(), filename);
}

alarm_page::alarm_page(QWidget *parent){
    setWindowTitle("��������");
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
    only_once -> setText("��һ��");
    every_day = new QRadioButton();
    every_day -> setText("ÿ��һ��");
    every_week = new QRadioButton();
    every_week -> setText("ÿ��һ��");
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
    add_alarm -> setText("�������");
    new_alarm_layout = new QFormLayout();
    new_alarm_layout -> addRow("��������", alarm_description);
    new_alarm_layout -> addRow("ʱ��", time_layout);
    new_alarm_layout -> addRow("Ƶ��", radio_layout);
    page[0] = new QWidget();
    day_layout = new QHBoxLayout();
    page[1] = new QWidget();
    for (int i = 0; i < 7; i++){
        day[i] = new QCheckBox();
        QString day_name;
        switch (i){
            case 0 : day_name = "����һ";
                     break;
            case 1 : day_name = "���ڶ�";
                     break;
            case 2 : day_name = "������";
                     break;
            case 3 : day_name = "������";
                     break;
            case 4 : day_name = "������";
                     break;
            case 5 : day_name = "������";
                     break;
            default : day_name = "������";
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
    alarm_list -> setHorizontalHeaderLabels(QStringList()<<"ѡ��"<<"����"<<"�Ƿ���"<<"ʱ��"<<"Ƶ��");
    alarm_list -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
    alarm_list_title = new QLabel();
    alarm_list_title -> setText("�����б�");
    del_alarm = new QPushButton();
    del_alarm -> setText("ɾ������");
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
            QMessageBox::critical(this, "����", "��ѡ������һ��");
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
                Str1 = "��һ��";
            else if (Clock -> alarms -> arr[i].getType() == 0x7f)
                Str1 = "ÿ��һ��";
            else for (int j = 0; j < 7; j++)
                if (Clock -> alarms -> arr[i].getType() & (1<<j)){
                    switch (j){
                        case 0 : Str1 += "����һ";
                                break;
                        case 1 : Str1 += "���ڶ�";
                                break;
                        case 2 : Str1 += "������";
                                break;
                        case 3 : Str1 += "������";
                                break;
                        case 4 : Str1 += "������";
                                break;
                        case 5 : Str1 += "������";
                                 break;
                        default : Str1 += "������";
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

