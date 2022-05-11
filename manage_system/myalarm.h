#ifndef MYALARM_H
#define MYALARM_H

#include <QObject>
#include<QTime>
enum REPEAT{Single, EveryDay, EveryWeek};
enum STATE{OFF,ON,DEL};
class MyAlarm : public QObject
{
    Q_OBJECT
public:
    explicit MyAlarm(QObject *parent = nullptr);

    int hour,minute;
    QString tip;
    REPEAT repeat;
    STATE state;
    MyAlarm* nextAlarm;
    int week;
    MyAlarm(int hour,int minute,QString tip="",REPEAT repeat=Single, STATE state=OFF, MyAlarm* nextAlarm=NULL);
    MyAlarm(MyAlarm &a);
    void operator=(MyAlarm&a);
    void ring();//slot函数
    QString toString();
    void setWeek(int weekNum);//周1到周日对应0-6

private:


signals:



};

#endif // MYALARM_H
