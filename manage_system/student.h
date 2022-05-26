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
    Class *studentClass;//ѧ���༶

public:
    Student(int id);
    ~Student();

    /*��ȡѧ���༶id*/
    int getClassId(int studentId);

    /*��̬��Ա����,��¼��֤����id��������֤��ȷ������true������ע���˺�,Ĭ����2020211302��������*/
    static bool login(int studentId,string password,int classId=2020211302);

    /*�γ̹���*/
    /*��ȡ���пγ�����*/
    QStringList getAllCourseName();
    /*ѯ�ʿγ�ʱ��,����Ϊ�γ����ơ����ڼ�(1-7)�Լ����շ��ؽ���ĳ���Ϊ3������,�������δ�ſγ̿�ʼСʱ����ʼ���ӣ��������ڿ�*/
    void getCourseTime(string courseName,int day,int *timeTable);
    /*ѯ�ʿγ̵ص�,����Ϊ�γ�����,����ֵΪ�γ̵ص���*/
    int getCoursePlace(string courseName);
    /*ѯ�ʿγ̽���,����Ϊ�γ�����*/
    string getSchedule(string courseName);
    /*ѯ�ʿγ�Ⱥ,����Ϊ�γ�����*/
    string getCourseGroup(string courseName);

    /*�γ����Ϲ���*/
    /*��ȡ�γ���������,����ֵΪ���������б�*/
    QStringList getCourseDataName(string courseName);
    /*���ؿγ�����,��������Ϊ�γ�����,�������ƣ����·��*/
    void getCourseData(string courseName,string dataName,string filePath);

    /*��ҵ����*/
    /*�ύ��ҵ,����Ϊ�γ�����,����ֵ�б�����Ϊ��ҵ���ƣ���ҵ�ļ�·��*/
    void submitHomework(string courseName,string homeworkName,string filePath);
    /*ѯ���������ҵ,����Ϊ�γ�����,����ֵ�б�����Ϊ��ҵ���ƣ���ҵ����...*/
    QStringList getHomeworkDone(string courseName);
    /*ѯ��δ�����ҵ,����Ϊ�γ�����,����ֵ�б�����Ϊ��ҵ���ƣ���ҵ����...*/
    QStringList getHomeworkTodo(string courseName);

    /*���Թ���*/
    /*��ѯ���ԣ�����Ϊ�γ����ƣ�����ֵ�б�����Ϊ�������ƣ���ʼʱ�䣬�������ӣ����Եص�*/
    QStringList getExamInfo(string courseName);


    /*�ճ̱���*/
    /*�����ճ̰���,Ҫ���ճ̰��Ų�������,�����ˢ���ճ�,��������Ϊ�¼�,��ʼʱ�䣬����ʱ��*/
    void insertRecord(string event,MyTime startTime,MyTime endTime);
    /*�޸��ճ̰���,��������Ϊ�¼�,��ʼʱ�䣬����ʱ��*/
    void updateRecord(string event,MyTime startTime,MyTime endTime);
    /*ɾ���ض��ճ̰���,����Ϊ�¼�*/
    void deleteRecord(string event);
    /*��������ճ̰���*/
    void clearRecords();
    /*��ȡ�ճ��б�*/
    QStringList getRecords();
    /*����ճ̳�ͻ*/
    bool checkTimeConflict();
};

#endif // STUDENT_H
