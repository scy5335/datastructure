#include "logger.h"

Logger::Logger(string path):path(path)
{

}
Logger::~Logger()
{

}
void Logger::addLogger(string userAndOperation)
{
    ofstream file(path,ios::app);
    string log=QDateTime::currentDateTime().toString("yyyy年MM月dd日hh:mm:ss").toStdString()+userAndOperation;
    file<<log<<endl;
    file.close();
}
void Logger::clearLogger()
{
    ofstream file(path,ios::trunc);
    file.close();
}
QStringList Logger::getLogger()
{
    QStringList list;
    ifstream file(path,ios::in);
    while(!file.eof()){
        string line;
        file>>line;
        list.append(QString::fromStdString(line));
    }
//    /*该循环会导致最后读到一个空行，解决方法如下：去掉最后一个数据*/
//    /*更合理的代码待写*/
//    list.pop_back();
    file.close();
    return list;
}
