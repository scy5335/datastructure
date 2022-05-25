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
    //��ȡ�༶�γ��ļ��������ȡ�γ�id
    int courseId[20];//����һ���༶���20�ſ�
    fstream file;
    file.open("class\\"+to_string(classId)+"_course.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>courseId[courseNum++];
        }
        file.close();
    }
    if(courseNum>0){
        course=new Course*[courseNum];//newһ�����飬����Ԫ��Ϊ�γ�ָ������
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

    //ע���µĿγ�id
    file.open("class\\"+to_string(classId)+"courseId.txt",ios::in);
    if(file.is_open()){
        while(!file.eof()){
            file>>id>>name;
            if(name==courseName){//��ֹ�ظ����ӿγ�
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

    /*�ڰ༶�γ������Ǽǿγ�id*/
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
    /*�ڿγ���Ǽǿγ�id*/
    Course c(id,locale,"class\\"+to_string(classId)+"course");
    c.saveFile();
    return ;
}

void Class::deleteCoure(string courseName)
{
    getCourse(courseName)->remove();
}

void Class::setCourseTime(string courseName, int weekday, int startHour, int startMinute, int classes)
{
    /*weekday-1����Ϊ�γ��ຯ���Ľ�����һ��Ӧ0*/
    getCourse(courseName)->setCourseTime(weekday-1,startHour,startMinute,classes);
    getCourse(courseName)->saveFile();
}

void Class::setCourseGroup(string courseName, string courseGroup)
{
    getCourse(courseName)->setGroup(courseGroup);
    getCourse(courseName)->saveFile();
}
QStringList Class::getAllCourseName()
{
    QStringList list;
    for(int i=0;i<courseNum;++i){
        list.append(QString::fromStdString(getCourseName(course[i]->getCourseId())));
    }
    return list;
}

void Class::getCourseTime(string courseName, int day, int *timeTable)
{
    timeTable[0]=getCourse(courseName)->courseBeginHour(day-1);
    timeTable[1]=getCourse(courseName)->courseBeginMin(day-1);
    timeTable[2]=getCourse(courseName)->courseLast(day-1);
}

int Class::getCoursePlace(string courseName)
{
    return getCourse(courseName)->getLocale();
}

string Class::getSchedule(string courseName)
{
    getCourse(courseName)->dataSort();
    return getCourse(courseName)->data[getCourse(courseName)->getDataNum()-1]->getName();
}

string Class::getCourseGroup(string courseName)
{
    return getCourse(courseName)->getGroup();
}

void Class::uploadCourseData(string courseName, string dataName, string dataPath)
{
    /*releaseData��������û�и������ϲ�����λ��,������������ӦΪϵͳ��ǰ����������û�л�ȡϵͳ��ǰʱ��ķ���*/
    getCourse(courseName)->releaseData(dataName,dataPath,MyTime(2022,5,13));
    getCourse(courseName)->saveFile();
}

QStringList Class::getCourseDataInfo(string courseName)
{
    QStringList list;
    int dataNum=getCourse(courseName)->getDataNum();
    for(int i=0;i<dataNum;++i){
        list.append(QString::fromStdString(getCourse(courseName)->data[i]->getName()));
    }
    return list;
}

void Class::removeCourseData(string courseName, string dataName)
{
    Course *c=getCourse(courseName);
    if(c->dataSearch(dataName)){
        c->dataRemove(c->dataSearch(dataName));
        c->saveFile();
    }
}

void Class::downloadCourseData(string courseName, string dataName, string downloadPath)
{
    Course *c=getCourse(courseName);
    if(c->dataSearch(dataName)){
        c->dataSearch(dataName)->download(downloadPath);
    }
}

void Class::getCourseData(string courseName, string dataName, string filePath)
{
    getCourse(courseName)->dataSearch(dataName)->download(filePath);
}

void Class::uploadExam(string courseName, string examName, MyTime startTime, int location, int duration)
{
    Course *c=getCourse(courseName);
    c->setExamInfo(examName,startTime,location,duration);
    c->saveFile();
}

void Class::deleteExam(string courseName)
{
    Course *c=getCourse(courseName);
    c->cancelExam();
    c->saveFile();
}

QStringList Class::getExamInfo(string courseName)
{
    Course *c=getCourse(courseName);
    QStringList list;
    list.append(QString::fromStdString(c->getExamName()));
    list.append(QString::fromStdString(c->getStartTime().toString()));
    list.append(QString::number(c->getLastMinute()));
    list.append(QString::number(c->getLocale()));
    return list;
}

void Class::uploadHomework(string courseName, string homeworkName, MyTime deadline, string description)
{
    Course *c=getCourse(courseName);
    /*����ϵͳʱ��?*/
    c->releaseTask(homeworkName,MyTime(0,0,0),deadline,description);
    c->saveFile();
}

void Class::deleteHomework(string courseName, string homeworkName)
{
    Course *c=getCourse(courseName);
    if(c->taskSearch(homeworkName)){
        c->taskRemove(c->taskSearch(homeworkName));
        c->saveFile();
    }
}

QStringList Class::getHomework(string courseName)
{
    QStringList list;
    Course *c=getCourse(courseName);
    Task t;
    //���ݲ�ȱ,�޷���ȡtask��Ŀ��ֻ��ͨ���жϿ�ָ��
    for(int i=0;i<c->getTaskNum();i++)
    {
        list.append(QString::fromStdString(c->task[i]->getName()));
        list.append(QString::fromStdString(c->task[i]->deadline.toString()));
        list.append(QString::fromStdString(c->task[i]->getDesc()));
        //����ֻ�ܲ�ѯ��������ҵ�����ƺ���ҵ����
    }
    return list;
}
void Class::submitHomework(string courseName, string homeworkName, string filePath,int userId)
{
    getCourse(courseName)->taskSearch(homeworkName)->submit(userId,filePath);
    getCourse(courseName)->saveFile();
}

QStringList Class::getHomeworkDone(string courseName,int userId)
{
    QStringList list;
    Course *c=getCourse(courseName);
    for(int i=0;i<c->getTaskNum();++i){
        /*haveIFinished��������ֵΪ0ʱ����ʾ��ҵδ���,����0��ʾ���*/
        Task *t=c->task[i];
        if(t->haveIFinished(userId)>0){
            list.append(QString::fromStdString(t->getName()));
            list.append(QString::fromStdString(t->getDesc()));
        }
    }
    return list;
}

QStringList Class::getHomeworkTodo(string courseName,int userId)
{
    QStringList list;
    Course *c=getCourse(courseName);
    for(int i=0;i<c->getTaskNum();++i){
        /*haveIFinished��������ֵΪ0ʱ����ʾ��ҵδ���,����0��ʾ���*/
        Task *t=c->task[i];
        if(t->haveIFinished(userId)==0){
            list.append(QString::fromStdString(t->getName()));
            list.append(QString::fromStdString(t->getDesc()));
        }
    }
    return list;
}

