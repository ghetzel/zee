#ifndef ZTIMER_H
#define ZTIMER_H

#define ZEE_TIMER       "zee:timer"

#include <QTimer>
#include <zutil.h>
#include <zui/zuiutils.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZTimer : public QTimer, public ZConfigurable
{
    Q_OBJECT
public:
    ZTimer(const ZConfig &el, QObject *parent=0);
    ~ZTimer();
    void parse(const ZConfig &el);

private slots:
    void startEmit();

private:
    int _interval;
    bool _emitOnStart;
};

#endif // ZTIMER_H
