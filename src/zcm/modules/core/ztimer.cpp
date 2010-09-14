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
    : QTimer(parent),
      ZConfigurable(el,this)
{
    _tracker = new QTimer(this);
    zEvent->registerSignal(this, SIGNAL(timeout()));
    zEvent->registerSignal(this, SIGNAL(elapsed(int)));
    zEvent->registerSignal(this, SIGNAL(remaining(int)));
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
	if(QVariant(el.attribute("once")).toBool())
	    setSingleShot(true);

	_interval = el.attribute("interval").toInt();

        if(ZuiUtils::attributeTrue(el.attribute("onstart"))){
	    setInterval(0);
	    connect(this, SIGNAL(timeout()), this, SLOT(startEmit()));
	}else{
	    setInterval(_interval);
	}

	if(el.hasAttribute("tracking")){
	    uint tintv = QVariant(el.attribute("tracking")).toUInt();
	    trackStart(tintv);
	}
	start();
    }else if(el.hasAttribute("countdown")){
        _targetTime = QDateTime::fromString(el.attribute("countdown"));
    }else{
	z_log_error("ZTimer: Cannot start timer without an interval");
    }
}


void ZTimer::reset(){
    stop();
    start();
}

void ZTimer::startEmit(){
    disconnect(this, SLOT(startEmit()));
    setInterval(_interval);
}

void ZTimer::trackStart(int intv){
    if(intv >= ZTIMER_TRACKING_INTV){
	_elapsed = 0;
	_tracker->setInterval(intv);
	connect(_tracker, SIGNAL(timeout()), this, SLOT(trackTick()), Qt::UniqueConnection);
	_tracker->start();
    }
}

void ZTimer::trackTick(){
    _elapsed += _tracker->interval();
    if(_elapsed >= _interval){
	trackFinish();
    }else{
	emit tick();
	emit elapsed(_elapsed);
	emit remaining(_interval-_elapsed);
    }
}

void ZTimer::trackFinish(){
    _tracker->stop();
}
