#ifndef CLASS_H
#define CLASS_H
#include <string>
#include<fstream>
#include "course.h"
using namespace std;

class Class
{
private:
    int classId;//班级id
    int courseNum;//课程数应该由班级记录
    Course **course;//课程指针的数组

    /*根据课程名称获取课程id*/
    int getCourseId(string courseName);
    /*根据课程id获取课程名称*/
    string getCourseName(int courseId);
    Course *getCourse(string courseName);
public:
    Class(int classId);
    ~Class();

    /*课程功能*/
    /*新增课程,参数为课程名称和课程地点编号*/
    static void addCourse(string courseName,int locale,int classId);
    /*删除课程,参数为课程名称*/
    void deleteCoure(string courseName);
    /*设置课程时间参数依次为周几(1-7),开始小时,开始分钟,持续多少节课*/
    /*这个设定前提是一门课一天只上一次，并且是连续的*/
    void setCourseTime(string courseName,int weekday,int startHour,int startMinute,int classes);
    /*设置课程群,参数依次为课程名称，课程群*/
    void setCourseGroup(string courseName,string courseGroup);
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
    /*上传课程资料,参数依次为课程名称,资料名称,资料文件路径*/
    void uploadCourseData(string courseName,string dataName,string dataPath);
    /*获取课程资料名称,返回值为资料名称列表*/
    QStringList getCourseDataInfo(string courseName);
    /*删除课程资料,参数依次为课程名称,资料名称*/
    void removeCourseData(string courseName,string dataName);
    /*下载课程资料,参数为课程名称,资料名称,存放文件路径*/
    void downloadCourseData(string courseName,string dataName,string downloadPath);
    /*下载课程资料,参数依次为课程名称,资料名称，存放路径*/
    void getCourseData(string courseName,string dataName,string filePath);

    /*考试功能*/
    /*发布考试，参数依次为考试科目,考试名称,开始时间,地点，时长*/
    void uploadExam(string courseName,string examName,MyTime startTime,int location,int duration);
    /*取消考试,参数为考试科目,由于课程类默认只记录一个考试，所以会删除当前考试*/
    void deleteExam(string courseName);
    /*查询考试,返回值依次为考试名称,开始时间,地点,时长*/
    QStringList getExamInfo(string courseName);

    /*作业功能*/
    /*布置作业，参数依次为课程名称,作业名称,截止时间,作业描述*/
    void uploadHomework(string courseName,string homeworkName,MyTime deadline,string description);
    /*删除作业,参数依次为课程名称,作业名称*/
    void deleteHomework(string courseName,string homeworkName);
    /*查询作业,返回值依次为作业名称,截止时间,作业描述*/
    QStringList getHomework(string courseName);
    /*提交作业,参数为课程名称,返回值列表依次为作业名称，作业文件路径*/
    void submitHomework(string courseName,string homeworkName,string filePath,int userId);
    /*询问已完成作业,参数为课程名称,返回值列表依次为作业名称，作业描述...*/
    QStringList getHomeworkDone(string courseName,int userId);
    /*询问未完成作业,参数为课程名称,返回值列表依次为作业名称，作业描述...*/
    QStringList getHomeworkTodo(string courseName,int userId);
};

#endif // CLASS_H
