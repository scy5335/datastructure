#include "manager.h"

Manager::Manager():id(0),logger("manager\\manager_logger.txt")
{

}

Manager::~Manager()
{

}

void Manager::addCourse(string courseName,int locale,int classId)
{
    logger.addLogger("管理员增加了一门课程");
    Class::addCourse(courseName,locale,classId);
}

void Manager::deleteCoure(string courseName,int classId)
{
    logger.addLogger("管理员删除了一门课程");
    Class c(classId);
    c.deleteCoure(courseName);
}

void Manager::setCourseTime(string courseName,int weekday,int startHour,int startMinute,int classes,int classId)
{
    logger.addLogger("管理员设置了课程时间");
    Class c(classId);
    c.setCourseTime(courseName,weekday,startHour,startMinute,classes);
}

void Manager::setCourseGroup(string courseName,string courseGroup,int classId)
{
    logger.addLogger("管理员设置了课程群");
    Class c(classId);
    c.setCourseGroup(courseName,courseGroup);
}

void Manager::uploadCourseData(string courseName, string dataName, string dataPath,int classId)
{
    logger.addLogger("管理员上传了课程资料");
    Class c(classId);
    c.uploadCourseData(courseName,dataName,dataPath);
}

QStringList Manager::getCourseDataInfo(string courseName,int classId)
{
    logger.addLogger("管理员查询了课程资料");
    Class c(classId);
    return c.getCourseDataInfo(courseName);
}

void Manager::removeCourseData(string courseName, string dataName,int classId)
{
    logger.addLogger("管理员删除了课程资料");
<<<<<<< Updated upstream
    Class c(classId);
    c.removeCourseData(courseName,dataName);
=======
    Course c(getCourseId(courseName),"course");
    if(c.dataSearch(dataName)){
        c.dataRemove(c.dataSearch(dataName));
        c.saveFile();
    }

>>>>>>> Stashed changes
}

void Manager::downloadCourseData(string courseName,string dataName,string downloadPath,int classId)
{
    logger.addLogger("管理员下载询了课程资料");
<<<<<<< Updated upstream
    Class c(classId);
    c.downloadCourseData(courseName,dataName,downloadPath);
=======
    Course c(getCourseId(courseName),"course");
    if(c.dataSearch(dataName)){
        c.dataSearch(dataName)->download(downloadPath);
    }
>>>>>>> Stashed changes
}

void Manager::uploadExam(string courseName, string examName, MyTime startTime, int location, int duration,int classId)
{
    logger.addLogger("管理员发布了考试");
    Class c(classId);
    c.uploadExam(courseName,examName,startTime,location,duration);
}

void Manager::deleteExam(string courseName,int classId)
{
    logger.addLogger("管理员删除了考试");
    Class c(classId);
    c.deleteExam(courseName);
}

QStringList Manager::getExamInfo(string courseName,int classId)
{
    logger.addLogger("管理员查询了考试");
<<<<<<< Updated upstream
    Class c(classId);
    return c.getExamInfo(courseName);
=======
    QStringList list;
    Course c(getCourseId(courseName),"course");
    list.append(QString::fromStdString(c.getExamName()));
    list.append(QString::fromStdString(c.getStartTime().toString()));
    list.append(QString::number(c.getExamLocale()));
    list.append(QString::number(c.getLastMinute()));
    return list;
>>>>>>> Stashed changes
}

void Manager::uploadHomework(string courseName, string homeworkName, MyTime deadline, string description,int classId)
{
    logger.addLogger("管理员发布了作业");
    Class c(classId);
    c.uploadHomework(courseName,homeworkName,deadline,description);
}

void Manager::deleteHomework(string courseName, string homeworkName,int classId)
{
    logger.addLogger("管理员删除了作业");
    Class c(classId);
    c.deleteHomework(courseName,homeworkName);
}

QStringList Manager::getHomework(string courseName,int classId)
{
    logger.addLogger("管理员查询了作业");
<<<<<<< Updated upstream
    Class c(classId);
    return c.getHomework(courseName);
=======
    Course c(getCourseId(courseName),"course");
    Task t;
    //数据残缺,无法获取task数目，只能通过判断空指针
    for(int i=0;i<c.getTaskNum();i++)
    {
        list.append(QString::fromStdString(c.task[i]->getName()));
        list.append(QString::fromStdString(c.task[i]->deadline.toString()));
        list.append(QString::fromStdString(c.task[i]->getDesc()));
        //这里只能查询到布置作业的名称和作业描述
    }
    return list;
>>>>>>> Stashed changes
}

void Manager::clearLogger()
{
    logger.clearLogger();
}

QStringList Manager::getLogger()
{
    return logger.getLogger();
}
