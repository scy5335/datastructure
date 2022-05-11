#include "course.h"

Course::Course(QObject *parent)
    : QObject{parent}
{

}

Course::Course(unsigned courseId, unsigned teacherId, unsigned locale, unsigned char startWeek, unsigned char endWeek, unsigned long long firstClass, unsigned char continuous, string root)
{
    this->courseId = courseId;
    this->teacherId = teacherId;
    this->locale =locale;
    this->startWeek=startWeek;
    this->endWeek=endWeek;
    this->firstClass=firstClass;
    this->continuous=continuous;
    this->dir=root+"\\course_"+to_string(courseId)+"_"+to_string(firstClass)+"_"+to_string(continuous);
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

Course::Course(unsigned courseId, unsigned long long firstClass, unsigned char continuous, string root)
{
    this->courseId = courseId;
    this->firstClass = firstClass;
    this->continuous = continuous;
    this->dir=root+"\\course_"+to_string(courseId)+"_"+to_string(firstClass)+"_"+to_string(continuous);
    this->taskNum=0;
    this->dataNum=0;
    if(!fs::exists(dir))
    {
        qDebug()<<"未找到该课程路径，请检查该课程是否存在";
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

void Course::setPeriodWeek(int startWeek, int endWeek)
{
    this->startWeek=startWeek;
    this->endWeek=endWeek;
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
        task[taskNum] = new Task(courseId,taskName,sysTime,deadline,description,dir);
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

unsigned Course::getCourseId()
{
    return courseId;
}

unsigned Course::getTeacherId()
{
    return teacherId;
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

int Course::getStartWeek()
{
    return startWeek;
}

int Course::getEndWeek()
{
    return endWeek;
}

int Course::getTotalHour()
{
    int perWeek=0;
    for(int i=0;i<7;i++)
    {
        perWeek+=courseLast(i);
    }
    return perWeek*(endWeek-startWeek+1);
}

unsigned long long Course::getFirstClass()
{
    return firstClass;
}

int Course::getClassNum()
{
    return continuous;
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
        data[dataNum] = new Data(dataName,dir);
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
        task[taskNum]=new Task(courseId,name,dir);
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
    data[dataNum] = new Data(name,dir);
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
    ofs<<teacherId<<" "<<locale<<" "<<courseId<<endl;
    int i;
    for(i=0;i<7;i++)
    {
        ofs<<weekTable[i]<<" ";
    }
    ofs<<(int)startWeek<<" "<<(int)endWeek<<endl;
    ofs<<firstClass<<" "<<(int)continuous<<" "<<group<<endl;
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
        ofs<<examName;
    }
    else
    {
        ofs<<examName<<" "<<examLocale<<" "<<startTime.getYear()<<" "
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
    ifs>>teacherId>>locale>>courseId;
    int i;
    for(i=0;i<7;i++)
    {
        ifs>>weekTable[i];
    }
    int intTmp;
    ifs>>intTmp;startWeek=intTmp;
    ifs>>intTmp;endWeek=intTmp;
    ifs>>firstClass;
    ifs>>intTmp;continuous=intTmp;
    ifs>>group;
    string temp;
    for(i=0;ifs>>temp&&temp!="data:";i++)
    {
        taskReadIn(temp);
    }
    for(i=0;ifs>>temp&&temp!="exam:";i++)
    {
        dataReadIn(temp);
    }
    ifs>>examName;
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
    qDebug()<<courseId;
    for(i=0;i<taskNum;i++)
    {
        task[i]->remove();
        qDebug()<<"1";
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
    int i;
    for(i=0;i<taskNum;i++)
    {
        delete task[i];
    }
    for(i=0;i<dataNum;i++)
    {
        delete data[i];
    }
}
