#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icon"));
    QTranslator translator;
    translator.load(":/zh_CN");
    a.installTranslator(&translator);
    MainWindow w;
    w.move(500,100);
    w.show();

    return a.exec();
}
