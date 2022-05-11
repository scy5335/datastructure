#include "data.h"

Data::Data(QObject *parent)
    : QObject{parent}
{

}

Data::Data( string name, string parentCourseDir)
{
    this->name=name;
    this->path=parentCourseDir+"\\data";
    this->setTime=MyTime(9999,12,31);
    if(!fs::exists(path))
    {
        qDebug()<<"注意：创建了新的资料目录";
        fs::create_directories(path);
    }
}

void Data::setName(string name)
{
    string fromAddr = path+"\\"+this->name+".data";
    if(fs::exists(fromAddr))
    {
        fs::rename(fromAddr,path+"\\"+name+".data");
    }
    this->name=name;
}


void Data::upload(MyTime setTime, string fileAddr)
{
    this->setTime=setTime;
    hfmCompress(fileAddr,path+"\\"+this->name+".data",(char*)&setTime,sizeof(MyTime));
}

void Data::download(string downloadTo)
{
    hfmDecode(path+"\\"+this->name+".data",downloadTo,(char*)&setTime);
}

void Data::getSetTime()
{
    fstream ifs;
    ifs.open(path+"\\"+this->name+".data",ios::in|ios::binary);
    ifs.seekg(1+4+1,ios::cur);
    ifs.read((char*)&setTime,sizeof(MyTime));
    ifs.close();
}

string Data::getName()
{
    return this->name;
}

void Data::remove()
{
    fs::remove_all(path+"\\"+this->name+".data");
    this->name="none";
}

