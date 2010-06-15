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

void ZTimer::parse(const ZConfig &el){    
    if(el.hasAttribute("interval")){
        if(el.attribute("once","false")=="true")
            setSingleShot(true);

        setInterval(el.attribute("interval").toInt());
        start();
    }else{
        z_log_error("ZTimer: Cannot start timer without an interval");
    }
}
