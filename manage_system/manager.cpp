#include "manager.h"

int Manager::getCourseId(string course)
{
    int courseId=0;
    string courseName;
    fstream file;
    file.open("course\\courseId.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>courseId>>courseName;
            if(courseName==course){
                file.close();
                return courseId;
            }
        }
        if(file.eof()){//不存在该课程名称，则创造一个id
            courseId++;
            file.close();
            file.open("course\\courseId.txt",ios::app);
            if(file.is_open()){
                file<<courseId<<endl;
                file<<courseName<<endl;
            }
        }
    }
    return courseId;
}

Manager::Manager():id(0),logger("manager\\manager_logger.txt")
{

}

Manager::~Manager()
{

}

void Manager::addCourse(string courseName,int locale)
{
    logger.addLogger("管理员增加了一门课程");
    /*课程编号应该由课程文件产生*/
    Course c(getCourseId(courseName),locale,"course");
    c.saveFile();
}

void Manager::deleteCoure(string courseName)
{
    logger.addLogger("管理员删除了一门课程");
    Course c(getCourseId(courseName),"course");
    c.remove();
    c.saveFile();
    /*还应该修改课程编号和课程名称关系的文件，但是如果保证该门课程不再查询，则不会查询到该门课程id*/
}

void Manager::setCourseTime(string courseName,int weekday,int startHour,int startMinute,int classes)
{
    logger.addLogger("管理员设置了课程时间");
    Course c(getCourseId(courseName),"course");
    /*weekday-1是因为课程类函数的解释周一对应0*/
    c.setCourseTime(weekday-1,startHour,startMinute,classes);
    c.saveFile();
}

void Manager::setCourseGroup(string courseName,string courseGroup)
{
    Course c(getCourseId(courseName),"course");
    c.setGroup(courseGroup);
    c.saveFile();
}

void Manager::uploadCourseData(string courseName, string dataName, string dataPath)
{
    logger.addLogger("管理员上传了课程资料");
    Course c(getCourseId(courseName),"course");
    /*releaseData函数好像没有给出资料参数的位置,第三个参数本应为系统当前参数，这里没有获取系统当前时间的方法*/
    c.releaseData(dataName,dataPath,MyTime(2022,5,13));
    c.saveFile();
}

QStringList Manager::getCourseDataInfo(string courseName)
{
    logger.addLogger("管理员查询了课程资料");
    QStringList list;
    Course c(getCourseId(courseName),"course");
    int dataNum=c.getDataNum();
    for(int i=0;i<dataNum;++i){
        list.append(QString::fromStdString(c.data[i]->getName()));
    }
    return list;
}

void Manager::removeCourseData(string courseName, string dataName)
{
    logger.addLogger("管理员删除了课程资料");
    Course c(getCourseId(courseName),"course");
    c.dataRemove(c.dataSearch(dataName));
    c.saveFile();
}

void Manager::downloadCourseData(string courseName,string dataName,string downloadPath)
{
    logger.addLogger("管理员下载询了课程资料");
    Course c(getCourseId(courseName),"course");
    c.dataSearch(dataName)->download(downloadPath);
}

void Manager::uploadExam(string courseName, string examName, MyTime startTime, int location, int duration)
{
    logger.addLogger("管理员发布了考试");
    Course c(getCourseId(courseName),"course");
    c.setExamInfo(examName,startTime,location,duration);
    c.saveFile();
}

void Manager::deleteExam(string courseName)
{
    logger.addLogger("管理员删除了考试");
    Course c(getCourseId(courseName),"course");
    /*增加了取消考试函数*/
//    c.setExamInfo("无",MyTime(0,0,0),0,0);
    c.cancelExam();
    c.saveFile();
}

QStringList Manager::getExamInfo(string courseName)
{
    logger.addLogger("管理员查询了考试");
    QStringList list;
    Course c(getCourseId(courseName),"course");
    list.append(QString::fromStdString(c.getExamName()));
    list.append(c.getStartTime().toString());
    list.append(QString::number(c.getExamLocale()));
    list.append(QString::number(c.getLastMinute()));
    return list;
}

void Manager::uploadHomework(string courseName, string homeworkName, MyTime deadline, string description)
{
    logger.addLogger("管理员发布了作业");
    Course c(getCourseId(courseName),"course");
    /*下面releaseTask函数的获取当前系统时间的方法未给出*/
    c.releaseTask(homeworkName,MyTime(2022,5,13),deadline,description);
    c.saveFile();
}

void Manager::deleteHomework(string courseName, string homeworkName)
{
    logger.addLogger("管理员删除了作业");
    Course c(getCourseId(courseName),"course");
    c.taskRemove(c.taskSearch(homeworkName));
}

QStringList Manager::getHomework(string courseName)
{
    QStringList list;
    logger.addLogger("管理员查询了作业");
    Course c(getCourseId(courseName),"course");
    Task t;
    //数据残缺,无法获取task数目，只能通过判断空指针
    for(int i=0;i<c.getTaskNum();i++)
    {
        list.append(QString::fromStdString(c.task[i]->getName()));
        list.append(c.task[i]->setTime.toString());
        list.append(QString::fromStdString(c.task[i]->getDesc()));
        //这里只能查询到布置作业的名称和作业描述
    }
    return list;
}

void Manager::clearLogger()
{
    logger.clearLogger();
}

QStringList Manager::getLogger()
{
    return logger.getLogger();
}
