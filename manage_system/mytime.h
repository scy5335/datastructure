#ifndef MYTIME_H
#define MYTIME_H

#include<QTime>
#include<iostream>
using namespace std;
class MyTime
{
    unsigned short year;
    unsigned char month,day,hour,minute;
public:
    MyTime();

    MyTime(int year,int month, int day, int hour=0, int minute=0);

    MyTime(const MyTime& other);

    void operator=(const MyTime&a);

    void setYear(int year);

    void setMonth(int month);

    void setDay(int day);

    void setHour(int hour);

    void setMin(int minute);

    int getYear()const;

    int getMonth()const;

    int getDay()const;

    int getHour()const;

    int getMin()const;

    int getWeek0_6()const;

    bool isLeapYear()const;

    void dayIncOne();

    void yearIncre(int offset);

    void monthIncre(int offset);

    void dayIncre(int offset);

    void hourIncre(int offset);

    void minIncre(int offset);

    string toString();

    string toString(char*);

    bool operator<(const MyTime& b) const;

    bool dateEquals(const MyTime& b) const;

    bool timeEquals(const MyTime& b) const;

    bool operator==(const MyTime& b) const;

    string toByteStream();

    ~MyTime();

signals:

};

#endif // MYTIME_H
