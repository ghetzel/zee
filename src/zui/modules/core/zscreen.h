#ifndef ZSCREEN_H
#define ZSCREEN_H

#define ZUI_SCREEN          "zui:screen"

#include <QtGui>
#include <zcontainerwidget.h>
#include <zscreenmanager.h>

class ZScreen : public ZContainerWidget
{
    Q_OBJECT
public:
    ZScreen(const ZConfig &el, ZScreenManager *manager);

private:
    ZScreenManager *_manager;

    void parse(const ZConfig &el);
};

#endif // ZSCREEN_H
