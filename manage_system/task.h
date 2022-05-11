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
    Task(int parentCourseId, string name, MyTime setTime, MyTime deadline, string description, string parentCourseDir);//通过所属课程和作业名称完成对作业文件目录的定位，如果目录不存在，说明该作业不存在，创建该目录
    Task(int parentCourseId,string name,string parentCourseDir);
    void setDesciption(string description);
    void setSetTime(MyTime& time);
    void setDeadline(MyTime& time);
//    string& getFileAddr();

    //作业信息查询 学生视图
    int haveIFinished(unsigned long long id);
    //作业提交
    bool submit(unsigned long long id, string fileAddr);
    bool download(unsigned long long id, string downloadTo);
    bool readSubmittedList();
    bool saveSubmittedList();
    int readTaskBasicFile();//如果读取成功返回4，否则返回-1到3之间的一个数
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

