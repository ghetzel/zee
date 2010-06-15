#ifndef ZPIEGAUGE_H
#define ZPIEGAUGE_H

#define ZUI_PIEGAUGE			"zui:piegauge"

#include <zgenericdial.h>

class ZPieGauge : public ZGenericDial
{
public:
    ZPieGauge(const ZConfig &el, QWidget *parent=0);

private:
    void paintEvent(QPaintEvent *event);
};

#endif // ZPIEGAUGE_H
