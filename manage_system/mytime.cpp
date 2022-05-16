#include "mytime.h"
const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
MyTime::MyTime(QObject *parent)
    : QObject{parent}
{

}

MyTime::MyTime(int year, int month, int day, int hour, int minute)
{
    this->year = year;
    this->month = month - 1;
    this->day = day - 1;
    this->hour = hour;
    this->minute = minute;
}

MyTime::MyTime(const MyTime &other)
{
    this->year=other.year;
    this->month=other.month;
    this->day=other.day;
    this->hour=other.hour;
    this->minute=other.minute;
}


void MyTime::operator=(const MyTime&a)
{
    this->year=a.year;
    this->month=a.month;
    this->day=a.day;
    this->hour=a.hour;
    this->minute=a.minute;
}

void MyTime::setYear(int year)
{
    if(year>=0)
        this->year = year;
    else
        this->year=0;
}

void MyTime::setMonth(int month)
{
    if(month>0&&month<=12)
        this->month = month - 1;
    else if(month<1)
        this->month=0;
    else
        this->month=11;
}

void MyTime::setDay(int day)
{
    if(day>0&&day<=days[this->month])
        this->day = day - 1;
    else if(day<=0)
        this->day=0;
    else
        this->day=days[this->month]-1+(isLeapYear()&&this->month==1);
}

void MyTime::setHour(int hour)
{
    this->hour = hour;
}

void MyTime::setMin(int minute)
{
    this->minute = minute;
}

int MyTime::getYear()const
{
    return year;
}

int MyTime::getMonth()const
{
    return month + 1;
}

int MyTime::getDay()const
{
    return day + 1;
}

int MyTime::getHour()const
{
    return hour;
}

int MyTime::getMin()const
{
    return minute;
}

bool MyTime::isLeapYear()const
{
    return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

int MyTime::getWeek0_6()const
{
    int y = year, m = month + 1, d = day + 1;
    if (m == 1 || m == 2)
        y--, m += 12;
    int c = y / 100;
    y = y - c * 100;
    int week = c / 4 - 2 * c + y + y / 4 + (26 * (m + 1) / 10) + d - 1;
    week= (week % 7 + 7) % 7;
    if(0<week&&week<7)
    {
        week--;
    }
    else if(week==0)
    {
        week=6;
    }
    return week;
}

void MyTime::dayIncOne()
{
    int temp = day + 1;
    day = temp % days[month];
    if (temp >= days[month])
    {
        monthIncre(1);
    }
}

void MyTime::yearIncre(int offset)
{
    year += offset;
}

void MyTime::monthIncre(int offset)
{
    int temp = month + offset;
    month = temp % 12;
    yearIncre(temp / 12);
}

void MyTime::dayIncre(int offset)
{
    while (offset--)
    {
        dayIncOne();
    }
}

void MyTime::hourIncre(int offset)
{
    int temp = hour + offset;
    hour = temp % 24;
    dayIncre(temp / 24);
}

void MyTime::minIncre(int offset)
{
    int temp = minute + offset;
    minute = temp % 60;
    hourIncre(temp / 60);
}

string MyTime::toString()
{
    QString date = QDate(year,this->getMonth(),this->getDay()).toString("yyyy-MM-dd");
    QString time = QTime(hour,minute).toString("HH:mm");
    return date.toStdString()+" "+time.toStdString();
}

string MyTime::toString(char *format)
{
    QString dateTime = QDateTime(QDate(year,getMonth(),getDay()),QTime(hour,minute)).toString(format);
    return dateTime.toStdString();
}

bool MyTime::operator<(const MyTime &b)const
{
    if(this->year!=b.year)
        return this->year<b.year;
    if(this->month!=b.month)
        return this->month<b.month;
    if(this->day!=b.day)
        return this->day<b.day;
    if(this->hour!=b.hour)
        return this->hour<b.hour;
    return this->minute<b.minute;
}

bool MyTime::dateEquals(const MyTime &b) const
{
    return year==b.year&&month==b.month&&day==b.day;
}

bool MyTime::timeEquals(const MyTime &b) const
{
    return hour==b.hour&&minute==b.minute;
}

bool MyTime::operator==(const MyTime &b) const
{
    return dateEquals(b)&&timeEquals(b);
}
