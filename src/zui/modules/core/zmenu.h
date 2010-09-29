#ifndef ZMENU_H
#define ZMENU_H

#include <QMenu>
#include <zeventmanager.h>
#include <zui/zwidget.h>

class ZMenu : public QMenu, public ZWidget
{
public:
    ZMenu(const ZConfig &el, QWidget *parent=0);
    void parse(const ZConfig &el);
};

#endif // ZMENU_H
