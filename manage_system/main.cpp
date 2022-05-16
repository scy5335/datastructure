#include "mainwindow.h"
#include "logwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("fusion"));//设置样式为fusion

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "manage_system_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    logwindow logpage;
    mainwindow mainpage;
    logpage.dislogwindow();
    QObject::connect(&logpage, &logwindow::showmainwindow, &mainpage, &mainwindow::display_student_page);
    QObject::connect(&logpage, &logwindow::showmanagewindow, &mainpage, &mainwindow::display_manage_page);
    return a.exec();
}
