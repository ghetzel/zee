#ifndef ZFRAME_H
#define ZFRAME_H

#define ZUI_FRAME       "zui:frame"

#include <QFrame>
#include <zeventmanager.h>
#include <zui/zwidget.h>

class ZFrame : public ZWidget<QGroupBox>
{
public:
    ZFrame(const ZConfig &el, QWidget *parent=0);

private:
    void parse(const ZConfig &el);
};

#endif // ZFRAME_H
