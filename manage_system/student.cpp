#include "student.h"

int Student::getCourseId(string courseName)
{
    int courseId=0;
    string name;
    fstream file;
    file.open("course\\courseId.txt",ios::in);
    while(!file.eof()){
        file>>courseId>>courseName;
        if(courseName==name){
            file.close();
            return courseId;
        }
    }
    return courseId;
}
string Student::getCourseName(int courseId)
{
    int id=0;
    string name;
    fstream file;
    file.open("course\\courseId.txt",ios::in);
    while(!file.eof()){
        file>>id>>name;
        if(courseId==id){
            file.close();
            return name;
        }
    }
    return name;
}

Course *Student::getCourse(string courseName)
{
    int couseId=getCourseId(courseName);
    for(int i=0;i<courseNum;++i){
        if(couseId==course[i]->getCourseId()){
            return course[i];
        }
    }
}

Student::Student(int id):
    userId(id),logger("student\\"+to_string(id)+"_log.txt"),calendar(to_string(id)+"_calendar.txt")
{
    fstream file;
    file.open("student\\"+to_string(id)+"_course.txt",ios::in);//读取学生课程文件
    if(file.is_open()){
        int courseId[10];
        file>>courseNum;//文件第一个数据是课程科目
        for(int i=0;i<courseNum;++i){
            file>>courseId[i];
            course[i]=new Course(courseId[i],"course");
        }
    }
}

Student::~Student()
{

}

bool Student::login(int studentId, string password)
{
    int id;
    string pwd;
    fstream file("student\\studentInfo.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>id;
            file>>pwd;
            if(id==studentId&&password==pwd){
                file.close();
                return true;
            }
        }
        file.close();
        file.open("student\\studentInfo.txt",ios::app);
        if(file.is_open()){
            file<<studentId<<endl;
            file<<password<<endl;
            file.close();
        }
        /*创建学生课程文件*/
        file.open("student\\"+to_string(id)+"_course.txt",ios::out);
        if(file.is_open()){
            file<<0<<endl;//初始课程数目为0
            file.close();
        }
        file.open("student\\"+to_string(id)+"_logger.txt",ios::out);
        if(file.is_open()){
            file.close();
        }
        file.open("student\\"+to_string(id)+"_calendar.txt",ios::out);
        if(file.is_open()){
            file.close();
        }
    }
    return false;
}

QStringList Student::getAllCourseName()
{
    QStringList list;
    for(int i=0;i<courseNum;++i){
        list.append(QString::fromStdString(getCourseName(course[i]->getCourseId())));
    }
    return list;
}

void Student::getCourseTime(string courseName,int day,int timeTable[3])
{
    logger.addLogger("学生查询了课程时间");
    timeTable[0]=getCourse(courseName)->courseBeginHour(day-1);
    timeTable[1]=getCourse(courseName)->courseBeginMin(day-1);
    timeTable[2]=getCourse(courseName)->courseLast(day-1);
}

int Student::getCoursePlace(string courseName)
{
    logger.addLogger("学生查询了课程地点");
    /*地点标识类型为int*/
    return getCourse(courseName)->getLocale();
}

void Student::getCourseData(string courseName,string dataName,string filePath)
{
    logger.addLogger("学生查询了课程资源");
    getCourse(courseName)->dataSearch(dataName)->download(filePath);
}


string Student::getSchedule(string courseName)
{
    logger.addLogger("学生查询了课程进度");
    /*没有相应函数，尝试获取最后一个data的名称*/
    getCourse(courseName)->dataSort();
    return getCourse(courseName)->data[getCourse(courseName)->getDataNum()-1]->getName();
}

string Student::getCourseGroup(string courseName)
{
    logger.addLogger("学生查询了课程群");
    return getCourse(courseName)->getGroup();
}
void Student::submitHomework(string courseName,string homeworkName,string filePath)
{
    getCourse(courseName)->taskSearch(homeworkName)->submit(userId,filePath);
}
QStringList Student::getHomeworkDone(string courseName)
{
    logger.addLogger("学生查询了已完成作业");
    QStringList list;
    Course *c=getCourse(courseName);
    for(int i=0;i<c->getTaskNum();++i){
        /*haveIFinished函数返回值为0时，表示作业未完成,大于0表示完成*/
        Task *t=c->task[i];
        if(t->haveIFinished(userId)>0){
            list.append(QString::fromStdString(t->getName()));
            list.append(QString::fromStdString(t->getDesc()));
        }
    }
    return list;
}

QStringList Student::getHomeworkTodo(string courseName)
{
    logger.addLogger("学生查询了未完成作业");
    QStringList list;
    Course *c=getCourse(courseName);
    for(int i=0;i<c->getTaskNum();++i){
        /*haveIFinished函数返回值为0时，表示作业未完成,大于0表示完成*/
        Task *t=c->task[i];
        if(t->haveIFinished(userId)==0){
            list.append(QString::fromStdString(t->getName()));
            list.append(QString::fromStdString(t->getDesc()));
        }
    }
    return list;
}

QStringList Student::getExamInfo(string courseName)
{
    logger.addLogger("学生查询了考试");
    QStringList list;
    list.append(QString::fromStdString(getCourse(courseName)->getExamName()));
    list.append(getCourse(courseName)->getStartTime().toString());
    list.append(QString::number(getCourse(courseName)->getLastMinute()));
    list.append(QString::number(getCourse(courseName)->getLocale()));
    return list;
}

void Student::setClock()
{
    logger.addLogger("学生设置了一个闹钟");
}

void Student::getClock()
{
    logger.addLogger("学生查询了闹钟");
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
