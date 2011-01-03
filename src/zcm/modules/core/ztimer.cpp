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

#include "ztimer.h"

ZTimer::ZTimer(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    _iterations = 0;
    _timer = new QTimer(this);
    _tracker = new QTimer(this);
    _prestart = new QTimer(this);
    _prestart->setSingleShot(true);

    connect(_prestart,  SIGNAL(timeout()),
            this,       SLOT(start()));
    connect(_timer,     SIGNAL(timeout()),
            this,       SLOT(incrementIterations()));
    connect(_timer,     SIGNAL(timeout()),
            this,       SIGNAL(timeout()));

    zEvent->registerSignal(this, SIGNAL(started()));
    zEvent->registerSignal(this, SIGNAL(stopped()));
    zEvent->registerSignal(this, SIGNAL(timeout()));
    zEvent->registerSignal(this, SIGNAL(elapsed(qint64)));
    zEvent->registerSignal(this, SIGNAL(remaining(qint64)));
    zEvent->registerSignal(this, SIGNAL(tick()));
    zEvent->registerSlot(this, SLOT(start()));
    zEvent->registerSlot(this, SLOT(start(int)));
    zEvent->registerSlot(this, SLOT(stop()));
    zEvent->registerSlot(this, SLOT(reset()));


    parse(_config);
}

ZTimer::~ZTimer(){
    if(_tracker->isActive())
        _tracker->stop();
    stop();
}

void ZTimer::parse(const ZConfig &el){
    if(el.hasAttribute("interval")){
        int startDelay = -1;

//!     @once: timeout once then stop
        if(QVariant(el.attribute("once")).toBool())
            _timer->setSingleShot(true);

//!     @delay: time to wait before starting in milliseconds
        if( (startDelay = el.attribute("delay").toInt()) > 0 )
            _prestart->setInterval(startDelay);

//!     @interval: length of timeout interval in milliseconds
        _interval = el.attribute("interval").toInt();

//!     @onstart: emit timeout() immediately after start?
        if(ZuiUtils::attributeTrue(el.attribute("onstart"))){
            setInterval(0);
            connect(this, SIGNAL(timeout()), this, SLOT(startEmit()));
        }else{
            setInterval(_interval);
        }

//!     @tracking: frequency of interim ticks to monitor timer progress
        if(el.hasAttribute("tracking")){
            uint tintv = QVariant(el.attribute("tracking")).toUInt();
            if(_prestart->interval() == 0)
                trackStart(tintv);
        }

        if(_prestart->interval() == 0)
            start();
    }else{
        z_log_error("ZTimer: Cannot start timer without an interval");
        return;
    }

}

void ZTimer::setInterval(qint64 msec){
    _timer->setInterval(msec);
}

bool ZTimer::isActive(){
    return _timer->isActive();
}

quint64 ZTimer::iterations(){
    return _iterations;
}

void ZTimer::start(){
    if(_tracker->interval() > 0) _tracker->start();
    _timer->start();
    emit started();
}

void ZTimer::stop(){
    if(_tracker->isActive())
        _tracker->stop();
    _timer->stop();
    emit stopped();
}

void ZTimer::reset(){
    stop();
    start();
}

void ZTimer::incrementIterations(){
    ++_iterations;
}

void ZTimer::startEmit(){
    disconnect(this, SLOT(startEmit()));
    setInterval(_interval);
}

void ZTimer::trackStart(int intv){
    _elapsed = 0;
    _tracker->setInterval(intv);
    if(connect(_tracker, SIGNAL(timeout()), this, SLOT(trackTick()), Qt::UniqueConnection))
        _tracker->start();
}

void ZTimer::trackTick(){
    _elapsed += _tracker->interval();
    if(_elapsed >= _interval){
        trackFinish();
        emit elapsed(_interval);
        emit remaining(0);

    }else{
        emit elapsed(_elapsed);
        emit remaining(_interval-_elapsed);
    }

    emit tick();
}

void ZTimer::trackFinish(){
    _tracker->stop();
}
