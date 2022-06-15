#ifndef COURSE_H
#define COURSE_H

#include <QObject>
#include<string>
#include"task.h"
#include"data.h"
#include<cstring>
#include<filesystem>
#define uchar unsigned char
#define ull unsigned long long
using namespace std;
namespace fs = std::filesystem;
const uchar listLen=30;
/*
�γ�����ܣ�
�γ���̳���QObject����������parentָ��������Qt���Զ��ͷŶ����ܡ�
-------------------------------------------------------------
-------------------------------------------------------------
˽�г�Ա�������ܣ�
unsigned courseId;
    �γ�ͨ���ֵ����õ��Ŀγ̱��룬�γ����ڲ����������ֵ���������Ҫ�ϲ��ṩ�ÿγ̱��롣���ļ��洢·���й�
unsigned teacherId;
    ��ʦ��id��ע���޷��������ķ�Χ
unsigned locale;
    �Ͽεص��ʶ
unsigned weekTable[7];
    ���ڼ�¼ÿ���Ͽε�ʱ�䡣��ʼ��Ϊ0�����λ��ʾ�����������ڿΣ���λ��ʮλ��ʾ��ʼ�ķ��ӣ�ǧλ��ʾ��ʼ��Сʱ��
    �ر����ѣ���Ҫͨ��setCourseTime(....)������
    ��Ҫͨ��courseBeginHour(.)��courseBeginMin(.)��courseLast(.)����ȡ
uchar startWeek,endWeek;
    �γ̵���ʼ�ܴκͽ����ܴΣ�����ұ�
ull firstClass;
    �ÿγ̵ĵ�һ���Ͽεİ༶�����ļ��洢·���й�
uchar continuous;
    �ÿγ̴ӵ�һ���Ͽεİ༶�����м��������İ༶�����ļ��洢·���й�
string group;
    �γ�Ⱥ�ַ���
bool need2save;
    ��������Ƿ���Ҫ���档�޸��ڴ������ݺ����Ϊtrue����������γ��ļ������Ϊtrue
uchar taskNum;
    �Ѷ������ҵ����
uchar dataNum;
    �Ѷ������������
string dir;
    �ÿγ̵�Ŀ¼
string examName;
    �������ơ�δ���ÿ���ʱΪ"unitialized"
int examLocale,lastMinute;
    ���Եص㣬����������
MyTime startTime;
    ���Կ�ʼ��ʱ��
-------------------------------------------------------------
-------------------------------------------------------------
���г�Ա��������
Task* task[listLen];
    ��ҵָ���б���󳤶�ΪlistLen��taskSort��ı���ҵָ�����б��е�˳��
    ����ֱ�ӷ������ύ��ҵ������Ҫ����task��remove��������Ϊremove����ֻ�ᾲĬ��ɾ����task�������ļ���
Data* data[listLen];
    ����ҵָ���б�����ȫһ����ͬ����Ҫ����remove����

-------------------------------------------------------------
-------------------------------------------------------------
��������
Course(unsigned courseId, unsigned locale, string root="D:\\");
    ��Ҫ���ڴ����µĿγ�ʱʹ�ã����ʼ���γ̵���Ϣ��
    ���Ǿ�����Ͽ�ʱ���Լ�������Ϣ����δ��������ʼ��Ϊ��Чֵ��
Course(unsigned courseId,string root="D:\\");
    io����
    ��Ҫ���ڸ��Ѵ��ڵĿγ̴���һ���γ������壬��ͨ�������ҵ��ļ���λ�ò���ȡ��
    ��������ڶ�Ӧ���ļ��ᱨ���������жϳ���
void setLocale(int locale);
    ����������һ��
void setCourseTime(uchar weekDay, uchar hour, uchar min, uchar last);//���ڡ��Ӽ���ļ��ֿ�ʼ���������ڿ�
    ����ĳһ����Ͽ�ʱ�䣬ע��weekDay��ƽ����˵��������-1����MyTime���ȡ������һ�¡���������Ϊ���ڼ�-1����ʼ�Ͽε�Сʱ�����ӣ��������ڿ�
void setPeriodWeek(int startWeek, int endWeek);
    �����Ͽε��ܴη�Χ
void setGroup(string group);
    ����Ⱥ
void setExamInfo(string examName, MyTime startTime, int locale, int lastMinute);
    ���ÿ�����Ϣ������Ϊ�������ơ���ʼʱ�䡢�ص㡢���Գ������ٷ���
void setRoot(string root);
    �������ø�Ŀ¼��ԭ��·�����ٱ��棬����������ݶ�ʧ

-------------------------------------------------------------
-------------------------------------------------------------
����Ϊ�����Ļ�ȡ˽�б�����ֵ�ĺ���
unsigned getCourseId();
unsigned getLocale();
int courseBeginHour(int day);
int courseBeginMin(int day);
int courseLast(int day);
int getTotalHour();
    ��ȡ�ܿ�ʱ��
string getGroup();
string getExamName();
int getExamLocale();
MyTime getStartTime();
int getLastMinute();
-------------------------------------------------------------
-------------------------------------------------------------
Task* releaseTask(string taskName, MyTime sysTime, MyTime deadline, string description="");
    ������ҵ����������Ϊ��ҵ���ơ�ϵͳ��ǰʱ�䣨��ΪsetTime������ֹʱ�䡢��ҵ������Ĭ��Ϊ�մ���
    ע�⣺��io����������need2saveΪtrue
Data* releaseData(string dataName, string fileAddr, MyTime sysTime);
    �ϴ����ϣ���������Ϊ�������ơ��ļ�·����ϵͳ��ǰʱ�䣨��ΪsetTime��
void saveFile();
    io����
    ������ÿγ���ص�������Ϣ��ͬʱ��need2saveΪfalse
    ��ע���ϲ����豣�涨λ�ÿγ̵�������Ϣ���γ����ƻ���id����һ���༶���Լ�һ�������༶��
void readFile();
    io����
    ��ȡ��ÿγ���ص�������Ϣ�������ʱneed2saveΪtrue������ʾ���ݿ��ܶ�ʧ�����������ȡ�ļ���
-------------------------------------------------------------
-------------------------------------------------------------
void taskSort(bool sortByDDL);
    ����Ϊ��ʱ����deadlineʱ�����ҵ�������У���������setTimeʱ�����ҵ�������С�
    ����һ��γ̵���ҵ���������������������У����ò���������ǿ���
Task* taskSearch(string name);
    ��������ָ�����Ƶ���ҵ�����ظ���ҵ��ָ�롣
    �������ҵ�����ڣ�����nullptr
void dataSort();
    ����setTime�������������У�ͬ�����ò�������
Data* dataSearch(string name);
    ��������ָ�����Ƶ����ϣ����ظ����ϵ�ָ��
-------------------------------------------------------------
-------------------------------------------------------------
void taskRemove(Task* t);
    io����
    ��ȫɾ��ָ������ҵ������ɾ������ҵ�ı����ļ����ͷŸ���ҵ�����Լ�taskNum--
    ע�⣬�ú������ܻ�ı�ԭ��ҵ�б��˳�����Ծ�������ͨ��task�����±������ҵ�б�����ֱ����ָ�����
void dataRemove(Data* d);
    io����
    taskRemove�����ϰ汾
void remove();
    io����
    ɾ�����γ̣�����ɾ��������ҵ�����ϣ�ɾ���γ��ļ���courseId��Ϊ0xFFFFFFFF
    ע�⣬��Ҫ�ϲ��ͷŸÿγ̶��󣬷�������������֮��Ĵ���
-------------------------------------------------------------
-------------------------------------------------------------
˽�з�����
void taskReadIn(string name);
    io����
    ��ȡָ�����Ƶ���ҵȫ����Ϣ��������Ӧ��Task�����task�б���
void dataReadIn(string name);
    io����
    ��ȡָ�����Ƶ����ϣ�������Ӧ��Data�����data�б���
-------------------------------------------------------------
-------------------------------------------------------------
��ʹ�÷������ο���
1. �γ̵Ĵ��������
    �����´����Ŀγ̣����õ�һ�����캯���������ܶ�����ƿγ̻�����Ϣ��
    ��ȡ�Ѵ����Ŀγ̣����õڶ������캯����ֻ��3����Ϣ���ɶ�λ��������
    ע�⣬�γ���ĸ�Ŀ¼��������Ŀ��ܻᵼ���޷���λ�γ��ļ���

2. ��ʱ��Ҫ�����ļ�
    �������µĿγ̱���ʱ������������ҵʱ�������ϻ��Զ����浽�ļ��У��Ͼ�Ҫ�ϴ���

3. ����ʹ��˳��
    ����/��ȡ�γ�new Course(...)�����÷Ǳ�����Ϣ������setExamInfo(....)
    ������ҵreleaseTask(....)�����������ȹ��ܻ����ҵָ�룬�Ӷ�ʹ�ò鿴��ҵ��Ϣ���ύ��ҵ�ȹ���
    �ϴ����ϵķ������ơ�
    ����ɾ��ĳ����ҵ�����ϣ�����taskRemove��dataRemove�����������Ҫɾ���γ̣������remove�������ǵ��޸��ϲ�Ŀγ��б�


4. ע������
    1. �ǵ��ڱ�Ҫʱ�̱��档��������need2save�����ж��Ƿ���Ҫ����
    2. ������ҵ�ĺ�����ͬ����ҵ�Ѵ���ʱ��ֱ�ӷ��ؿ�ָ�룬ע������nullptr�ĵ��á����������ϵĺ����ڼ�⵽ͬ�����ϴ���ʱ����²���������ָ�룬ע���������
    3. ��ҵ�����������Լ���·���ϲ�Ҫ�����Ļ��߿ո�ͻ��з��ȷ���
    4. ��ҵ�����ơ����ϵ������޷������޸ģ������Ҫ�޸ģ���ɾ�������·�����
    5. ��Ҫֱ�ӵ�����ҵ�������ϵ�remove����������ֻ��ɾ�����ǵ��ļ���ɾ�������޷��ָ���
    6: �������û�����ͨ��ui������ҵ�Ĳ��ֻ�����Ϣ��ui�ཨ����ҵ��������ָ���ӳ���ϵ�����û������ҵ����ʱ������ֱ��ȷ������ҵ��ָ�롣�����ҽ�task�б���Ϊ���б����ˡ�
       ���չʾ��ҵ����Ϣ��չʾ��ҵ����Щ��Ϣ������ֱ��ͨ����ҵ�����ã����γ���û���ٴη�װ���ǣ�������ͬ��
    7. ����ʵ�����ȷ��listLen������ҵ�������б����󳤶ȡ�
*/

class Course : public QObject
{
    Q_OBJECT
private:
    unsigned courseId;
    unsigned locale;
    unsigned weekTable[7];
    string group;
    bool need2save;
    uchar taskNum;
    uchar dataNum;
    string dir;
    string examName;
    int examLocale,lastMinute;
    MyTime startTime;
    void taskReadIn(string name);
    void dataReadIn(string name);
public:
    Task* task[listLen];
    Data* data[listLen];
    explicit Course(QObject *parent = nullptr);
    Course(unsigned courseId, unsigned locale, string root="D:\\");
    Course(unsigned courseId, string root="D:\\");
    void setLocale(int locale);
    void setCourseTime(uchar weekDay, uchar hour, uchar min, uchar last);//���ڡ��Ӽ���ļ��ֿ�ʼ���������ڿ�
    void setGroup(string group);
    void setExamInfo(string examName, MyTime startTime, int locale, int lastMinute);
    void setRoot(string root);
    void cancelExam();
    unsigned getCourseId();

    unsigned getLocale();
    int courseBeginHour(int day);
    int courseBeginMin(int day);
    int courseLast(int day);
    int getStartWeek();
    int getEndWeek();
    int getTotalHour();
    ull getFirstClass();
    int getClassNum();
    string getGroup();
    string getExamName();
    int getExamLocale();
    MyTime getStartTime();
    int getLastMinute();
    Task* releaseTask(string taskName, MyTime sysTime, MyTime deadline, string description="");//ֻ���ڴ��д�������Ҫ���档
    Data* releaseData(string dataName, string fileAddr, MyTime sysTime);
    void saveFile();
    void readFile();
    void taskSort(bool sortByDDL);
    static void taskSort(Task*buffer[], int len, bool sortByDDL);
    Task* taskSearch(string name);
    int taskSearchByKeyword(string keyword, Task*buffer[]);
    void dataSort();
    static void dataSort(Data*buffer[], int len);
    Data* dataSearch(string name);
    int dataSearchByKeyword(string keyword, Data* buffer[]);
    int getTaskNum();
    int getDataNum();
    void taskRemove(Task* t);
    void dataRemove(Data* d);
    void remove();
    ~Course();
signals:

};

class MyString
{
public:
    static bool contains(string parent, string child);
private:
    static void getNext(string child, int next[]);
    static int KMP(string parent, string child, int next[]);
};
#endif // COURSE_H























