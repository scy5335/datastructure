#include "myclock.h"

MyClock::MyClock(QObject *parent)
    : QObject{parent}
{
    this->sysTime=MyTime(2022,1,1);
    this->secsPerSystemHour=10;
    this->alarms=new AlarmArr();
    this->heap=new Heap();
    connect(&timer,&QTimer::timeout,this,&MyClock::addOneMinute);
    connect(&timer,&QTimer::timeout,this,&MyClock::check);
    this->setParent(parent);
}

MyClock::MyClock(MyTime sysTime, double secsPerSystemHour)
{
    this->sysTime=sysTime;
    this->secsPerSystemHour=secsPerSystemHour;
    this->alarms=new AlarmArr();
    this->heap=new Heap();
    connect(&timer,&QTimer::timeout,this,&MyClock::addOneMinute);
    connect(&timer,&QTimer::timeout,this,&MyClock::check);
}

void MyClock::setTime(MyTime sysTime)
{
    this->sysTime=sysTime;
    emit timeChange();
}

MyTime MyClock::getTime()
{
    return sysTime;
}

void MyClock::setSecsPerSystemHour(double secsPerSystemHour)
{
    this->secsPerSystemHour=secsPerSystemHour;
    timer.start(secsPerSystemHour*1000/60);
}

double MyClock::getSecsPerSystemHour()
{
    return secsPerSystemHour;
}

void MyClock::start()
{
    timer.start(secsPerSystemHour*1000/60);
}

void MyClock::pause()
{
    timer.stop();
}

Alarm* MyClock::addAlarm(Alarm a)
{
    Alarm* temp = alarms->add(a);
    if(!temp)
    {
        return nullptr;
    }
    heap->push(temp);
    return temp;
}

void MyClock::rmAlarm(Alarm *a)
{
    if(a)
        a->state=state::DEL;
}

string MyClock::ringingAlarmTip()
{
    if(heap->front())
        return heap->front()->tip;
    return "error";
}


void MyClock::dayInit()
{
    heap->len=0;
    for(int i=0; i<alarms->len; i++)
    {
        if(alarms->arr[i].getState()!=state::DEL)
            heap->push(&alarms->arr[i]);
        else
        {
            alarms->memReuse.push(i);
        }
    }
}

void MyClock::check()
{
    emit timeChange();
    if(sysTime.getHour()==0&&sysTime.getMin()==0)
        dayInit();
    Alarm* front = heap->front();
    while(front &&(*front < sysTime||*front==sysTime||front->state==state::DEL))
    {
        if(front->state==state::DEL)
        {
            alarms->memReuse.push((front-alarms->arr)/sizeof(Alarm));
        }
        else if(*front==sysTime)
        {
            if(front->state==state::ON&&(front->type==type::single||front->valid(sysTime.getWeek0_6())))
            {
                //响铃
                qDebug()<<ringingAlarmTip().c_str();
                if(front->type==type::single)
                {
                    front->state=state::OFF;
                }
                emit ring(front->getTip());
            }
        }
        heap->pop();
        front = heap->front();
    }
}



void MyClock::addOneMinute()
{
    sysTime.minIncre(1);
}

void MyClock::saveFile()
{
    fstream ofs;
    ofs.open("clock.backup",ios::out|ios::trunc);
    if(!ofs.is_open())
    {
        qDebug()<<"时钟文件保存失败";
        return;
    }
    ofs<<sysTime.getYear()<<" "<<sysTime.getMonth()<<" "<<sysTime.getDay()<<" "<<sysTime.getHour()<<" "<<sysTime.getMin()<<" "<<secsPerSystemHour<<endl;
    ofs<<alarms->len<<endl;
    for(int i=0; i<alarms->len; i++)
    {
        ofs<<alarms->arr[i].h<<" "<<alarms->arr[i].m<<" "<<alarms->arr[i].type<<" "<<alarms->arr[i].state<<endl;
        ofs<<alarms->arr[i].tip<<endl;
    }
    ofs.close();
}

void MyClock::readFile()
{
    fstream ifs;
    ifs.open("clock.backup",ios::in);
    if(!ifs.is_open())
    {
        qDebug()<<"找不到时钟文件";
        return;
    }
    int temp;
    ifs>>temp, sysTime.setYear(temp);
    ifs>>temp, sysTime.setMonth(temp);
    ifs>>temp, sysTime.setDay(temp);
    ifs>>temp, sysTime.setHour(temp);
    ifs>>temp, sysTime.setMin(temp);
    ifs>>secsPerSystemHour;
    ifs>>temp;
    int h,m,type,state;
    char tip[205];
    alarms->clear();
    for(int i=0; i<temp; i++)
    {
        ifs>>h>>m>>type>>state;
        ifs.get();
        ifs.getline(tip,200);
        addAlarm(Alarm(h,m,type,state,tip));
    }
}

int MyClock::getWeek0_6()const{
    return sysTime.getWeek0_6();
}

MyClock::~MyClock()
{
}

Heap::Heap()
{
    heap = new Alarm*[maxLen];
    len=0;
}

Alarm *Heap::front()
{
    if(len!=0)
    {
        return heap[1];
    }
    else
        return NULL;
}

void Heap::push(Alarm *aPtr){
    if(len==maxLen-1)
        return;
    int i=++len;
    for (int f=i>>1;f&&*aPtr<*heap[f];i=f,f=i>>1)
        heap[i]=heap[f];
    heap[i]=aPtr;
}

void Heap::pop(){
    if(len==0)
        return;
    Alarm* k=heap[len--];
    int i=1;
    for (int a=i<<1,b=i<<1|1;a<=len;a=i<<1,b=i<<1|1)
    {
        if (b<=len&&*heap[b]<*heap[a])
            a=b;
        if (!(*heap[a]<*k))
            break;
        heap[i]=heap[a];
        i=a;
    }
    heap[i]=k;
}

Heap::~Heap()
{
    delete[] heap;
}

int AlarmArr::getLen()
{
    return len;
}

AlarmArr::AlarmArr()
{
    arr=new Alarm[maxLen];
    len=0;
}

Alarm *AlarmArr::add(Alarm a)
{
    int addIndex;
    if(memReuse.empty())
    {
        if(len==maxLen)
        {
            return NULL;
        }
        addIndex=len;
        len++;
    }
    else
    {
        addIndex=memReuse.front();
        memReuse.pop();
    }
    arr[addIndex]=a;
    return &arr[addIndex];
}

void AlarmArr::clear()
{
    len=0;
    while(!memReuse.empty())
    {
        memReuse.pop();
    }
}

AlarmArr::~AlarmArr()
{
    delete[] arr;
}
