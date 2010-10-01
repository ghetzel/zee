#ifndef ZCONTAINER_H
#define ZCONTAINER_H

#define ZUI_CONTAINER2       "zui:container"

#include <QWidget>
#include <zui/zcontainerwidget.h>
#include <zeventmanager.h>

class ZContainer : public QFrame, public ZContainerWidget
{
public:
    ZContainer(const ZConfig &el, QWidget *parent=0);

private:
    void parse(const ZConfig &el);
};

#endif // ZCONTAINER_H
