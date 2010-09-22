#ifndef ZCOUNTDOWN_H
#define ZCOUNTDOWN_H

#define ZCM_COUNTDOWN           "zee:countdown"

#define ZCDWN_DEFAULT_INTV      1000

#define NOW_MSEC()		(CAST(qint64,QDateTime::currentDateTime().toTime_t())*1000LL)+CAST(qint64,QTime::currentTime().msec())

#include <ztimer.h>
#include <libzee/libzee.h>
#include <zui/zuiutils.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZCountdown : public QObject, public ZConfigurable
{
    Q_OBJECT
public:
    ZCountdown(const ZConfig &el, QObject *parent=0);
    ~ZCountdown();

public slots:
    void start();
    void stop();
    void reset();

signals:
    void started();
    void stopped();
    void elapsed(qint64);
    void remaining(qint64);
    void timeout();
    void tick();

private slots:
    void _tick();

private:
    void parse(const ZConfig &el);

private:
    ZTimer *_tracker;
    qint64 _startMsec;
    qint64 _targetMsec;
};

#endif // ZCOUNTDOWN_H
