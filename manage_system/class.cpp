#include "class.h"

Course* Class::getCourse(string courseName)
{
    int couseId=getCourseId(courseName);
    for(int i=0;i<courseNum;++i){
        if(couseId==course[i]->getCourseId()){
            return course[i];
        }
    }
    return NULL;
}
Class::Class(int classId):classId(classId),courseNum(0),course(NULL)
{
    //读取班级课程文件，逐个获取课程id
    int courseId[20];//限制一个班级最多20门课
    fstream file;
    file.open("class\\"+to_string(classId)+"_course.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>courseId[courseNum++];
        }
        file.close();
    }
    if(courseNum>0){
        course=new Course*[courseNum];//new一个数组，数组元素为课程指针类型
        for(int i=0;i<courseNum;++i){
            course[i]=new Course(courseId[i],"class\\"+to_string(classId)+"course");
        }
    }
}

Class::~Class()
{
    for(int i=0;i<courseNum;++i){
        delete course[i];
    }
    delete [] course;
}
int Class::getCourseId(string courseName)
{
    int id=0;
    string name;
    fstream file("class\\"+to_string(classId)+"courseId.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>id>>name;
            if(courseName==name){
                break;
            }
        }
        file.close();
    }
    return id;
}

string Class::getCourseName(int courseId)
{
    int id=0;
    string name;
    fstream file;
    file.open("class\\"+to_string(classId)+"courseId.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>id>>name;
            if(courseId==id){
                break;
            }
        }
        file.close();
    }
    return name;
}

void Class::addCourse(string courseName, int locale, int classId)
{
    int id=0;
    string name;
    fstream file;

    //注册新的课程id
    file.open("class\\"+to_string(classId)+"courseId.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>id>>name;
            if(name==courseName){//防止重复增加课程
                file.close();
                return;
            }
        }
        file.close();
    }
    id++;
    file.open("class\\"+to_string(classId)+"courseId.txt",ios::app);
    if(file.is_open()){
        file<<endl<<id<<endl<<courseName;
        file.close();
    }

    /*在班级课程名单登记课程id*/
    file.open("class\\"+to_string(classId)+"_course.txt",ios::in);
    if(file.is_open()){
        int courseId;
        while(!file.eof()){
            file>>courseId;
            if(courseId==id){
                file.close();
                return;
            }
        }
        file.close();
    }
    file.open("class\\"+to_string(classId)+"_course.txt",ios::app);
    if(file.is_open()){
        file<<endl<<id;
    }
    /*在课程类登记课程id*/
    Course c(id,locale,"class\\"+to_string(classId)+"course");
    c.saveFile();
    return ;
}

void Class::deleteCoure(string courseName)
{
    if(getCourse(courseName)){
        getCourse(courseName)->remove();
    }
}

void Class::setCourseTime(string courseName, int weekday, int startHour, int startMinute, int classes)
{
    /*weekday-1是因为课程类函数的解释周一对应0*/
    if(getCourse(courseName)){
        getCourse(courseName)->setCourseTime(weekday-1,startHour,startMinute,classes);
        getCourse(courseName)->saveFile();
    }
}

void Class::setCourseGroup(string courseName, string courseGroup)
{
    if(getCourse(courseName)){
        getCourse(courseName)->setGroup(courseGroup);
        getCourse(courseName)->saveFile();
    }
}
QStringList Class::getAllCourseName()
{
    QStringList list;
    for(int i=0;i<courseNum;++i){
        list.append(QString::fromStdString(getCourseName(course[i]->getCourseId())));
    }
    return list;
}

QStringList Class::getCourseInfo(string courseName)
{
    QStringList list;
    list+="上课地点:"+QString::number(getCoursePlace(courseName));
    list+="课程进度:"+QString::fromStdString(getSchedule(courseName));
    list+="课程群号:"+QString::fromStdString(getCourseGroup(courseName));
    return list;
}

void Class::getCourseTime(string courseName, int day, int *timeTable)
{
    if(getCourse(courseName)){
        timeTable[0]=getCourse(courseName)->courseBeginHour(day-1);
        timeTable[1]=getCourse(courseName)->courseBeginMin(day-1);
        timeTable[2]=getCourse(courseName)->courseLast(day-1);
    }
}

int Class::getCoursePlace(string courseName)
{
    if(getCourse(courseName)){
        return getCourse(courseName)->getLocale();
    }
}

string Class::getSchedule(string courseName)
{
    if(getCourse(courseName)){
        getCourse(courseName)->dataSort();
        return getCourse(courseName)->data[getCourse(courseName)->getDataNum()-1]->getName();
    }
}

string Class::getCourseGroup(string courseName)
{
    if(getCourse(courseName)){
        return getCourse(courseName)->getGroup();
    }
}

void Class::uploadCourseData(string courseName, string dataName, string dataPath)
{
    /*releaseData函数好像没有给出资料参数的位置,第三个参数本应为系统当前参数，这里没有获取系统当前时间的方法*/
    if(getCourse(courseName)){
        getCourse(courseName)->releaseData(dataName,dataPath,MyTime(2022,5,13));
        getCourse(courseName)->saveFile();
    }
}

QStringList Class::getCourseDataInfo(string courseName)
{
    QStringList list;
    if(getCourse(courseName)){
        int dataNum=getCourse(courseName)->getDataNum();
        for(int i=0;i<dataNum;++i){
            list.append(QString::fromStdString(getCourse(courseName)->data[i]->getName()));
        }
    }
    return list;
}

void Class::removeCourseData(string courseName, string dataName)
{
    if(getCourse(courseName)){
        Course *c=getCourse(courseName);
        if(c->dataSearch(dataName)){
            c->dataRemove(c->dataSearch(dataName));
            c->saveFile();
        }
    }
}

void Class::downloadCourseData(string courseName, string dataName, string downloadPath)
{
    if(getCourse(courseName)){
        Course *c=getCourse(courseName);
        if(c->dataSearch(dataName)){
            c->dataSearch(dataName)->download(downloadPath);
        }
    }
}

void Class::getCourseData(string courseName, string dataName, string filePath)
{
    if(getCourse(courseName)){
        getCourse(courseName)->dataSearch(dataName)->download(filePath);
    }
}

void Class::uploadExam(string courseName, string examName, MyTime startTime, int location, int duration)
{
    if(getCourse(courseName)){
        Course *c=getCourse(courseName);
        c->setExamInfo(examName,startTime,location,duration);
        c->saveFile();
    }
}

void Class::deleteExam(string courseName)
{
    if(getCourse(courseName)){
        Course *c=getCourse(courseName);
        c->cancelExam();
        c->saveFile();
    }
}

QStringList Class::getExamInfo(string courseName)
{
    QStringList list;
    if(getCourse(courseName)){
        Course *c=getCourse(courseName);
        list.append("考试名称:"+QString::fromStdString(c->getExamName()));
        list.append("开始时间:"+QString::fromStdString(c->getStartTime().toString()));
        list.append("考试时长(分钟):"+QString::number(c->getLastMinute()));
        list.append("考试地点:"+QString::number(c->getLocale()));
    }
    return list;
}

void Class::uploadHomework(string courseName, string homeworkName, MyTime deadline, string description)
{
    if(getCourse(courseName)){
        Course *c=getCourse(courseName);
        /*设置系统时间?*/
        c->releaseTask(homeworkName,MyTime(0,0,0),deadline,description);
        c->saveFile();
    }
}

void Class::deleteHomework(string courseName, string homeworkName)
{
    if(getCourse(courseName)){
        Course *c=getCourse(courseName);
        if(c->taskSearch(homeworkName)){
            c->taskRemove(c->taskSearch(homeworkName));
            c->saveFile();
        }
    }
}

QStringList Class::getHomework(string courseName)
{
    QStringList list;
    if(getCourse(courseName)){
        Course *c=getCourse(courseName);
        Task t;
        //数据残缺,无法获取task数目，只能通过判断空指针
        for(int i=0;i<c->getTaskNum();i++)
        {
            list.append(QString::fromStdString(c->task[i]->getName()));
            list.append(QString::fromStdString(c->task[i]->deadline.toString()));
            list.append(QString::fromStdString(c->task[i]->getDesc()));
            //这里只能查询到布置作业的名称和作业描述
        }
    }
    return list;
}
void Class::submitHomework(string courseName, string homeworkName, string filePath,int userId)
{
    if(getCourse(courseName)){
        getCourse(courseName)->taskSearch(homeworkName)->submit(userId,filePath);
        getCourse(courseName)->saveFile();
    }
}

QStringList Class::getHomeworkDone(string courseName,int userId)
{
    QStringList list;
    if(getCourse(courseName)){
        Course *c=getCourse(courseName);
        for(int i=0;i<c->getTaskNum();++i){
            /*haveIFinished函数返回值为0时，表示作业未完成,大于0表示完成*/
            Task *t=c->task[i];
            if(t->haveIFinished(userId)>0){
                list.append(QString::fromStdString(t->getName()));
                list.append(QString::fromStdString(t->getDesc()));
            }
        }
    }
    return list;
}

QStringList Class::getHomeworkTodo(string courseName,int userId)
{
    QStringList list;
    if(getCourse(courseName)){
        Course *c=getCourse(courseName);
        for(int i=0;i<c->getTaskNum();++i){
            /*haveIFinished函数返回值为0时，表示作业未完成,大于0表示完成*/
            Task *t=c->task[i];
            if(t->haveIFinished(userId)==0){
                list.append(QString::fromStdString(t->getName()));
                list.append(QString::fromStdString(t->getDesc()));
            }
        }
    }
    return list;
}
