#ifndef TASK_H
#define TASK_H

#include <QObject>
#include"mytime.h"
#include<string>
#include<fstream>
#include<filesystem>
#include<queue>
#include<hfmtree.h>

using namespace std;
namespace fs = std::filesystem;

class Task : public QObject
{
    Q_OBJECT
public:
    MyTime setTime,deadline;
    explicit Task(QObject *parent = nullptr);
    Task(int parentCourseId, string name, MyTime setTime, MyTime deadline, string description, string parentCourseDir, QObject *parent);//ͨ�������γ̺���ҵ������ɶ���ҵ�ļ�Ŀ¼�Ķ�λ�����Ŀ¼�����ڣ�˵������ҵ�����ڣ�������Ŀ¼
    Task(int parentCourseId,string name,string parentCourseDir, QObject *parent);
    void setDesciption(string description);
    void setSetTime(MyTime& time);
    void setDeadline(MyTime& time);
//    string& getFileAddr();

    //��ҵ��Ϣ��ѯ ѧ����ͼ
    int haveIFinished(unsigned long long id);
    //��ҵ�ύ
    bool submit(unsigned long long id, string fileAddr);
    bool download(unsigned long long id, string downloadTo);
    bool readSubmittedList();
    bool saveSubmittedList();
    int readTaskBasicFile();//�����ȡ�ɹ�����4�����򷵻�-1��3֮���һ����
    bool saveTaskBasicFile();

    string getName();
    string getDesc();

    void remove();
    ~Task();


private:
    string name;
    string description;
    int parentCourseId;
    long long* submittedStuList;
    string directory;

signals:

};

#endif // TASK_H

