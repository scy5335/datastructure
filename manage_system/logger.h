#ifndef LOGGER_H
#define LOGGER_H
#include<QDateTime>
#include<QDebug>
#include<fstream>
#include<string.h>
#include "mytime.h"
using namespace std;

class Logger
{
private:
    string path;//��־�ļ�·��
public:
    Logger(string path);
    ~Logger();
    /*����һ����־��¼�������û��Ͳ�����Ϣ���ַ���,��־��¼���Զ�����ʱ���*/
    void addLogger(string userAndOperation);
    /*�����־*/
    void clearLogger();
    /*��ȡ��־���м�¼*/
    QStringList getLogger();
};

#endif // LOGGER_H
