#include "manager.h"

Manager::Manager():id(0),logger("manager\\manager_logger.txt")
{

}

Manager::~Manager()
{

}

void Manager::addCourse(string courseName,int locale,int classId)
{
    logger.addLogger("����Ա������һ�ſγ�");
    Class::addCourse(courseName,locale,classId);
}

void Manager::deleteCoure(string courseName,int classId)
{
    logger.addLogger("����Աɾ����һ�ſγ�");
    Class c(classId);
    c.deleteCoure(courseName);
}

void Manager::setCourseTime(string courseName,int weekday,int startHour,int startMinute,int classes,int classId)
{
    logger.addLogger("����Ա�����˿γ�ʱ��");
    Class c(classId);
    c.setCourseTime(courseName,weekday,startHour,startMinute,classes);
}

void Manager::setCourseGroup(string courseName,string courseGroup,int classId)
{
    logger.addLogger("����Ա�����˿γ�Ⱥ");
    Class c(classId);
    c.setCourseGroup(courseName,courseGroup);
}

void Manager::uploadCourseData(string courseName, string dataName, string dataPath,int classId)
{
    logger.addLogger("����Ա�ϴ��˿γ�����");
    Class c(classId);
    c.uploadCourseData(courseName,dataName,dataPath);
}

QStringList Manager::getCourseDataInfo(string courseName,int classId)
{
    logger.addLogger("����Ա��ѯ�˿γ�����");
    Class c(classId);
    return c.getCourseDataInfo(courseName);
}

void Manager::removeCourseData(string courseName, string dataName,int classId)
{
    logger.addLogger("����Աɾ���˿γ�����");
    Class c(classId);
    c.removeCourseData(courseName,dataName);
}

void Manager::downloadCourseData(string courseName,string dataName,string downloadPath,int classId)
{
    logger.addLogger("����Ա����ѯ�˿γ�����");
    Class c(classId);
    c.downloadCourseData(courseName,dataName,downloadPath);
}

void Manager::uploadExam(string courseName, string examName, MyTime startTime, int location, int duration,int classId)
{
    logger.addLogger("����Ա�����˿���");
    Class c(classId);
    c.uploadExam(courseName,examName,startTime,location,duration);
}

void Manager::deleteExam(string courseName,int classId)
{
    logger.addLogger("����Աɾ���˿���");
    Class c(classId);
    c.deleteExam(courseName);
}

QStringList Manager::getExamInfo(string courseName,int classId)
{
    logger.addLogger("����Ա��ѯ�˿���");
    Class c(classId);
    return c.getExamInfo(courseName);
}

void Manager::uploadHomework(string courseName, string homeworkName, MyTime deadline, string description,int classId)
{
    logger.addLogger("����Ա��������ҵ");
    Class c(classId);
    c.uploadHomework(courseName,homeworkName,deadline,description);
}

void Manager::deleteHomework(string courseName, string homeworkName,int classId)
{
    logger.addLogger("����Աɾ������ҵ");
    Class c(classId);
    c.deleteHomework(courseName,homeworkName);
}

QStringList Manager::getHomework(string courseName,int classId)
{
    logger.addLogger("����Ա��ѯ����ҵ");
    Class c(classId);
    return c.getHomework(courseName);
}

void Manager::clearLogger()
{
    logger.clearLogger();
}

QStringList Manager::getLogger()
{
    return logger.getLogger();
}

