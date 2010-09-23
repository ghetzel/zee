/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef ZTIMER_H
#define ZTIMER_H

#define ZEE_TIMER               "zee:timer"
#define ZTIMER_TRACKING_INTV    125

#include <QTimer>
#include <zutil.h>
#include <zui/zuiutils.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZTimer : public QObject, public ZConfigurable
{
    Q_OBJECT

public:
    ZTimer(const ZConfig &el, QObject *parent=0);
    ~ZTimer();
    void parse(const ZConfig &el);
    void setInterval(qint64);
    bool isActive();

public slots:
    void start();
    void stop();
    void reset();

signals:
    void timeout();
    void started();
    void stopped();
    void elapsed(qint64);
    void remaining(qint64);
    void tick();

private slots:
    void startEmit();
    void trackStart(int intv=ZTIMER_TRACKING_INTV);
    void trackTick();
    void trackFinish();

private:
    bool _emitOnStart;
    qint64 _interval;
    qint64 _elapsed;
    QTimer *_timer;
    QTimer *_tracker;
    QTimer *_prestart;
};

#endif // ZTIMER_H
