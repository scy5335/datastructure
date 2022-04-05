#include "mainwindow.h"
#include "logwindow.h"

#include <QApplication>
#include <QLocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
    MainWindow student;
    logpage.dislogwindow();
    QObject::connect(&logpage, &logwindow::showmainwindow, &student, &MainWindow::display);
    return a.exec();
}
