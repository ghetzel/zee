#ifndef ZTIMER_H
#define ZTIMER_H

#define ZEE_TIMER       "zee:timer"

#include <QTimer>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZTimer : public QTimer, public ZConfigurable
{
public:
    ZTimer(const ZConfig &el, QObject *parent=0);
    void parse(const ZConfig &el);
};

#endif // ZTIMER_H
