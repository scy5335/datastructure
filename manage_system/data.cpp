#include "data.h"

Data::Data(QObject *parent)
    : QObject{parent}
{

}

Data::Data( string name, string parentCourseDir, QObject *parent)
{
    this->name=name;
    this->path=parentCourseDir+"\\data";
    this->setTime=MyTime(9999,12,31);
    if(!fs::exists(path))
    {
        qDebug()<<"注意：创建了新的资料目录";
        fs::create_directories(path);
    }
    setParent(parent);
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
    string extension = fs::path(fileAddr).extension().string();
    DataInfo info;
    info.setTime=setTime;
    strcpy_s(info.extionsion,extension.length()+1,extension.c_str());
    hfmCompress(fileAddr,path+"\\"+this->name+".data",(char*)&info,sizeof(info));
}

void Data::download(string downloadTo)
{
    string ext = getExtension();
    DataInfo info;
    hfmDecode(path+"\\"+this->name+".data",downloadTo+"\\"+this->name+ext,(char*)&info);
    this->setTime=info.setTime;
}

void Data::getSetTime()
{
    fstream ifs;
    ifs.open(path+"\\"+this->name+".data",ios::in|ios::binary);
    ifs.seekg(1+4+1,ios::cur);
    ifs.read((char*)&setTime,sizeof(MyTime));
    ifs.close();
}

string Data::getExtension()
{
    fstream ifs;
    ifs.open(path+"\\"+this->name+".data",ios::in|ios::binary);
    ifs.seekg(1+4+1,ios::cur);
    DataInfo info;
    ifs.read((char*)&info,sizeof(info));
    ifs.close();
    return string(info.extionsion);
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

Data::~Data()
{

}


