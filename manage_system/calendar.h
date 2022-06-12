#ifndef CALENDAR_H
#define CALENDAR_H
#include<QDateTime>
#include<fstream>
#include "mytime.h"
#include "alarm.h"
using namespace std;

static int personalType=0;//个人活动
static int groupType=1;//集体活动

static string study="自习";
static string exercise="锻炼";
static string outgoing="外出";
static string classMeeting="班会";
static string groupWork="小组作业";
static string innovation="创新创业";
static string party="聚餐";
static string playGame="游戏";
static string sing="唱歌";

struct Record{
    string event;
    MyTime startTime;
    MyTime endTime;
    int place;
    int type;
    Record *next;
    Record():next(NULL)
    {
    }
    Record(string event,MyTime startTime,MyTime endTime,int place=0,int type=personalType):
        event(event),startTime(startTime),endTime(endTime),place(place),type(type),next(NULL)
    {
    }
    QStringList getRecordInfo();
};

class Calendar
{
private:
    string path;//日程表文件路径
    Record* head;//空头节点

    void readFile();
    void updateFile();
public:
    Calendar(string path);
    ~Calendar();
    /*增加日程表记录*/
    void addRecord(string event,MyTime startTime,MyTime endTime,int place=0,int type=personalType);
    /*更新日程表记录*/
    void updateRecord(string event,MyTime startTime,MyTime endTime,int place=0,int type=personalType);
    /*删除特定日程安排,参数为事件*/
    void deleteRecord(string event);
    /*清除所有日程安排*/
    void clear();
    /*获取日程表文件所有记录,列表依次为事件，开始时间，结束时间，地点*/
    QStringList getRecords(string name="",int type=-1);
    /*该函数只检测了课外活动是否冲突时间*/
    bool checkTimeConflict(MyTime* courseTTb[15][8]);
};

#endif // CALENDAR_H
