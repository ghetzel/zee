#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    MapWidget *map = new MapWidget(&w);

    w.setCentralWidget(map);
    w.show();
    return a.exec();
}
