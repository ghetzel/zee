#ifndef ZSPACER_H
#define ZSPACER_H

#define ZUI_SPACER     "zui:spacer"

#include <QtGui>
#include <zeventmanager.h>
#include <zui/zwidget.h>


class ZSpacer : public ZWidget<QFrame>
{
public:
    ZSpacer(const ZConfig &el, QWidget *parent=0);


private:
    void parse(const ZConfig &el);
};

#endif // ZSPACER_H
