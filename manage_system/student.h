#ifndef STUDENT_H
#define STUDENT_H
#include "logger.h"
#include "calendar.h"
#include "course.h"

class Student
{
private:
    int userId;
    int courseNum;
    string userPassword;
    Logger logger;
    Calendar calendar;
    Course* course[10];//课程数应该由学生自己记录

//    /*获取当前学生的课程数目*/
//    int getCourseNumber();
    /*根据课程id获取课程名称*/
    string getCourseName(int courseId);
    /*根据课程名称获取课程id*/
    int getCourseId(string courseName);
    /*在课程类指针数组里，根据课程名称获取课程类指针*/
    Course *getCourse(string courseName);
public:
    Student(int id);
    ~Student();

    /*静态成员函数*/
    /*登录验证，若id和密码验证正确，返回true*/
    static bool login(int studentId,string password);

    /*课程功能*/
    /*获取所有课程名称*/
    QStringList getAllCourseName();
    /*询问课程时间,参数为课程名称、星期几(1-7)以及接收返回结果的长度为3的数组,数组依次存放课程开始小时，开始分钟，连续几节课*/
    void getCourseTime(string courseName,int day,int timeTable[3]);
    /*询问课程地点,参数为课程名称,返回值为课程地点编号*/
    int getCoursePlace(string courseName);
    /*询问课程进度,参数为课程名称*/
    string getSchedule(string courseName);
    /*询问课程群,参数为课程名称*/
    string getCourseGroup(string courseName);

    /*课程资料功能*/
    /*下载课程资料,参数依次为课程名称,资料名称，存放路径*/
    void getCourseData(string courseName,string dataName,string filePath);

    /*作业功能*/
    /*提交作业,参数为课程名称,返回值列表依次为作业名称，作业文件路径*/
    void submitHomework(string courseName,string homeworkName,string filePath);
    /*询问已完成作业,参数为课程名称,返回值列表依次为作业名称，作业描述...*/
    QStringList getHomeworkDone(string courseName);
    /*询问未完成作业,参数为课程名称,返回值列表依次为作业名称，作业描述...*/
    QStringList getHomeworkTodo(string courseName);

    /*考试功能*/
    /*查询考试，参数为课程名称，返回值列表依次为考试名称，开始时间，持续分钟，考试地点*/
    QStringList getExamInfo(string courseName);

//    /*闹钟功能*/
//    void setClock();//设置闹钟
//    void getClock();//获取闹钟

    /*日程表功能*/
    /*要求日程安排不能重名*/
    /*增加日程安,参数依次为事件,开始时间，结束时间*/
    void insertRecord(string event,MyTime startTime,MyTime endTime);
    /*修改日程安排,参数依次为事件,开始时间，结束时间*/
    void updateRecord(string event,MyTime startTime,MyTime endTime);
    /*删除特定日程安排,参数为事件*/
    void deleteRecord(string event);
    void clearRecords();//清除日程
    QStringList getRecords();//获取日程列表
    bool checkTimeConflict();//检测日程冲突
};

#endif // STUDENT_H