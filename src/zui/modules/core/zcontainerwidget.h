#ifndef ZCONTAINERWIDGET_H
#define ZCONTAINERWIDGET_H

#define ZUI_CONTAINER       "zui:container"

#include <QtGui>
#include <zui/zwidget.h>

class ZContainerWidget : public QFrame, public ZWidget
{
    Q_OBJECT
public:
    ZContainerWidget(const ZConfig &el, QWidget *parent=0);

private:
    void parse(const ZConfig &el);
};

#endif // ZCONTAINERWIDGET_H
