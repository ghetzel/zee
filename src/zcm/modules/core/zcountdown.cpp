#include "zcountdown.h"

ZCountdown::ZCountdown(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{    
    _tracker = NULL;
    parse(_config);   

    if(_tracker){
        connect(_tracker,   SIGNAL(tick()),
                this,       SLOT(_tick()));
        connect(_tracker,   SIGNAL(started()),
                this,       SIGNAL(started()));
        connect(_tracker,   SIGNAL(stopped()),
                this,       SIGNAL(stopped()));
    }

    zEvent->registerSignal(this, SIGNAL(started()));
    zEvent->registerSignal(this, SIGNAL(stopped()));
    zEvent->registerSignal(this, SIGNAL(tick()));
    zEvent->registerSignal(this, SIGNAL(timeout()));
    zEvent->registerSignal(this, SIGNAL(elapsed(qint64)));
    zEvent->registerSignal(this, SIGNAL(remaining(qint64)));
    zEvent->registerSlot(this, SLOT(start()));
    zEvent->registerSlot(this, SLOT(stop()));
    zEvent->registerSlot(this, SLOT(reset()));
}

ZCountdown::~ZCountdown(){
    if(_tracker && _tracker->isActive())
        _tracker->stop();
}

void ZCountdown::parse(const ZConfig &el){
//! @target: the target time for the countdown
    _targetMsec = (ZDateTime::strtotime_t(el.attribute("target")) * 1000LL);
    qint64 now = (ZDateTime::now_t() * 1000LL);

    if(target.isValid()){
        _targetMsec = target.toTime_t()*1000LL;

        if(!el.hasAttribute("interval"))
            _config.setAttribute("interval", ZCDWN_DEFAULT_INTV);

        if(_targetMsec > )
            _tracker = new ZTimer(_config, this);

        z_log_debug("ZCountdown: Target epoch = "+STR(_targetMsec) + " -> "+target.toString("yyyy-MM-dd hh:mm:ss"));
        z_log_debug("ZCountdown: Current epoch = "+STR(ZDateTime::now_t()));
    }else{
        z_log_error("ZCountdown: Invalid target date specified.");
    }
}

void ZCountdown::_tick(){
    qint64 nowMsec = NOW_MSEC();

    if(nowMsec < _targetMsec){
        z_log_debug("ZCountdown: Current epoch = "+STR(nowMsec));
        z_log_debug("ZCountdown: Elapsed = "+STR(nowMsec - _startMsec));
        z_log_debug("ZCountdown: Remains = "+STR(_targetMsec - nowMsec));

        emit elapsed(nowMsec - _startMsec);
        emit remaining(_targetMsec - nowMsec);
        emit tick();
    }else{
        z_log_debug("ZCountdown: COMPLETED");
        emit timeout();
    }
}

void ZCountdown::start(){
    if(_tracker) _tracker->start();
    _startMsec = NOW_MSEC();
}

void ZCountdown::stop(){
    if(_tracker && _tracker->isActive()) _tracker->stop();
    _startMsec = 0;
}

void ZCountdown::reset(){
    if(_tracker) _tracker->reset();
}
