#include "ztimer.h"

ZTimer::ZTimer(const ZConfig &el, QObject *parent)
    : QTimer(parent),
      ZConfigurable(el,this)
{
    zEvent->registerSignal(this, SIGNAL(timeout()));
    zEvent->registerSlot(this, SLOT(start()));
    zEvent->registerSlot(this, SLOT(start(int)));
    zEvent->registerSlot(this, SLOT(stop()));
    parse(_config);
}

ZTimer::~ZTimer(){
    stop();
}

void ZTimer::parse(const ZConfig &el){    
    if(el.hasAttribute("interval")){
        if(el.attribute("once","false")=="true")
            setSingleShot(true);

        _interval = el.attribute("interval").toInt();

        if(ZuiUtils::attributeTrue(el, "onstart")){
            setInterval(0);
            connect(this, SIGNAL(timeout()), this, SLOT(startEmit()));
        }else{
            setInterval(_interval);
        }
        start();
    }else{
        z_log_error("ZTimer: Cannot start timer without an interval");
    }
}

void ZTimer::startEmit(){
    disconnect(this, SLOT(startEmit()));
    setInterval(_interval);
}
