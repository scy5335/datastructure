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
    string path;//id所属用户的日程表文件路径
    Record* head;//空头节点
public:
    Calendar(string path);
    ~Calendar();
    void addRecord(string event,MyTime startTime,MyTime endTime);
    void updateRecord(string event,MyTime startTime,MyTime endTime);
    void deleteRecord(string event);
    void clear();
    QStringList getRecords();
    /*该函数只检测了课外活动是否冲突时间*/
    bool checkTimeConflict();
};

#endif // CALENDAR_H
