#include "calendar.h"

Calendar::Calendar(string path):
    path(path),
    head(new Record())
{
    head->next=NULL;
    /*读取文件初始化日程链表，成员函数通过链表来操作，直到析构才释放链表*/
    int startTime,endTime;
    int year1,month1,day1,hour1,minute1;
    int year2,month2,day2,hour2,minute2;
    string event;
    ifstream file(path,ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>startTime;
            file>>endTime;
            file>>event;
            minute1=startTime&0x0000003f;
            hour1=startTime  &0x000007c0;
            day1=startTime   &0x0000f800;
            month1=startTime &0x000f0000;
            year1=startTime  &0xfff00000;
            minute2=startTime&0x0000003f;
            hour2=startTime  &0x000007c0;
            day2=startTime   &0x0000f800;
            month2=startTime &0x000f0000;
            year2=startTime  &0xfff00000;
            addRecord(event,MyTime(year1,month1,day1,hour1,minute1),MyTime(year2,month2,day2,hour2,minute2));
        }
        file.close();
    }
}

Calendar::~Calendar()
{
    /*通过链表更新文件*/
    int startTime;
    int endTime;
    Record *temp=head->next;
    ofstream file(path,ios::out);
    if(file.is_open()){
        while(temp){
            head->next=temp->next;
            startTime=(temp->startTime.getYear()<<20)
                    |(temp->startTime.getMonth()<<16)
                    |(temp->startTime.getDay()<<11)
                    |(temp->startTime.getHour()<<6)
                    |(temp->startTime.getMin());
            endTime=(temp->endTime.getYear()<<20)
                    |(temp->endTime.getMonth()<<16)
                    |(temp->endTime.getDay()<<11)
                    |(temp->endTime.getHour()<<6)
                    |(temp->endTime.getMin());
            file<<startTime<<endl;
            file<<endTime<<endl;
            file<<temp->event<<endl;

            delete temp;
            temp=head->next;
        }
        file.close();
    delete head;
    }
}
void Calendar::addRecord(string event,MyTime startTime,MyTime endTime)
{
    Record* temp=head;
    Record* r=new Record(event,startTime,endTime);
    while(temp->next){
        if(startTime<temp->next->startTime){
            r->next=temp->next;
            temp->next=r;
            return;
        }
        else{
            temp=temp->next;
        }
    }
    temp->next=r;//此时temp即是最后一个节点
}
void Calendar::updateRecord(string event,MyTime startTime,MyTime endTime)
{
    Record* temp=head->next;
    while(temp){
        if(temp->event==event){
            temp->startTime=startTime;
            temp->endTime=endTime;
            temp->event=event;
            return;
        }
        else{
            temp=temp->next;
        }
    }
}
void Calendar::deleteRecord(string event)
{
    Record *preTemp=head,*temp=head->next;
    while(temp){
        if(temp->event==event){
            preTemp->next=temp->next;
            delete temp;
            return;
        }
        else{
            temp=temp->next;
            preTemp=preTemp->next;
        }
    }
}
void Calendar::clear()
{
    Record *temp=head->next;
    while(temp){
        head->next=temp->next;
        delete temp;
        temp=head->next;
    }
}
QStringList Calendar::getRecords()
{
    /*如何把日程链表转化为ui需要的列表?未完善*/
    QStringList list;
    Record *temp=head->next;
    while(temp){
        list.append(temp->startTime.toString());
        list.append(temp->endTime.toString());
        list.append(QString::fromStdString(temp->event));
        temp=temp->next;
    }
    return list;
}
bool Calendar::checkTimeConflict()
{
    Record *preTemp,*temp;
    preTemp=head->next;
    if(preTemp){
        temp=preTemp->next;
        while(temp&&preTemp->endTime<temp->startTime){
            preTemp=temp;
            temp=temp->next;
        }
        if(temp){//由于发生时间冲突退出循环
            return true;
        }
    }
    return false;
}
