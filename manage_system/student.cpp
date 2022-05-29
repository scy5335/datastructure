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
    logger("student\\"+to_string(id)+"_logger.txt"),
    calendar("student\\"+to_string(id)+"_calendar.txt"),
    studentClass(new Class(getClassId(id)))
{
//    /*将课程表导入日程表中，这是初始化操作，以便后续判断时间冲突*/
//    int day,timeTable[3];
//    QStringList list=studentClass->getAllCourseName();
//    for(int i=0;i<list.length();++i){
//        for(day=1;day<=5;++day){
//            studentClass->getCourseTime(list[i].toLocal8Bit().data(),day,timeTable);
//            /*下面生成时间年月日不好确定*/
//            MyTime *startTime=new MyTime(0,0,0,timeTable[0],timeTable[1]);
//            MyTime *endTime=new MyTime(0,0,0,timeTable[0],timeTable[1]);
//            endTime->minIncre(timeTable[2]*50-5);//计算课程总时间,默认课间没有户外活动
//            insertRecord("周"+to_string(day)+list[i].toLocal8Bit().data(),*startTime,*endTime);
//        }
//    }
}

Student::~Student()
{
    delete studentClass;
}

bool Student::enroll(int studentId, string password, int classId)
{
    int id=1,classID=2020211302;
    string pwd;
    fstream file("student\\studentInfo.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>id>>pwd>>classID;
            if(id==studentId){//学生账号存在
                file.close();
                return false;
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
//    /*创建学生日志文件*/
//    file.open("student\\"+to_string(id)+"_logger.txt",ios::out);
//    if(file.is_open()){
//        file.close();
//    }
//    /*创建学生日程表文件*/
//    file.open("student\\"+to_string(id)+"_calendar.txt",ios::out);
//    if(file.is_open()){
//        file.close();
//    }
    return false;
}

bool Student::login(int studentId, string password)
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
void Student::insertRecord(string event,MyTime startTime,MyTime endTime,int place,int type)
{
    logger.addLogger("学生增加了一条日程安排");
    calendar.addRecord(event,startTime,endTime,place,type);
}

void Student::updateRecord(string event,MyTime startTime,MyTime endTime,int place,int type)
{
    logger.addLogger("学生修改了一条日程安排");
    calendar.updateRecord(event,startTime,endTime,place,type);
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

    /*计算课程表*/
    int day,timeTable[3];
    int startTime[15]={0,800,850,950,1040,1130,1300,1350,1445,1540,1635,1725,1830,1920,2010};
    MyTime* courseTTb[15][8];//此处注意应当初始为null
    for(int i=0;i<15;++i){
        for(int j=0;j<8;++j){
            courseTTb[i][j]=NULL;
        }
    }
    QStringList list=studentClass->getAllCourseName();
    for(int i=0;i<list.length();++i){
        for(day=1;day<=7;++day){
            int cnt;
            studentClass->getCourseTime(list[i].toLocal8Bit().data(),day,timeTable);
            switch(timeTable[0]*100+timeTable[1]){
            case 800:cnt=1;break;
            case 850:cnt=2;break;
            case 950:cnt=3;break;
            case 1040:cnt=4;break;
            case 1130:cnt=5;break;
            case 1300:cnt=6;break;
            case 1350:cnt=7;break;
            case 1445:cnt=8;break;
            case 1540:cnt=9;break;
            case 1635:cnt=10;break;
            case 1725:cnt=11;break;
            case 1830:cnt=12;break;
            case 1920:cnt=13;break;
            case 2010:cnt=14;break;
            default:break;
            }
            for(int i=0;i<timeTable[2];++i){
                courseTTb[cnt+i][day]=new MyTime(0,0,0,startTime[cnt+i]/100,startTime[cnt+i]%100);
            }
        }
    }


    bool flag=calendar.checkTimeConflict(courseTTb);
    for(int i=0;i<15;++i){
        for(int j=0;j<8;++j){
            delete courseTTb[i][j];
        }
    }
    return flag;
}
