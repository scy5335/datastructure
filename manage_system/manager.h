#ifndef MANAGER_H
#define MANAGER_H
#include "logger.h"
#include "course.h"
#include "class.h"
class Manager
{
private:
    int id;
//    string password;
    Logger logger;

public:
    Manager();
    ~Manager();

    /*课程功能*/
    /*新增课程,参数为课程名称,课程地点编号和班级id,班级id范围是2020211301——2020211310*/
    void addCourse(string courseName,int locale,int classId);
    /*删除课程,参数为课程名称*/
    void deleteCoure(string courseName,int classId);
    /*设置课程时间参数依次为周几(1-7),开始小时,开始分钟,持续多少节课*/
    /*这个设定前提是一门课一天只上一次，并且是连续的*/
    void setCourseTime(string courseName,int weekday,int startHour,int startMinute,int classes,int classId);
    /*设置课程群,参数依次为课程名称，课程群*/
    void setCourseGroup(string courseName,string courseGroup,int classId);

    /*课程资料功能*/
    /*上传课程资料,参数依次为课程名称,资料名称,资料文件路径*/
    void uploadCourseData(string courseName,string dataName,string dataPath,int classId);
    /*获取课程资料名称,返回值为资料名称列表*/
    QStringList getCourseDataInfo(string courseName,int classId);
    /*删除课程资料,参数依次为课程名称,资料名称*/
    void removeCourseData(string courseName,string dataName,int classId);
    /*下载课程资料,参数为课程名称,资料名称,存放文件路径*/
    void downloadCourseData(string courseName,string dataName,string downloadPath,int classId);

    /*考试功能*/
    /*发布考试，参数依次为考试科目,考试名称,开始时间,地点，时长*/
    void uploadExam(string courseName,string examName,MyTime startTime,int location,int duration,int classId);
    /*取消考试,参数为考试科目,由于课程类默认只记录一个考试，所以会删除当前考试*/
    void deleteExam(string courseName,int classId);
    /*查询考试,返回值依次为考试名称,开始时间,地点,时长*/
    QStringList getExamInfo(string courseName,int classId);

    /*作业功能*/
    /*布置作业，参数依次为课程名称,作业名称,截止时间,作业描述*/
    void uploadHomework(string courseName,string homeworkName,MyTime deadline,string description,int classId);
    /*删除作业,参数依次为课程名称,作业名称*/
    void deleteHomework(string courseName,string homeworkName,int classId);
    /*查询作业,返回值依次为作业名称,截止时间,作业描述*/
    QStringList getHomework(string courseName,int classId);

    /*日志功能*/
    /*清空日志*/
    void clearLogger();
    /*获取日志列表*/
    QStringList getLogger();
};

#endif // MANAGER_H
