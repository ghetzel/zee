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

        if(ZuiUtils::attributeTrue(el, "onstart")){
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
