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
    string path;
public:
    Logger(string path);
    ~Logger();
    /*增加一条日志记录，参数用户和操作信息的字符串*/
    void addLogger(string userAndOperation);
    /*清除日志*/
    void clearLogger();
    /*读取日志所有记录*/
    QStringList getLogger();
};

#endif // LOGGER_H