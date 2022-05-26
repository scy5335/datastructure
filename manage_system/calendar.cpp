#include "calendar.h"

void Calendar::getRecordFromfile()
{
    /*读取文件初始化日程链表，成员函数通过链表来操作，直到析构才释放链表*/
    int year1,month1,day1,hour1,minute1;
    int year2,month2,day2,hour2,minute2;
    string event;
    ifstream file(path,ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>year1>>month1>>day1>>hour1>>minute1;
            file>>year2>>month2>>day2>>hour2>>minute2;
            file>>event;
            addRecord(event,MyTime(year1,month1,day1,hour1,minute1),MyTime(year2,month2,day2,hour2,minute2));
        }
        file.close();
    }
}

void Calendar::updateFile()
{
    /*通过链表更新文件*/
    Record *temp=head->next;
    ofstream file(path,ios::out);
    if(file.is_open()){
        while(temp){
            file<<endl<<temp->startTime.getYear();
            file<<endl<<temp->startTime.getMonth();
            file<<endl<<temp->startTime.getDay();
            file<<endl<<temp->startTime.getHour();
            file<<endl<<temp->startTime.getMin();
            file<<endl<<temp->endTime.getYear();
            file<<endl<<temp->endTime.getMonth();
            file<<endl<<temp->endTime.getDay();
            file<<endl<<temp->endTime.getHour();
            file<<endl<<temp->endTime.getMin();
            file<<endl<<temp->event;
            temp=temp->next;
        }
        file.close();
    }
}

Calendar::Calendar(string path):
    path(path),
    head(new Record())
{
    head->next=NULL;
    getRecordFromfile();
}

Calendar::~Calendar()
{
    updateFile();
    Record *temp=head;
    while(temp){
        head=temp->next;
        delete temp;
        temp=head;
    }
}
void Calendar::addRecord(string event,MyTime startTime,MyTime endTime)
{
    Record* temp=head;
    Record* r=new Record(event,startTime,endTime);
    while(temp->next){
        if(event==temp->next->event)//不允许重名
            return;
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
        list.append(QString::fromStdString(temp->startTime.toString()));
        list.append(QString::fromStdString(temp->endTime.toString()));
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
