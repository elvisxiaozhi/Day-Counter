#include "mainwindow.h"
#include <QApplication>
#include <cstdlib>
#include <QSettings>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings.setValue("Day-Counter", QCoreApplication::applicationFilePath().replace('/', '\\'));

    return a.exec();
}
