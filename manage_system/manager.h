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

    /*�γ̹���*/
    /*�����γ�,����Ϊ�γ�����,�γ̵ص��źͰ༶id,�༶id��Χ��2020211301����2020211310*/
    void addCourse(string courseName,int locale,int classId);
    /*ɾ���γ�,����Ϊ�γ�����*/
    void deleteCoure(string courseName,int classId);
    /*���ÿγ�ʱ���������Ϊ�ܼ�(1-7),��ʼСʱ,��ʼ����,�������ٽڿ�*/
    /*����趨ǰ����һ�ſ�һ��ֻ��һ�Σ�������������*/
    void setCourseTime(string courseName,int weekday,int startHour,int startMinute,int classes,int classId);
    /*���ÿγ�Ⱥ,��������Ϊ�γ����ƣ��γ�Ⱥ*/
    void setCourseGroup(string courseName,string courseGroup,int classId);

    /*�γ����Ϲ���*/
    /*�ϴ��γ�����,��������Ϊ�γ�����,��������,�����ļ�·��*/
    void uploadCourseData(string courseName,string dataName,string dataPath,int classId);
    /*��ȡ�γ���������,����ֵΪ���������б�*/
    QStringList getCourseDataInfo(string courseName,int classId);
    /*ɾ���γ�����,��������Ϊ�γ�����,��������*/
    void removeCourseData(string courseName,string dataName,int classId);
    /*���ؿγ�����,����Ϊ�γ�����,��������,����ļ�·��*/
    void downloadCourseData(string courseName,string dataName,string downloadPath,int classId);

    /*���Թ���*/
    /*�������ԣ���������Ϊ���Կ�Ŀ,��������,��ʼʱ��,�ص㣬ʱ��*/
    void uploadExam(string courseName,string examName,MyTime startTime,int location,int duration,int classId);
    /*ȡ������,����Ϊ���Կ�Ŀ,���ڿγ���Ĭ��ֻ��¼һ�����ԣ����Ի�ɾ����ǰ����*/
    void deleteExam(string courseName,int classId);
    /*��ѯ����,����ֵ����Ϊ��������,��ʼʱ��,�ص�,ʱ��*/
    QStringList getExamInfo(string courseName,int classId);

    /*��ҵ����*/
    /*������ҵ����������Ϊ�γ�����,��ҵ����,��ֹʱ��,��ҵ����*/
    void uploadHomework(string courseName,string homeworkName,MyTime deadline,string description,int classId);
    /*ɾ����ҵ,��������Ϊ�γ�����,��ҵ����*/
    void deleteHomework(string courseName,string homeworkName,int classId);
    /*��ѯ��ҵ,����ֵ����Ϊ��ҵ����,��ֹʱ��,��ҵ����*/
    QStringList getHomework(string courseName,int classId);

    /*��־����*/
    /*�����־*/
    void clearLogger();
    /*��ȡ��־�б�*/
    QStringList getLogger();
};

#endif // MANAGER_H
