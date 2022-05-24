#ifndef CALENDAR_H
#define CALENDAR_H
#include<QDateTime>
#include<fstream>
#include "mytime.h"
using namespace std;

struct Record{
    string event;
    MyTime startTime;
    MyTime endTime;
    Record* next;
    Record():next(NULL)
    {
    }
    Record(string event,MyTime startTime,MyTime endTime):
        event(event),startTime(startTime),endTime(endTime),next(NULL)
    {
    }
};

class Calendar
{
private:
    string path;//日程表文件路径
    Record* head;//空头节点

    void getRecordFromfile();
    void updateFile();
public:
    Calendar(string path);
    ~Calendar();
    /*增加日程表记录*/
    void addRecord(string event,MyTime startTime,MyTime endTime);
    /*更新日程表记录*/
    void updateRecord(string event,MyTime startTime,MyTime endTime);
    /*删除特定日程安排,参数为事件*/
    void deleteRecord(string event);
    /*清除所有日程安排*/
    void clear();
    /*获取日程表文件所有记录*/
    QStringList getRecords();
    /*该函数只检测了课外活动是否冲突时间*/
    bool checkTimeConflict();
};

#endif // CALENDAR_H
