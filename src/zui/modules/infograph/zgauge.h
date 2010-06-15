#ifndef ZGAUGE_H
#define ZGAUGE_H

#define ZUI_GAUGE			"zui:gauge"

#include <zgenericdial.h>

class ZGauge : public ZGenericDial
{
public:
    ZGauge(const ZConfig &el, QWidget *parent=0);
    void parse(const ZConfig &el);

private:
    QSvgRenderer *_indicator;
    void paintEvent(QPaintEvent *event);
};

#endif // ZGAUGE_H
