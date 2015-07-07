#include "mainwindow.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName("MyOrg");
    QApplication::setApplicationName("MyApp");

    MainWindow w;
    w.show();

    return a.exec();
}
