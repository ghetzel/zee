#ifndef ZSEEKBAR_H
#define ZSEEKBAR_H

#include <QtCore>
#include <zeventmanager.h>
#include <zui/zwidget.h>

class ZSeekbar : public QWidget, public ZWidget
{
public:
    ZSeekbar(const ZConfig &el, QWidget *parent=0);
    void parse(const ZConfig &el);
    void paintEvent(QPaintEvent *);

private:
    void init();
};

#endif // ZSEEKBAR_H
