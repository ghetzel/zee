#include "zcountdown.h"

ZCountdown::ZCountdown(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{    
    _tracker = NULL;
    parse(_config);   

    if(_tracker){
        connect(_tracker,   SIGNAL(timeout()),
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
    _target = ZDateTime::strtotime(el.attribute("target"));

    if(_target.isValid()){
        _targetMsec = (_target.toTime_t()*1000LL)+_target.time().msec();
        qint64 now = ZDateTime::nowMsec_t();

        if(!el.hasAttribute("interval"))
            _config.setAttribute("interval", ZCDWN_DEFAULT_INTV);

        if(_targetMsec > 0)
            _tracker = new ZTimer(_config.toElement(), this);

        z_log_debug("ZCountdown: Target epoch  = "+STR(_targetMsec));
        z_log_debug("ZCountdown: Current epoch = "+STR(now));
        z_log_debug("ZCountdown: ---- DIFF ----  "+STR(_targetMsec-now));
    }else{
        z_log_error("ZCountdown: Invalid target date specified.");
    }
}

void ZCountdown::_tick(){
    qint64 nowMsec = ZDateTime::nowMsec_t();

    if(nowMsec < _targetMsec){
        emit elapsed(nowMsec - _startMsec);
        emit remaining(_targetMsec - nowMsec);
        emit tick();
    }else{
        z_log_debug("ZCountdown: COMPLETED");
        _tracker->stop();
        emit timeout();
    }
}

bool ZCountdown::isActive(){
    return _tracker->isActive();
}

void ZCountdown::start(){
    if(_tracker) _tracker->start();
    _startMsec = ZDateTime::nowMsec_t();
}

void ZCountdown::stop(){
    if(_tracker && _tracker->isActive()) _tracker->stop();
    _startMsec = 0;
}

void ZCountdown::reset(){
    if(_tracker) _tracker->reset();
}
