#include "course.h"

Course::Course(QObject *parent)
    : QObject{parent}
{

}

Course::Course(unsigned courseId, unsigned locale, string root)
{
    this->courseId = courseId;
    this->locale =locale;
    this->dir=root+"\\course_"+to_string(courseId);
    this->taskNum=0;
    this->dataNum=0;
    need2save = false;
    if(!fs::exists(dir))
    {
        fs::create_directories(dir);
    }
    memset(weekTable,0,7*sizeof(unsigned));
    this->examName = "uninitialized";
    this->group = "uninitialized";
}

Course::Course(unsigned courseId, string root)
{
    this->courseId = courseId;
    this->dir=root+"\\course_"+to_string(courseId);
    this->taskNum=0;
    this->dataNum=0;
    if(!fs::exists(dir))
    {
        qDebug()<<"未找到该课程路径，请检查该课程是否存在";
        memset(weekTable,0,7*sizeof(unsigned));
        this->examName = "uninitialized";
        this->group = "uninitialized";
    }
    else
    {
        this->readFile();
    }
}




void Course::setLocale(int locale)
{
    this->locale=locale;
    need2save=true;
}

void Course::setCourseTime(unsigned char weekDay, unsigned char hour, unsigned char min, unsigned char lastHour)
{
    unsigned short temp = hour*1000+min*10+lastHour;
    weekTable[weekDay]=temp;
    need2save=true;
}


void Course::setGroup(string group)
{
    this->group = group;
    need2save=true;
}

Task *Course::releaseTask(string taskName, MyTime sysTime, MyTime deadline, string description)
{
    //查找同名作业
    Task*temp = taskSearch(taskName);
    if(temp)
    {
        qDebug()<<"该作业已存在";
        return nullptr;
    }
    if(taskNum<listLen)
    {
        task[taskNum] = new Task(courseId,taskName,sysTime,deadline,description,dir,this);
        taskNum++;
        need2save=true;
        return task[taskNum-1];
    }
    return nullptr;
}

void Course::setExamInfo(string examName, MyTime startTime, int locale, int lastMinute)
{
    this->examName=examName;
    this->startTime=startTime;
    this->examLocale=locale;
    this->lastMinute=lastMinute;
    need2save=true;
}

void Course::setRoot(string root)
{
    this->dir=root+"\\course_"+to_string(courseId);
    need2save=true;
}

void Course::cancelExam()
{
    need2save=true;
    this->examName="uninitialized";
    need2save = true;
}

unsigned Course::getCourseId()
{
    return courseId;
}


unsigned Course::getLocale()
{
    return locale;
}

int Course::courseBeginHour(int day)
{
    return weekTable[day]/1000;
}

int Course::courseBeginMin(int day)
{
    return (weekTable[day]%1000)/10;
}

int Course::courseLast(int day)
{
    return weekTable[day]%10;
}



int Course::getTotalHour()
{
    int perWeek=0;
    for(int i=0;i<7;i++)
    {
        perWeek+=courseLast(i);
    }
    return perWeek*16;
}

string Course::getGroup()
{
    return group;
}

string Course::getExamName()
{
    return examName;
}

int Course::getExamLocale()
{
    return examLocale;
}

MyTime Course::getStartTime()
{
    return startTime;
}

int Course::getLastMinute()
{
    return lastMinute;
}

Data* Course::releaseData(string dataName, string fileAddr, MyTime sysTime)
{
    Data* tmp = dataSearch(dataName);
    if(tmp)
    {
        qDebug()<<"该资料已存在，将更新该资料";
        tmp->upload(sysTime,fileAddr);
        return tmp;
    }
    if(dataNum<listLen)
    {
        data[dataNum] = new Data(dataName,dir,this);
        data[dataNum]->upload(sysTime,fileAddr);
        dataNum++;
        need2save=true;
        return data[dataNum-1];
    }
    return nullptr;

}

void Course::taskReadIn(string name)
{
    if(taskNum<listLen)
    {
        task[taskNum]=new Task(courseId,name,dir,this);
        if(task[taskNum]->readTaskBasicFile()!=4)
        {
            qDebug()<<name.c_str()<<"作业读取失败";
            return;
        }
        task[taskNum]->readSubmittedList();
        taskNum++;
    }
    else
    {
        qDebug()<<"已读入"<<taskNum<<"个课程，已超出上限";
    }
}

void Course::dataReadIn(string name)
{
    if(dataNum>=listLen)
    {
        qDebug()<<"dataList空间不足";
        return;
    }
    data[dataNum] = new Data(name,dir,this);
    data[dataNum]->getSetTime();
    dataNum++;
}

void Course::saveFile()
{
    if(!fs::exists(dir))
    {
        fs::create_directories(dir);
    }
    fstream ofs;
    ofs.open(dir+"\\courseInfo.txt",ios::out|ios::trunc);
    ofs<<locale<<" "<<courseId<<endl;
    int i;
    for(i=0;i<7;i++)
    {
        ofs<<weekTable[i]<<" ";
    }
    ofs<<group<<endl;
    for(i=0;i<taskNum;i++)
    {
        ofs<<task[i]->getName()<<endl;
        //作业保存
        task[i]->saveTaskBasicFile();
        task[i]->saveSubmittedList();
    }
    ofs<<"data:"<<endl;
    for(i=0;i<dataNum;i++)
    {
        ofs<<data[i]->getName()<<endl;
        //无需单独资料保存
    }
    ofs<<"exam:"<<endl;
    if(examName=="uninitialized")
    {
        ofs<<examName<<endl;
    }
    else
    {
        ofs<<examName<<endl<<examLocale<<" "<<startTime.getYear()<<" "
          <<startTime.getMonth()<<" "<<startTime.getDay()<<" "
         <<startTime.getHour()<<" "<<startTime.getMin()<<" "<<lastMinute<<endl;
    }
    need2save=false;
    ofs.close();
}

void Course::readFile()
{
    if(need2save==true)
    {
        qDebug()<<"数据尚未保存，读取可能造成数据丢失";
    }
    taskNum=0;
    dataNum=0;
    if(!fs::exists(dir))
    {
        return;
    }
    fstream ifs;
    ifs.open(dir+"\\courseInfo.txt",ios::in);
    if(!ifs.is_open())
    {
        qDebug()<<"读取课程文件失败";
        return;
    }
    ifs>>locale>>courseId;
    int i;
    for(i=0;i<7;i++)
    {
        ifs>>weekTable[i];
    }
    ifs>>group;
    string temp;
    char Str[100];
    ifs.getline(Str,100);//读掉一个换行符
    ifs.getline(Str,100);
    temp=Str;
    for(i=0;temp!="data:";i++)
    {
        taskReadIn(temp);
        ifs.getline(Str,100);
        temp=Str;
    }
    ifs.getline(Str,100);
    temp=Str;
    for(i=0;temp!="exam:";i++)
    {
        dataReadIn(temp);
        ifs.getline(Str,100);
        temp=Str;
    }
    ifs.getline(Str,100);
    examName = Str;
    if(examName != "uninitialized")
    {
        ifs>>examLocale;
        int t;
        ifs>>t, startTime.setYear(t);
        ifs>>t, startTime.setMonth(t);
        ifs>>t, startTime.setDay(t);
        ifs>>t, startTime.setHour(t);
        ifs>>t, startTime.setMin(t);
        ifs>>lastMinute;
    }
    ifs.close();
}

void Course::taskSort(bool sortByDDL)
{
    int i, j;
    if(sortByDDL==1)
    {
        for(i=1;i<taskNum;i++)
        {
            for(j=i;j>0&&task[j]->deadline<task[j-1]->deadline;j--)
            {
                swap(task[j],task[j-1]);
            }
        }
        return;
    }
    for(i=1;i<taskNum;i++)
    {
        for(j=i;j>0&&task[j]->setTime<task[j-1]->setTime;j--)
        {
            swap(task[j],task[j-1]);
        }
    }
}

void Course::taskSort(Task *buffer[], int len, bool sortByDDL)
{
    int i, j;
    if(sortByDDL==1)
    {
        for(i=1;i<len;i++)
        {
            for(j=i;j>0&&buffer[j]->deadline<buffer[j-1]->deadline;j--)
            {
                swap(buffer[j],buffer[j-1]);
            }
        }
        return;
    }
    for(i=1;i<len;i++)
    {
        for(j=i;j>0&&buffer[j]->setTime<buffer[j-1]->setTime;j--)
        {
            swap(buffer[j],buffer[j-1]);
        }
    }
}

Task *Course::taskSearch(string name)
{
    for(int i=0;i<taskNum;i++)
    {
        if(task[i]->getName()==name)
        {
            return task[i];
        }
    }
    return nullptr;
}

int Course::taskSearchByKeyword(string keyword, Task *buffer[])
{
    int cnt=0;
    for(int i=0; i<taskNum; i++)
    {
        if(MyString::contains(task[i]->getName(),keyword))
        {
            buffer[cnt++]=task[i];
        }
    }
    return cnt;
}


void Course::dataSort()
{
    int i, j;
    for(i=1;i<dataNum;i++)
    {
        for(j=i;j>0&&data[j]->setTime<data[j]->setTime;j--)
        {
            swap(data[j],data[j-1]);
        }
    }
}

void Course::dataSort(Data *buffer[], int len)
{
    int i, j;
    for(i=1;i<len;i++)
    {
        for(j=i;j>0&&buffer[j]->setTime<buffer[j]->setTime;j--)
        {
            swap(buffer[j],buffer[j-1]);
        }
    }
}

Data *Course::dataSearch(string name)
{
    for(int i=0;i<dataNum;i++)
    {
        if(data[i]->getName()==name)
        {
            return data[i];
        }
    }
    return nullptr;
}

int Course::dataSearchByKeyword(string keyword, Data *buffer[])
{
    int cnt=0;
    for(int i=0; i<dataNum; i++)
    {
        if(MyString::contains(data[i]->getName(),keyword))
        {
            buffer[cnt++]=data[i];
        }
    }
    return cnt;
}

int Course::getTaskNum()
{
    return taskNum;
}

int Course::getDataNum()
{
    return dataNum;
}

void Course::taskRemove(Task *t)
{
    t->remove();
    int i;
    for(i=0;i<taskNum&&task[i]->getName()!=t->getName();i++);
    delete task[i];
    task[i]=task[taskNum-1];
    taskNum--;
    need2save=true;
}

void Course::dataRemove(Data *d)
{
    d->remove();
    int i;
    for(i=0;i<dataNum&&data[i]->getName()!=d->getName();i++);
    delete data[i];
    data[i]=data[dataNum-1];
    dataNum--;
    need2save=true;
}

void Course::remove()
{
    this->courseId=0xFFFFFFFF;
    int i;
    for(i=0;i<taskNum;i++)
    {
        task[i]->remove();
        delete task[i];
    }
    for(i=0;i<dataNum;i++)
    {
        data[i]->remove();
        delete data[i];
    }
    fs::remove_all(dir);
}

Course::~Course()
{

}

bool MyString::contains(string parent, string child)
{
    int childLen=child.length();
    if(childLen==0)
        return true;
    int parentLen = parent.length();
    if(parentLen<childLen)
        return false;
    if(parentLen==childLen)
    {
        return parent==child;
    }
    int next[parentLen+5];
    getNext(child,next);
    return KMP(parent,child,next)>=0;
}

void MyString::getNext(string child, int next[])
{
    int len = 0;
    int i=0, j=-1;
    next[0]=-1;
    len=child.length();
    while(i<len-1)
    {
        if(j==-1||child[i]==child[j])
        {
            i++;
            j++;
            next[i]=j;
        }
        else
        {
            j=next[j];
        }
    }
}

int MyString::KMP(string parent, string child, int next[])
{
    int i=0,j=0;
    int len1=parent.length();
    int len2=child.length();
    while(i<len1&&j<len2)
    {
        if(j==-1||parent[i]==child[j])
        {
            i++;
            j++;
        }
        else
        {
            j=next[j];
        }
    }
    if(j>=len2)
        return i-len2+1;
    else
        return -1;
}

