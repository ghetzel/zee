#ifndef ZWINDOW_H
#define ZWINDOW_H

#define ZUI_APPLICATION         "zui:application"
#define ZUI_APP_DEFAULT_NAME   "ROOT"


#include <QtCore>
#include <QApplication>
#include <zui/zwidget.h>
#include <zui/zroot.h>

class ZWindow : public ZWidget<QFrame>
{
    Q_OBJECT

public:
    ZWindow(const ZConfig &el, QWidget *parent=0);
    QWidget *rootSurface();

signals:
    void clicked(int,int);
    void doubleClicked(int,int);
    void released(int,int);
    void hover(int,int);

private:
    QWidget *_rootSurface;

    void init();
    void parse(const ZConfig &el);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

};

#endif // ZWINDOW_H
