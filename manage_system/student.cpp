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
    /*���γ̱����ճ̱��У����ǳ�ʼ���������Ա�����ж�ʱ���ͻ*/
    int day,timeTable[3];
    QStringList list=studentClass->getAllCourseName();
    for(int i=0;i<list.length();++i){
        for(day=1;day<=5;++day){
            studentClass->getCourseTime(list[i].toStdString(),day,timeTable);
            /*��������ʱ�������ղ���ȷ��*/
            MyTime *startTime=new MyTime(0,0,0,timeTable[0],timeTable[1]);
            MyTime *endTime=new MyTime(0,0,0,timeTable[0],timeTable[1]);
            endTime->minIncre(timeTable[2]*50-5);//����γ���ʱ��,Ĭ�Ͽμ�û�л���
            insertRecord("��"+to_string(day)+list[i].toStdString(),*startTime,*endTime);
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
            if(id==studentId){//ѧ���˺Ŵ���
                file.close();
                return password==pwd;
            }
        }
        file.close();
    }
    /*�������ڸ�ѧ�������ݲ���classId����ѧ��ע���˺�*/
    file.open("student\\studentInfo.txt",ios::app);
    if(file.is_open()){
        file<<endl<<studentId;
        file<<endl<<password;
        file<<endl<<classId;
        file.close();
    }
    /*����ѧ����־�ļ�*/
    file.open("student\\"+to_string(id)+"_logger.txt",ios::out);
    if(file.is_open()){
        file.close();
    }
    /*����ѧ���ճ̱��ļ�*/
    file.open("student\\"+to_string(id)+"_calendar.txt",ios::out);
    if(file.is_open()){
        file.close();
    }
    return false;
}

QStringList Student::getAllCourseName()
{
    logger.addLogger("ѧ����ѯ�����пγ�����");
    return studentClass->getAllCourseName();
}

void Student::getCourseTime(string courseName,int day,int *timeTable)
{
    logger.addLogger("ѧ����ѯ�˿γ�ʱ��");
    studentClass->getCourseTime(courseName,day,timeTable);
}

int Student::getCoursePlace(string courseName)
{
    logger.addLogger("ѧ����ѯ�˿γ̵ص�");
    return studentClass->getCoursePlace(courseName);
}

void Student::getCourseData(string courseName,string dataName,string filePath)
{
    logger.addLogger("ѧ����ѯ�˿γ���Դ");
    studentClass->getCourseData(courseName,dataName,filePath);
}

string Student::getSchedule(string courseName)
{
    logger.addLogger("ѧ����ѯ�˿γ̽���");
    return studentClass->getSchedule(courseName);
}

string Student::getCourseGroup(string courseName)
{
    logger.addLogger("ѧ����ѯ�˿γ�Ⱥ");
    return studentClass->getCourseGroup(courseName);
}

QStringList Student::getCourseDataName(string courseName)
{
    logger.addLogger("ѧ����ѯ�˿γ�����");
    return studentClass->getCourseDataInfo(courseName);
}
void Student::submitHomework(string courseName,string homeworkName,string filePath)
{
    logger.addLogger("ѧ���ύ����ҵ");
    studentClass->submitHomework(courseName,homeworkName,filePath,userId);
}
QStringList Student::getHomeworkDone(string courseName)
{
    logger.addLogger("ѧ����ѯ���������ҵ");
    return studentClass->getHomeworkDone(courseName,userId);
}

QStringList Student::getHomeworkTodo(string courseName)
{
    logger.addLogger("ѧ����ѯ��δ�����ҵ");
    return studentClass->getHomeworkTodo(courseName,userId);
}

QStringList Student::getExamInfo(string courseName)
{
    logger.addLogger("ѧ����ѯ�˿���");
    return studentClass->getExamInfo(courseName);
}

void Student::insertRecord(string event,MyTime startTime,MyTime endTime)
{
    logger.addLogger("ѧ��������һ���ճ̰���");
    calendar.addRecord(event,startTime,endTime);
}

void Student::updateRecord(string event,MyTime startTime,MyTime endTime)
{
    logger.addLogger("ѧ���޸���һ���ճ̰���");
    calendar.updateRecord(event,startTime,endTime);
}

void Student::deleteRecord(string event)
{
    logger.addLogger("ѧ��ɾ����һ���γ̰���");
    calendar.deleteRecord(event);
}

void Student::clearRecords()
{
    logger.addLogger("ѧ��������ճ̰���");
    calendar.clear();
}

QStringList Student::getRecords()
{
    logger.addLogger("ѧ����ѯ�ճ̰���");
    return calendar.getRecords();
}

bool Student::checkTimeConflict()
{
    logger.addLogger("ѧ����ѯ���ճ̳�ͻ");
    return calendar.checkTimeConflict();
}
