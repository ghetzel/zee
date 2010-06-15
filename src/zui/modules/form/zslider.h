#ifndef ZSLIDER_H
#define ZSLIDER_H

#define ZUI_SLIDER	"zui:slider"

#include <zutil.h>
#include <zui/zwidget.h>


class ZSlider : public QSlider, public ZWidget
{
    Q_OBJECT

public:
    ZSlider(const ZConfig &el, QWidget *parent);

private:
    void init();
    void parse(const ZConfig &el);
};

#endif // ZSLIDER_H
