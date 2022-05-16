#include "alarm.h"

Alarm::Alarm(QObject *parent)
    : QObject{parent}
{

}

Alarm::Alarm(int h, int m, int type, int initState, string tip)
{
    this->h = h;
    this->m = m;
    if((type>>7)!=0)
        this->type=type::single;
    else
        this->type=type;
    if(initState==state::ON||initState==state::OFF)
        this->state=initState;
    else this->state = state::OFF;
    this->tip="";
    for(int i=0; i<tip.length(); i++)
    {
        if(tip[i]=='\n'||tip[i]=='\r')
        {
            this->tip+=" ";
        }
        else
            this->tip+=tip[i];
    }
}

Alarm::Alarm(const Alarm &a)
{
    h=a.h;
    m=a.m;
    type=a.type;
    state=a.state;
    tip=a.tip;
}

void Alarm::setType(int type)
{
    if((type>>7)!=0)   this->type=type::single;
    else    this->type=type;
}

void Alarm::setState(int state)
{
    if(state==state::ON||state==state::OFF||state==state::DEL)
        this->state=state;
}

void Alarm::setTip(string tip)
{
    this->tip="";
    for(int i=0; i<tip.length(); i++)
    {
        if(tip[i]=='\n'||tip[i]=='\r')
        {
            this->tip+=" ";
        }
        else
            this->tip+=tip[i];
    }
}

int Alarm::getHour()const
{
    if(state!=state::DEL)
        return h;
    return -1;
}

int Alarm::getMinute()const
{
    if(state!=state::DEL)
        return m;
    return -1;
}

int Alarm::getType()const
{
    if(state!=state::DEL)
        return type;
    return -1;
}

int Alarm::getState()const
{
    if(state!=state::DEL)
        return state;
    return -1;
}

string Alarm::getTip()const
{
    if(state!=state::DEL)
        return tip;
    return "DEL alarm";
}

bool Alarm::valid(int weekDay)
{
    return type&(1<<weekDay);
}

bool Alarm::operator<(const Alarm &a)const
{
    return h<a.h||(h==a.h&&m<a.m)||this->state==state::DEL;
}

bool Alarm::operator<(const MyTime &t)const
{
    return h<t.getHour()||(h==t.getHour()&&m<t.getMin());
}

void Alarm::operator=(const Alarm &a)
{
    h=a.h;
    m=a.m;
    type=a.type;
    state=a.state;
    tip=a.tip;
}

bool Alarm::operator==(const MyTime &t)const
{
    return h == t.getHour()&&m==t.getMin();
}
