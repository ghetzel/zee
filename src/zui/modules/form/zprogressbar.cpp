#include "zprogressbar.h"

ZProgressBar::ZProgressBar(const ZConfig &el, QWidget *parent)
    : QProgressBar(parent),
      ZWidget(el,this)
{
    parse(_config);
    init();
}

void ZProgressBar::parse(const ZConfig &el){
    if(el.hasAttribute("min"))
	setMinimum(el.attribute("min","0").toInt());
    if(el.hasAttribute("max"))
	setMaximum(el.attribute("max","0").toInt());
    if(el.hasAttribute("value"))
	setValue(el.attribute("value","0").toInt());
}

void ZProgressBar::init(){
    zEvent->registerSignal(this,SIGNAL(valueChanged(int)));
    zEvent->registerSlot(this,SLOT(setEnabled(bool)));
    zEvent->registerSlot(this,SLOT(setMinimum(int)));
    zEvent->registerSlot(this,SLOT(setMaximum(int)));
    zEvent->registerSlot(this,SLOT(setRange(int,int)));
    zEvent->registerSlot(this,SLOT(setValue(int)));
    zEvent->registerSlot(this,SLOT(reset()));
}
