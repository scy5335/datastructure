#include "myalarm.h"

MyAlarm::MyAlarm(QObject *parent)
    : QObject{parent}
{

}

MyAlarm::MyAlarm(int hour, int minute, QString tip, REPEAT repeat, STATE state, MyAlarm *nextAlarm)
{
    this->hour=hour;
    this->minute=minute;
    this->tip=tip;
    this->repeat=repeat;
    this->state=state;
    this->nextAlarm=nextAlarm;
    this->week=-1;
}

MyAlarm::MyAlarm(MyAlarm &a)
{
    this->hour=a.hour;
    this->minute=a.minute;
    this->tip=a.tip;
    this->repeat=a.repeat;
    this->state=a.state;
    this->nextAlarm=a.nextAlarm;
}

void MyAlarm::operator=(MyAlarm &a)
{
    this->hour=a.hour;
    this->minute=a.minute;
    this->tip=a.tip;
    this->repeat=a.repeat;
    this->state=a.state;
    this->nextAlarm=a.nextAlarm;
}

QString MyAlarm::toString()
{
    QString time = QTime(hour,minute).toString("hh:mm");
    switch(repeat)
    {
    case Single:
    {
        return "单次闹钟 时间为"+time+" 备注为:"+tip;
    }
    case EveryDay:
    {
        return "每日闹钟 时间为"+time+" 备注为"+tip;
    }
    default:
    {
        return "周次闹钟 时间为"+time+" 备注为"+tip;
    }
    }
}

void MyAlarm::setWeek(int weekNum)
{
    if(weekNum>=0&&weekNum<7)
        this->week=weekNum;
    else
        throw new _exception();
}


