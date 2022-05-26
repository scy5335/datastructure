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

const int maxLen = 40;//�����������

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
    /*����ֱ��ͨ��alarms��arr����ȥ����������Ϣ��
    �����ӱ����Ϊɾ������ͨ��rmAlarm��������ֱ�ӽ�ĳ�����ӵ�״̬����ΪDEL��ʱ�������Ӳ���������ʧ��
    �����ӽ��������ɷ��Ӻ󱻷�����ն��У��ȴ��´��������ʱ������ƪ�ڴ档���Զ�ȡ����ʱע���жϴ������Ƿ���Ϊɾ��
    */
    AlarmArr* alarms;
    MyClock(MyTime sysTime, double secsPerSystemHour);
    //ʱ����غ���
    void setTime(MyTime sysTime);
    MyTime getTime();
    void setSecsPerSystemHour(double secsPerSystemHour);
    double getSecsPerSystemHour();
    void start();
    void pause();
    //������غ���
    Alarm* addAlarm(Alarm a);
    void rmAlarm(Alarm* a);
    string ringingAlarmTip();//����ͨ���ú�����ȡ��������ĺ���������ui���ȡ�������ӵ�tip��Ϣ
    void saveFile();//���浽ͬĿ¼��clock.backup�ļ���
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
    void ring(string description);//���������ź�
    void timeChange();//ʱ��ı��ź�
};


#endif // MYCLOCK_H
