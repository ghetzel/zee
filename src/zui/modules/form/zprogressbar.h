#ifndef ZPROGRESSBAR_H
#define ZPROGRESSBAR_H

#define ZUI_PROGRESS	    "zui:progress"

#include <QProgressBar>
#include <zutil.h>
#include <zui/zwidget.h>

class ZProgressBar : public ZWidget<QProgressBar>
{
    Q_OBJECT

public:
    ZProgressBar(const ZConfig &el, QWidget *parent);
    void parse(const ZConfig &el);

private:
    void init();
};

#endif // ZPROGRESSBAR_H
