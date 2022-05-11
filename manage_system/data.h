#ifndef DATA_H
#define DATA_H

#include <QObject>
#include<string>
#include"mytime.h"
#include<fstream>
#include<hfmtree.h>
using namespace std;
class Data : public QObject
{
    Q_OBJECT
public:
    MyTime setTime;
    explicit Data(QObject *parent = nullptr);
    Data(string name, string parentCourseDir);
    void setName(string name);
    void upload(MyTime setTime, string fileAddr);
    void download(string downloadTo);
    void getSetTime();
    string getName();
    void remove();
private:
    string path;
    string name;

signals:

};

#endif // DATA_H


