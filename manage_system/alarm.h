#ifndef ALARM_H
#define ALARM_H

#include <QObject>
#include <QDebug>
#include<string>
#include"mytime.h"
using namespace std;
namespace type {
    const int mon = 0x1;
    const int tue = 0x2;
    const int wed = 0x4;
    const int thu = 0x8;
    const int fri = 0x10;
    const int sat = 0x20;
    const int sun = 0x40;
    const int everyday = 0x7F;
    const int single = 0x0;
}

namespace state{
    const int ON = 1;
    const int OFF = 2;
    const int DEL = 3;
}

class Alarm : public QObject
{
    Q_OBJECT
public:
    explicit Alarm(QObject *parent = nullptr);
    Alarm(int h, int m, int type, int initState, string tip);//使用type和state命名空间下的常量
    Alarm(const Alarm& a);
    void setType(int type);
    void setState(int state);
    void setTip(string tip);
    int getHour()const;
    int getMinute()const;
    int getType()const;
    int getState()const;
    string getTip()const;
    bool operator<(const Alarm& a)const;
    bool operator<(const MyTime& t)const;
    void operator=(const Alarm& a);
    bool operator==(const MyTime& t)const;
    friend class MyClock;
private:
    int h,m;//小时与分钟
    int type;
    int state;
    string tip;
    bool valid(int weekDay);//weekDay的范围是从0到6，对应星期一到日，用于检测周期闹钟这天是否应响铃

signals:


};

#endif // ALARM_H
