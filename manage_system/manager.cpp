#include "manager.h"

Manager::Manager():logger("manager\\manager_logger.txt")
{
    if(!std::filesystem::exists("manager")){
        std::filesystem::create_directories("manager");
    }
//    //在管理员账号存在的前提下,寻找管理员密码
//    int id;
//    string pwd;
//    fstream file("manager\\managerInfo.txt",ios::in);
//    if(file.is_open()){
//        while(!file.eof()){
//            file>>id>>pwd;
//            if(id==managerId){
//                password=pwd;
//            }
//        }
//        file.close();
//    }
}

//Manager::Manager(int managerId, string pwd):
//    id(managerId),password(pwd),
//    logger("manager\\"+to_string(managerId)+"manager_logger.txt")
//{
//}

Manager::~Manager()
{

}

bool Manager::login(string password)
{
    return password=="123456";
//    int id;
//    string pwd;
//    fstream file("manager\\managerInfo.txt",ios::in);
//    if(file.is_open()){
//        while(!file.eof()){
//            file>>id>>pwd;
//            if(id==managerId){//管理员账号存在
//                file.close();
//                return password==pwd;
//            }
//        }
//        file.close();
//    }
//    return false;
}

//bool Manager::enroll(int managerId, string password)
//{
//    int id;
//    string pwd;
//    fstream file("manager\\managerInfo.txt",ios::in);
//    if(file.is_open()){
//        while(!file.eof()){
//            file>>id>>pwd;
//            if(id==managerId){//管理员账号已存在
//                file.close();
//                return false;
//            }
//        }
//        file.close();
//    }

//    file.open("manager\\managerInfo.txt",ios::app);
//    if(file.is_open()){
//        file<<endl<<managerId;
//        file<<endl<<password;
//        file.close();
//    }
//    return true;
//}

void Manager::addCourse(string courseName,int locale,int classId)
{
    logger.addLogger("管理员增加了一门课程");
    Class::addCourse(courseName,locale,classId);
}

void Manager::deleteCoure(string courseName,int classId)
{
    logger.addLogger("管理员删除了一门课程");
    Class c(classId);
    c.deleteCoure(courseName);
}

void Manager::setCourseTime(string courseName,int weekday,int startHour,int startMinute,int classes,int classId)
{
    logger.addLogger("管理员设置了课程时间");
    Class c(classId);
    c.setCourseTime(courseName,weekday,startHour,startMinute,classes);
}

void Manager::setCourseGroup(string courseName,string courseGroup,int classId)
{
    logger.addLogger("管理员设置了课程群");
    Class c(classId);
    c.setCourseGroup(courseName,courseGroup);
}

void Manager::uploadCourseData(string courseName, string dataName, string dataPath,int classId)
{
    logger.addLogger("管理员上传了课程资料");
    Class c(classId);
    c.uploadCourseData(courseName,dataName,dataPath);
}

QStringList Manager::getCourseDataInfo(string courseName,int classId)
{
    logger.addLogger("管理员查询了课程资料");
    Class c(classId);
    return c.getCourseDataInfo(courseName);
}

void Manager::removeCourseData(string courseName, string dataName,int classId)
{
    logger.addLogger("管理员删除了课程资料");
    Class c(classId);
    c.removeCourseData(courseName,dataName);
}

void Manager::downloadCourseData(string courseName,string dataName,string downloadPath,int classId)
{
    logger.addLogger("管理员下载询了课程资料");
    Class c(classId);
    c.downloadCourseData(courseName,dataName,downloadPath);
}

void Manager::uploadExam(string courseName, string examName, MyTime startTime, int location, int duration,int classId)
{
    logger.addLogger("管理员发布了考试");
    Class c(classId);
    c.uploadExam(courseName,examName,startTime,location,duration);
}

void Manager::deleteExam(string courseName,int classId)
{
    logger.addLogger("管理员删除了考试");
    Class c(classId);
    c.deleteExam(courseName);
}

QStringList Manager::getExamInfo(string courseName,int classId)
{
    logger.addLogger("管理员查询了考试");
    Class c(classId);
    return c.getExamInfo(courseName);
}

void Manager::uploadHomework(string courseName, string homeworkName, MyTime deadline, string description,int classId)
{
    logger.addLogger("管理员发布了作业");
    Class c(classId);
    c.uploadHomework(courseName,homeworkName,deadline,description);
}

void Manager::deleteHomework(string courseName, string homeworkName,int classId)
{
    logger.addLogger("管理员删除了作业");
    Class c(classId);
    c.deleteHomework(courseName,homeworkName);
}

QStringList Manager::getHomework(string courseName,int classId)
{
    logger.addLogger("管理员查询了作业");
    Class c(classId);
    return c.getAllHomework(courseName);
}

void Manager::clearLogger()
{
    logger.clearLogger();
}

QStringList Manager::getLogger()
{
    return logger.getLogger();
}
