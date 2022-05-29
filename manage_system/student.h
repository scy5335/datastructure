#ifndef STUDENT_H
#define STUDENT_H
#include "logger.h"
#include "calendar.h"
#include "course.h"
#include "class.h"

class Student
{
private:
    int userId;
    string userPassword;
    Logger logger;
    Calendar calendar;
    Class *studentClass;//学生班级

public:
    /*获取学生班级id*/
    int getClassId(int studentId);
    Student(int id);
    ~Student();
    /*注册函数,参数依次为学生id，学生密码,默认班级2020211302班*/
    static bool enroll(int studentId,string password,int classId=2020211302);
    /*登录验证，若id和密码验证正确，返回true，否则注册账号,默认在2020211302班名单下*/
    static bool login(int studentId,string password);

    /*课程功能*/
    /*获取所有课程名称*/
    QStringList getAllCourseName();
    /*询问课程时间,参数为课程名称、星期几(1-7)以及接收返回结果的长度为3的数组,数组依次存放课程开始小时，开始分钟，连续几节课*/
    void getCourseTime(string courseName,int day,int *timeTable);
    /*询问课程地点,参数为课程名称,返回值为课程地点编号*/
    int getCoursePlace(string courseName);
    /*询问课程进度,参数为课程名称*/
    string getSchedule(string courseName);
    /*询问课程群,参数为课程名称*/
    string getCourseGroup(string courseName);

    /*课程资料功能*/
    /*获取课程资料名称,返回值为资料名称列表*/
    QStringList getCourseDataName(string courseName);
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


    /*日程表功能*/
    /*增加日程安排,要求日程安排不能重名,否则会刷新日程,参数依次为事件,开始时间，结束时间*/
    void insertRecord(string event,MyTime startTime,MyTime endTime,int place=0,int type=0);
    /*修改日程安排,参数依次为事件,开始时间，结束时间*/
    void updateRecord(string event,MyTime startTime,MyTime endTime,int place=0,int type=0);
    /*删除特定日程安排,参数为事件*/
    void deleteRecord(string event);
    /*清除所有日程安排*/
    void clearRecords();
    /*获取日程列表*/
    QStringList getRecords();
    /*检测日程冲突*/
    bool checkTimeConflict();
};

#endif // STUDENT_H
