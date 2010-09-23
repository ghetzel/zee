#ifndef ZCOUNTDOWN_H
#define ZCOUNTDOWN_H

#define ZCM_COUNTDOWN           "zee:countdown"
#define ZCDWN_DEFAULT_INTV      1000

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
    bool isActive();

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
    QDateTime _target;
    qint64 _targetMsec;
};

#endif // ZCOUNTDOWN_H
