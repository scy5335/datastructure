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
    Data(string name, string parentCourseDir, QObject *parent);
    void setName(string name);
    void upload(MyTime setTime, string fileAddr);
    void download(string downloadTo);
    void getSetTime();
    string getName();
    void remove();
    ~Data();
private:
    string path;
    string name;
    string getExtension();

signals:

};

#endif // DATA_H

struct DataInfo{
    MyTime setTime;
    char extionsion[8];
};

