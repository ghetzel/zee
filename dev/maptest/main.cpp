#include <QtGui/QApplication>
#include "mainwindow.h"
#include "zmapview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.layout()->setSpacing(0);
    w.layout()->setMargin(0);
    ZMapScene *ms = new ZMapScene(QRectF(),&w);
    ZMapView *map = new ZMapView(ms, &w);

    w.setCentralWidget(map);
    w.show();
    return a.exec();
}
