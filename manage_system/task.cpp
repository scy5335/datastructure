#include "task.h"

Task::Task(QObject *parent)
    : QObject{parent}
{

}



Task::Task(int parentCourseId, string name, MyTime setTime, MyTime deadline, string description, string parentCourseDir,QObject *parent)
{
    this->parentCourseId=parentCourseId;
    this->name=name;
    this->setTime=setTime;
    this->deadline=deadline;
    this->submittedStuList=new long long[200]();
    directory=parentCourseDir+"\\task_"+this->name;
    this->description=description;
    qDebug()<<"创建作业对象成功，路径为"<<directory.c_str();
    setParent(parent);
}

Task::Task(int parentCourseId, string name, string parentCourseDir, QObject *parent)
{
    this->parentCourseId=parentCourseId;
    this->name=name;
    this->submittedStuList=new long long[200]();
    directory=parentCourseDir+"\\task_"+this->name;
    if(!fs::exists(directory))
    {
        fs::create_directories(directory);
    }
    setParent(parent);
}




void Task::setDesciption(string description)
{
    this->description=description;
}

void Task::setSetTime(MyTime &time)
{
    this->setTime=time;
}

void Task::setDeadline(MyTime &time)
{
    this->deadline=time;
}

int Task::haveIFinished(unsigned long long id)
{
    if(submittedStuList[0]<0)
    {
        readSubmittedList();
    }
    for(int i=1; i<submittedStuList[0];i++)
    {
        if(id==submittedStuList[i])
        {
            return i;
        }
    }
    return 0;
}

bool Task::submit(unsigned long long id, string fileAddr)
{
    if(!haveIFinished(id))
    {
<<<<<<< HEAD
        //直接添� 到提交列表结尾
        submittedStuList[submittedStuList[0]++]=id;
        saveSubmittedList();
    }//否则不需要添� 到该列表
=======
        //直接添加到提交列表结尾
        submittedStuList[submittedStuList[0]++]=id;
        saveSubmittedList();
    }//否则不需要添加到该列表
>>>>>>> parent of b97e4d1 (学生课程表界面对接)
    //读取文件
    hfmCompress(fileAddr,this->directory+"\\"+to_string(id)+".task",nullptr,0);
    return true;
}

bool Task::download(unsigned long long id, string downloadTo)
{
    if(!haveIFinished(id))
        return false;
    hfmDecode(this->directory+"\\"+to_string(id)+".task",downloadTo,nullptr);//未完成
    return 0;
}

bool Task::readSubmittedList()
{
    fstream fst;
    fst.open(this->directory+"\\"+"list.txt",ios::in);
    if(!fst.is_open())
        return false;
    int i=1;
    long long studentId;
    while(fst>>studentId)
    {
        submittedStuList[i]=studentId;
//        qDebug()<<submittedStuList[i];
        i++;
    }
    submittedStuList[0]=i;
    return true;
}

bool Task::saveSubmittedList()
{
    if(!fs::exists(directory))
    {
        fs::create_directories(directory);
    }
    fstream ofs;
    ofs.open(this->directory+"\\"+"list.txt",ios::out);
    if(!ofs.is_open())
        return false;
    for(int i=1;i<submittedStuList[0];i++)
    {
        ofs<<submittedStuList[i]<<" ";
        if(i%10==0)
            ofs<<endl;
    }
    return true;
}

int Task::readTaskBasicFile()
{
    fstream fst;
    fst.open(this->directory+"\\"+"basic.txt",ios::in);
    string temp;
    bool flag[4]={0};
    if(fst.is_open())
    {
        while(fst>>temp)
        {
            if(temp=="name:")
            {
                fst>>this->name;
                flag[0]=true;
            }
            else if(temp=="description:")
            {
                this->description="";
                int i=0;
                while(getline(fst,temp)&&temp!="ENDENDENDENDEND;")
                {
                    if(i!=0)
                        description+="\n";
                    if(temp!="\n")
                    {
                        description+=temp;
                    }
                }
                flag[1]=true;
            }
            else if(temp=="setTime:")
            {
                int num;
                fst>>num;
                this->setTime.setYear(num);
                fst>>num;
                this->setTime.setMonth(num);
                fst>>num;
                this->setTime.setDay(num);
                fst>>num;
                this->setTime.setHour(num);
                fst>>num;
                this->setTime.setMin(num);
                flag[2]=true;
            }
            else if(temp=="deadline:")
            {
                int num;
                fst>>num;
                this->deadline.setYear(num);
                fst>>num;
                this->deadline.setMonth(num);
                fst>>num;
                this->deadline.setDay(num);
                fst>>num;
                this->deadline.setHour(num);
                fst>>num;
                this->deadline.setMin(num);
                flag[3]=true;
            }
        }
        int i;
        for(i=0;i<4&&flag[i];i++);
        fst.close();
        return i;
    }
    else
    {
        return -1;
    }
}

bool Task::saveTaskBasicFile()
{
    if(!fs::exists(directory))
    {
        fs::create_directories(directory);
    }
    fstream ofs;
    ofs.open(this->directory+"\\"+"basic.txt",ios::out|ios::trunc);
    if(!ofs.is_open())
    {
        return false;
    }
    ofs<<"name: "<<this->name<<endl;

    ofs<<"description: "<<this->description<<endl<<"ENDENDENDENDEND;"<<endl;

    ofs<<"setTime: "<<this->setTime.getYear()<<" "
      <<setTime.getMonth()<<" "<<setTime.getDay()<<" "
     <<setTime.getHour()<<" "<<setTime.getMin()<<endl;

    ofs<<"deadline: "<<this->deadline.getYear()<<" "
      <<deadline.getMonth()<<" "<<deadline.getDay()<<" "
     <<deadline.getHour()<<" "<<deadline.getMin()<<endl;
    return true;
}

string Task::getName()
{
    return name;
}

string Task::getDesc()
{
    return description;
}


void Task::remove()
{
    fs::remove_all(this->directory);
//    fs::remove();
    this->name="none";
}

Task::~Task()
{
    delete[] submittedStuList;
}
