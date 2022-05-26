#ifndef CLASS_H
#define CLASS_H
#include <string>
#include<fstream>
#include "course.h"
using namespace std;

class Class
{
private:
    int classId;//�༶id
    int courseNum;//�γ���Ӧ���ɰ༶��¼
    Course **course;//�γ�ָ�������

    /*���ݿγ����ƻ�ȡ�γ�id*/
    int getCourseId(string courseName);
    /*���ݿγ�id��ȡ�γ�����*/
    string getCourseName(int courseId);
    Course *getCourse(string courseName);
public:
    Class(int classId);
    ~Class();

    /*�γ̹���*/
    /*�����γ�,����Ϊ�γ����ƺͿγ̵ص���*/
    static void addCourse(string courseName,int locale,int classId);
    /*ɾ���γ�,����Ϊ�γ�����*/
    void deleteCoure(string courseName);
    /*���ÿγ�ʱ���������Ϊ�ܼ�(1-7),��ʼСʱ,��ʼ����,�������ٽڿ�*/
    /*����趨ǰ����һ�ſ�һ��ֻ��һ�Σ�������������*/
    void setCourseTime(string courseName,int weekday,int startHour,int startMinute,int classes);
    /*���ÿγ�Ⱥ,��������Ϊ�γ����ƣ��γ�Ⱥ*/
    void setCourseGroup(string courseName,string courseGroup);
    /*��ȡ���пγ�����*/
    QStringList getAllCourseName();
    /*ѯ�ʿγ�ʱ��,����Ϊ�γ����ơ����ڼ�(1-7)�Լ����շ��ؽ���ĳ���Ϊ3������,�������δ�ſγ̿�ʼСʱ����ʼ���ӣ��������ڿ�*/
    void getCourseTime(string courseName,int day,int timeTable[3]);
    /*ѯ�ʿγ̵ص�,����Ϊ�γ�����,����ֵΪ�γ̵ص���*/
    int getCoursePlace(string courseName);
    /*ѯ�ʿγ̽���,����Ϊ�γ�����*/
    string getSchedule(string courseName);
    /*ѯ�ʿγ�Ⱥ,����Ϊ�γ�����*/
    string getCourseGroup(string courseName);

    /*�γ����Ϲ���*/
    /*�ϴ��γ�����,��������Ϊ�γ�����,��������,�����ļ�·��*/
    void uploadCourseData(string courseName,string dataName,string dataPath);
    /*��ȡ�γ���������,����ֵΪ���������б�*/
    QStringList getCourseDataInfo(string courseName);
    /*ɾ���γ�����,��������Ϊ�γ�����,��������*/
    void removeCourseData(string courseName,string dataName);
    /*���ؿγ�����,����Ϊ�γ�����,��������,����ļ�·��*/
    void downloadCourseData(string courseName,string dataName,string downloadPath);
    /*���ؿγ�����,��������Ϊ�γ�����,�������ƣ����·��*/
    void getCourseData(string courseName,string dataName,string filePath);

    /*���Թ���*/
    /*�������ԣ���������Ϊ���Կ�Ŀ,��������,��ʼʱ��,�ص㣬ʱ��*/
    void uploadExam(string courseName,string examName,MyTime startTime,int location,int duration);
    /*ȡ������,����Ϊ���Կ�Ŀ,���ڿγ���Ĭ��ֻ��¼һ�����ԣ����Ի�ɾ����ǰ����*/
    void deleteExam(string courseName);
    /*��ѯ����,����ֵ����Ϊ��������,��ʼʱ��,�ص�,ʱ��*/
    QStringList getExamInfo(string courseName);

    /*��ҵ����*/
    /*������ҵ����������Ϊ�γ�����,��ҵ����,��ֹʱ��,��ҵ����*/
    void uploadHomework(string courseName,string homeworkName,MyTime deadline,string description);
    /*ɾ����ҵ,��������Ϊ�γ�����,��ҵ����*/
    void deleteHomework(string courseName,string homeworkName);
    /*��ѯ��ҵ,����ֵ����Ϊ��ҵ����,��ֹʱ��,��ҵ����*/
    QStringList getHomework(string courseName);
    /*�ύ��ҵ,����Ϊ�γ�����,����ֵ�б�����Ϊ��ҵ���ƣ���ҵ�ļ�·��*/
    void submitHomework(string courseName,string homeworkName,string filePath,int userId);
    /*ѯ���������ҵ,����Ϊ�γ�����,����ֵ�б�����Ϊ��ҵ���ƣ���ҵ����...*/
    QStringList getHomeworkDone(string courseName,int userId);
    /*ѯ��δ�����ҵ,����Ϊ�γ�����,����ֵ�б�����Ϊ��ҵ���ƣ���ҵ����...*/
    QStringList getHomeworkTodo(string courseName,int userId);
};

#endif // CLASS_H
