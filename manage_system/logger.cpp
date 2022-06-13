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
    file<<endl<<log;
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
    if(file.is_open()){
        while(!file.eof()){
            string line;
            file>>line;
            list.append(QString::fromLocal8Bit(line));
        }
        file.close();
    }
    return list;
}
