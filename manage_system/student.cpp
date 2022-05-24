#include "student.h"

int Student::getClassId(int studentId)
{
    int id,classId=0;
    string pwd;
    fstream file("student\\studentInfo.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>id>>pwd>>classId;
            if(id==studentId){
                file.close();
                return classId;
            }
        }
    }
    return classId;
}

Student::Student(int id):
    userId(id),
    logger("student\\"+to_string(id)+"_log.txt"),
    calendar(to_string(id)+"_calendar.txt"),
    studentClass(new Class(getClassId(id)))
{
    /*将课程表导入日程表中，这是初始化操作，以便后续判断时间冲突*/
    int day,timeTable[3];
    QStringList list=studentClass->getAllCourseName();
    for(int i=0;i<list.length();++i){
        for(day=1;day<=5;++day){
            studentClass->getCourseTime(list[i].toStdString(),day,timeTable);
            /*下面生成时间年月日不好确定*/
            MyTime *startTime=new MyTime(0,0,0,timeTable[0],timeTable[1]);
            MyTime *endTime=new MyTime(0,0,0,timeTable[0],timeTable[1]);
            endTime->minIncre(timeTable[2]*50-5);//计算课程总时间,默认课间没有户外活动
            insertRecord("周"+to_string(day)+list[i].toStdString(),*startTime,*endTime);
        }
    }
}

Student::~Student()
{
    delete studentClass;
}

bool Student::login(int studentId, string password,int classId)
{
    int id=1,classID=2020211302;
    string pwd;
    fstream file("student\\studentInfo.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>id>>pwd>>classID;
            if(id==studentId){//学生账号存在
                file.close();
                return password==pwd;
            }
        }
        file.close();
    }
    /*若不存在该学生，根据参数classId给该学生注册账号*/
    file.open("student\\studentInfo.txt",ios::app);
    if(file.is_open()){
        file<<endl<<studentId;
        file<<endl<<password;
        file<<endl<<classId;
        file.close();
    }
    /*创建学生日志文件*/
    file.open("student\\"+to_string(id)+"_logger.txt",ios::out);
    if(file.is_open()){
        file.close();
    }
    /*创建学生日程表文件*/
    file.open("student\\"+to_string(id)+"_calendar.txt",ios::out);
    if(file.is_open()){
        file.close();
    }
    return false;
}

QStringList Student::getAllCourseName()
{
    logger.addLogger("学生查询了所有课程名称");
    return studentClass->getAllCourseName();
}

void Student::getCourseTime(string courseName,int day,int *timeTable)
{
    logger.addLogger("学生查询了课程时间");
    studentClass->getCourseTime(courseName,day,timeTable);
}

int Student::getCoursePlace(string courseName)
{
    logger.addLogger("学生查询了课程地点");
    return studentClass->getCoursePlace(courseName);
}

void Student::getCourseData(string courseName,string dataName,string filePath)
{
    logger.addLogger("学生查询了课程资源");
    studentClass->getCourseData(courseName,dataName,filePath);
}

string Student::getSchedule(string courseName)
{
    logger.addLogger("学生查询了课程进度");
    return studentClass->getSchedule(courseName);
}

string Student::getCourseGroup(string courseName)
{
    logger.addLogger("学生查询了课程群");
    return studentClass->getCourseGroup(courseName);
}

QStringList Student::getCourseDataName(string courseName)
{
    logger.addLogger("学生查询了课程资料");
    return studentClass->getCourseDataInfo(courseName);
}
void Student::submitHomework(string courseName,string homeworkName,string filePath)
{
    logger.addLogger("学生提交了作业");
    studentClass->submitHomework(courseName,homeworkName,filePath,userId);
}
QStringList Student::getHomeworkDone(string courseName)
{
    logger.addLogger("学生查询了已完成作业");
    return studentClass->getHomeworkDone(courseName,userId);
}

QStringList Student::getHomeworkTodo(string courseName)
{
    logger.addLogger("学生查询了未完成作业");
    return studentClass->getHomeworkTodo(courseName,userId);
}

QStringList Student::getExamInfo(string courseName)
{
    logger.addLogger("学生查询了考试");
    return studentClass->getExamInfo(courseName);
}
void Student::insertRecord(string event,MyTime startTime,MyTime endTime)
{
    logger.addLogger("学生增加了一条日程安排");
    calendar.addRecord(event,startTime,endTime);
}

void Student::updateRecord(string event,MyTime startTime,MyTime endTime)
{
    logger.addLogger("学生修改了一条日程安排");
    calendar.updateRecord(event,startTime,endTime);
}

void Student::deleteRecord(string event)
{
    logger.addLogger("学生删除了一条课程安排");
    calendar.deleteRecord(event);
}

void Student::clearRecords()
{
    logger.addLogger("学生清除了日程安排");
    calendar.clear();
}

QStringList Student::getRecords()
{
    logger.addLogger("学生查询日程安排");
    return calendar.getRecords();
}

bool Student::checkTimeConflict()
{
    logger.addLogger("学生查询了日程冲突");
    return calendar.checkTimeConflict();
}
