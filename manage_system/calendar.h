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
    string path;//�ճ̱��ļ�·��
    Record* head;//��ͷ�ڵ�

    void getRecordFromfile();
    void updateFile();
public:
    Calendar(string path);
    ~Calendar();
    /*�����ճ̱��¼*/
    void addRecord(string event,MyTime startTime,MyTime endTime);
    /*�����ճ̱��¼*/
    void updateRecord(string event,MyTime startTime,MyTime endTime);
    /*ɾ���ض��ճ̰���,����Ϊ�¼�*/
    void deleteRecord(string event);
    /*��������ճ̰���*/
    void clear();
    /*��ȡ�ճ̱��ļ����м�¼*/
    QStringList getRecords();
    /*�ú���ֻ����˿����Ƿ��ͻʱ��*/
    bool checkTimeConflict();
};

#endif // CALENDAR_H
ckTimeConflict();
};

#endif // CALENDAR_H
