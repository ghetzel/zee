#ifndef ZCONTAINERWIDGET_H
#define ZCONTAINERWIDGET_H

#include <QString>
#include <zui/zwidget.h>

class ZContainerWidget : public ZWidget
{
public:
    ZContainerWidget(const ZConfig &el, QWidget *self);

private:
    void parse(const ZConfig &el);
};

#endif // ZCONTAINERWIDGET_H
