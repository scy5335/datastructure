#ifndef MYCLOCK_H
#define MYCLOCK_H

#include <QObject>
#include<QTimer>
#include<QDateTime>
#include"mytime.h"
#include"alarm.h"
#include<cstdio>
#include<queue>
#include<QDebug>
#include<fstream>

const int maxLen = 40;//最大闹钟数量

class Heap{
    Alarm** heap;
    int len;
    Heap();
    void push(Alarm* aPtr);
    Alarm* front();
    void pop();
    void adjustHeap(int index);
    void heapEstablish();
    ~Heap();
    friend class MyClock;
};

class AlarmArr{
public:
    Alarm *arr;
    int getLen();
private:
    int len;
    AlarmArr();
    ~AlarmArr();
    Alarm* add(Alarm a);
    void clear();
    std::queue<int> memReuse;
    friend class MyClock;
};

class MyClock : public QObject
{
    Q_OBJECT
public:
    explicit MyClock(QObject *parent = nullptr);
    /*可以直接通过alarms的arr数组去访问闹钟信息。
    当闹钟被标记为删除（即通过rmAlarm函数或者直接将某个闹钟的状态设置为DEL）时，该闹钟不会立刻消失。
    此闹钟将会在若干分钟后被放入回收队列，等待下次添加闹钟时复用这篇内存。所以读取闹钟时注意判断此闹钟是否标记为删除
    */
    AlarmArr* alarms;
    MyClock(MyTime sysTime, double secsPerSystemHour);
    //时间相关函数
    void setTime(MyTime sysTime);
    MyTime getTime();
    void setSecsPerSystemHour(double secsPerSystemHour);
    double getSecsPerSystemHour();
    void start();
    void pause();
    //闹钟相关函数
    Alarm* addAlarm(Alarm a);
    void rmAlarm(Alarm* a);
    string ringingAlarmTip();//可以通过该函数获取堆中最早的函数，用于ui类获取响铃闹钟的tip信息
    void saveFile();//保存到同目录的clock.backup文件中
    void readFile();
    ~MyClock();

private:
    MyTime sysTime;
    double secsPerSystemHour;
    Heap* heap;
    QTimer timer;
    void addOneMinute();
    void dayInit();
    void check();

signals:
    void ring(string description);//响铃闹钟信号
    void timeChange();//时间改变信号
};


#endif // MYCLOCK_H
