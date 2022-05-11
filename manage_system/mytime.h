#ifndef MYTIME_H
#define MYTIME_H

#include <QObject>
#include<QTime>
#include<iostream>
using namespace std;
class MyTime : public QObject
{
    Q_OBJECT
    unsigned short year;
    unsigned char month,day,hour,minute;
public:
    explicit MyTime(QObject *parent = nullptr);

    MyTime(int year,int month, int day, int hour=0, int minute=0);

    MyTime(const MyTime& other);

    void operator=(const MyTime&a);

    void setYear(int year);

    void setMonth(int month);

    void setDay(int day);

    void setHour(int hour);

    void setMin(int minute);

    int getYear();

    int getMonth();

    int getDay();

    int getHour();

    int getMin();

    int getWeek0_6();

    bool isLeapYear();

    void dayIncOne();

    void yearIncre(int offset);

    void monthIncre(int offset);

    void dayIncre(int offset);

    void hourIncre(int offset);

    void minIncre(int offset);

    QString toString();

    QString toString(char*);

    bool operator<(const MyTime& b) const;

    bool dateEquals(const MyTime& b) const;

    bool timeEquals(const MyTime& b) const;

    bool operator==(const MyTime& b) const;

signals:

};

#endif // MYTIME_H
