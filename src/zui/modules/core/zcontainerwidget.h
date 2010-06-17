#ifndef ZCONTAINERWIDGET_H
#define ZCONTAINERWIDGET_H

#define ZUI_CONTAINER       "zui:container"

#include <QtGui>
#include <zui/zwidget.h>
#include <zeventmanager.h>

class ZContainerWidget : public QFrame, public ZWidget
{
    Q_OBJECT
public:
    ZContainerWidget(const ZConfig &el, QWidget *parent=0);

public slots:
    void toggle();

private:
    void parse(const ZConfig &el);
};

#endif // ZCONTAINERWIDGET_H
