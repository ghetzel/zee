#ifndef ZTIMER_H
#define ZTIMER_H

#define ZEE_TIMER               "zee:timer"
#define ZTIMER_TRACKING_INTV    125

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

public slots:
    void reset();

signals:
    void elapsed(int);
    void remaining(int);
    void tick();

private slots:
    void startEmit();
    void trackStart(int intv=ZTIMER_TRACKING_INTV);
    void trackTick();
    void trackFinish();

private:
    int _interval;
    bool _emitOnStart;
    QTimer *_tracker;
    int _elapsed;
};

#endif // ZTIMER_H
