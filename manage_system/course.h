#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include<string>
#include"task.h"
#include"data.h"
#include<cstring>
#include<filesystem>
#define uchar unsigned char
#define ull unsigned long long
using namespace std;
namespace fs = std::filesystem;
const uchar listLen=30;
/*
课程类介绍：
课程类继承了QObject，可以设置parent指针来利用Qt的自动释放对象功能。
-------------------------------------------------------------
-------------------------------------------------------------
私有成员变量介绍：
unsigned courseId;
    课程通过字典树得到的课程编码，课程类内部并不内置字典树，故需要上层提供该课程编码。与文件存储路径有关
unsigned teacherId;
    老师的id，注意无符号整数的范围
unsigned locale;
    上课地点标识
unsigned weekTable[7];
    用于记录每日上课的时间。初始化为0，其个位表示当天连续几节课，百位和十位表示开始的分钟，千位表示开始的小时。
    特别提醒，需要通过setCourseTime(....)来设置
    需要通过courseBeginHour(.)，courseBeginMin(.)和courseLast(.)来获取
uchar startWeek,endWeek;
    课程的起始周次和结束周次，左必右闭
ull firstClass;
    该课程的第一个上课的班级，与文件存储路径有关
uchar continuous;
    该课程从第一个上课的班级数起，有几个连续的班级，与文件存储路径有关
string group;
    课程群字符串
bool need2save;
    标记现在是否需要保存。修改内存中数据后会置为true，完整保存课程文件后会置为true
uchar taskNum;
    已读入的作业数量
uchar dataNum;
    已读入的资料数量
string dir;
    该课程的目录
string examName;
    考试名称。未设置考试时为"unitialized"
int examLocale,lastMinute;
    考试地点，持续分钟数
MyTime startTime;
    考试开始的时间
-------------------------------------------------------------
-------------------------------------------------------------
公有成员变量介绍
Task* task[listLen];
    作业指针列表，最大长度为listLen。taskSort会改变作业指针在列表中的顺序。
    可以直接访问以提交作业，但不要调用task的remove函数，因为remove函数只会静默地删除该task的所有文件。
Data* data[listLen];
    与作业指针列表几乎完全一样，同样不要调用remove函数

-------------------------------------------------------------
-------------------------------------------------------------
函数介绍
Course(unsigned courseId, unsigned locale, string root="D:\\");
    主要用于创建新的课程时使用，会初始化课程的信息，
    但是具体的上课时间以及考试信息由于未给出而初始化为无效值。
Course(unsigned courseId,string root="D:\\");
    io函数
    主要用于给已存在的课程创建一个课程类载体，会通过参数找到文件的位置并读取，
    如果不存在对应的文件会报错，但不会中断程序
void setLocale(int locale);
    和它的名字一样
void setCourseTime(uchar weekDay, uchar hour, uchar min, uchar last);//星期、从几点的几分开始，持续几节课
    设置某一天的上课时间，注意weekDay是平常所说的星期数-1，与MyTime类获取的星期一致。参数依次为星期几-1，开始上课的小时、分钟，持续几节课
void setPeriodWeek(int startWeek, int endWeek);
    设置上课的周次范围
void setGroup(string group);
    设置群
void setExamInfo(string examName, MyTime startTime, int locale, int lastMinute);
    设置考试信息，参数为考试名称、起始时间、地点、考试持续多少分钟
void setRoot(string root);
    重新设置根目录，原有路径不再保存，可能造成数据丢失

-------------------------------------------------------------
-------------------------------------------------------------
以下为基本的获取私有变量的值的函数
unsigned getCourseId();
unsigned getLocale();
int courseBeginHour(int day);
int courseBeginMin(int day);
int courseLast(int day);
int getTotalHour();
    获取总课时数
string getGroup();
string getExamName();
int getExamLocale();
MyTime getStartTime();
int getLastMinute();
-------------------------------------------------------------
-------------------------------------------------------------
Task* releaseTask(string taskName, MyTime sysTime, MyTime deadline, string description="");
    发布作业，参数依次为作业名称、系统当前时间（作为setTime）、截止时间、作业描述（默认为空串）
    注意：非io函数，会置need2save为true
Data* releaseData(string dataName, string fileAddr, MyTime sysTime);
    上传资料，参数依次为资料名称、文件路径、系统当前时间（作为setTime）
void saveFile();
    io函数
    保存与该课程相关的所有信息，同时置need2save为false
    （注意上层仍需保存定位该课程的三个信息：课程名称或者id，第一个班级，以及一共几个班级）
void readFile();
    io函数
    读取与该课程相关的所有信息。如果此时need2save为true，会提示数据可能丢失，但会继续读取文件。
-------------------------------------------------------------
-------------------------------------------------------------
void taskSort(bool sortByDDL);
    参数为真时利用deadline时间对作业升序排列，否则利用setTime时间对作业升序排列。
    鉴于一般课程的作业数量不多且往往有序排列，采用插入排序而非快排
Task* taskSearch(string name);
    遍历搜索指定名称的作业，返回该作业的指针。
    如果该作业不存在，返回nullptr
void dataSort();
    利用setTime对资料升序排列，同样采用插入排序
Data* dataSearch(string name);
    遍历搜索指定名称的资料，返回该资料的指针
-------------------------------------------------------------
-------------------------------------------------------------
void taskRemove(Task* t);
    io函数
    完全删除指定的作业，包括删除该作业的备份文件，释放该作业对象，以及taskNum--
    注意，该函数可能会改变原作业列表的顺序，所以尽量避免通过task数组下标访问作业列表，而是直接用指针访问
void dataRemove(Data* d);
    io函数
    taskRemove的资料版本
void remove();
    io函数
    删除本课程，包括删除所有作业和资料，删除课程文件，courseId置为0xFFFFFFFF
    注意，需要上层释放该课程对象，否则可能造成意料之外的错误
-------------------------------------------------------------
-------------------------------------------------------------
私有方法：
void taskReadIn(string name);
    io函数
    读取指定名称的作业全部信息，创建对应的Task类对象到task列表中
void dataReadIn(string name);
    io函数
    读取指定名称的资料，创建对应的Data类对象到data列表中
-------------------------------------------------------------
-------------------------------------------------------------
类使用方法（参考）
1. 课程的创建或读入
    对于新创建的课程，采用第一个构造函数，尽可能多的完善课程基本信息。
    读取已创建的课程，采用第二个构造函数，只需3个信息即可定位到函数。
    注意，课程类的根目录如果被更改可能会导致无法定位课程文件。

2. 何时需要保存文件
    设置了新的课程变量时，发布了新作业时，（资料会自动保存到文件中，毕竟要上传）

3. 常见使用顺序
    创建/读取课程new Course(...)，设置非必须信息，例如setExamInfo(....)
    发布作业releaseTask(....)，利用搜索等功能获得作业指针，从而使用查看作业信息、提交作业等功能
    上传资料的方法类似。
    若需删除某个作业或资料，调用taskRemove或dataRemove函数。如果需要删除课程，则调用remove函数。记得修改上层的课程列表


4. 注意事项
    1. 记得在必要时刻保存。可以利用need2save函数判断是否需要保存
    2. 发布作业的函数在同名作业已存在时会直接返回空指针，注意避免对nullptr的调用。而发布资料的函数在检测到同名资料存在时会更新并返回资料指针，注意二者区别。
    3. 作业、资料名称以及其路径上不要有中文或者空格和换行符等符号
    4. 作业的名称、资料的名称无法进行修改，如果需要修改，请删除再重新发布。
    5. 不要直接调用作业或者资料的remove函数，这样只会删除它们的文件。删除操作无法恢复。
    6: 我设想用户可以通过ui看到作业的部分基本信息，ui类建立作业容器和其指针的映射关系，在用户点击作业容器时，即可直接确定该作业的指针。所以我将task列表设为公有变量了。
       如何展示作业的信息，展示作业的哪些信息都可以直接通过作业对象获得（即课程类没有再次封装它们）。资料同理。
    7. 根据实际情况确定listLen，即作业和资料列表的最大长度。
*/

class Course : public QObject
{
    Q_OBJECT
private:
    unsigned courseId;
    unsigned locale;
    unsigned weekTable[7];
    string group;
    bool need2save;
    uchar taskNum;
    uchar dataNum;
    string dir;
    string examName;
    int examLocale,lastMinute;
    MyTime startTime;
    void taskReadIn(string name);
    void dataReadIn(string name);
public:
    Task* task[listLen];
    Data* data[listLen];
    explicit Course(QObject *parent = nullptr);
    Course(unsigned courseId, unsigned locale, string root="D:\\");
    Course(unsigned courseId, string root="D:\\");
    void setLocale(int locale);
    void setCourseTime(uchar weekDay, uchar hour, uchar min, uchar last);//星期、从几点的几分开始，持续几节课
    void setGroup(string group);
    void setExamInfo(string examName, MyTime startTime, int locale, int lastMinute);
    void setRoot(string root);
    void cancelExam();
    unsigned getCourseId();

    unsigned getLocale();
    int courseBeginHour(int day);
    int courseBeginMin(int day);
    int courseLast(int day);
    int getStartWeek();
    int getEndWeek();
    int getTotalHour();
    ull getFirstClass();
    int getClassNum();
    string getGroup();
    string getExamName();
    int getExamLocale();
    MyTime getStartTime();
    int getLastMinute();
    Task* releaseTask(string taskName, MyTime sysTime, MyTime deadline, string description="");//只在内存中创建，需要保存。
    Data* releaseData(string dataName, string fileAddr, MyTime sysTime);
    void saveFile();
    void readFile();
    void taskSort(bool sortByDDL);
    static void taskSort(Task*buffer[], int len, bool sortByDDL);
    Task* taskSearch(string name);
    int taskSearchByKeyword(string keyword, Task*buffer[]);
    void dataSort();
    static void dataSort(Data*buffer[], int len);
    Data* dataSearch(string name);
    int dataSearchByKeyword(string keyword, Data* buffer[]);
    int getTaskNum();
    int getDataNum();
    void taskRemove(Task* t);
    void dataRemove(Data* d);
    void remove();
    ~Course();
signals:

};

class MyString
{
public:
    static bool contains(string parent, string child);
private:
    static void getNext(string child, int next[]);
    static int KMP(string parent, string child, int next[]);
};
#endif // COURSE_H























