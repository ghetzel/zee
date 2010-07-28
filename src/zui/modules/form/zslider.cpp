#include "zslider.h"

ZSlider::ZSlider(const ZConfig &el, QWidget *parent)
    : ZWidget<QSlider>(el,this,parent)
{
    init();
}

void ZSlider::init(){
    parse(_config);

    zEvent->registerSignal(this, SIGNAL(valueChanged(int)));
    zEvent->registerSignal(this, SIGNAL(sliderPressed()));
    zEvent->registerSignal(this, SIGNAL(sliderReleased()));
    zEvent->registerSlot(this, SLOT(setValue(int)));
}

void ZSlider::parse(const ZConfig &el){
    if(el.attribute("direction","horizontal") == "vertical")
	setOrientation(Qt::Vertical);
    else
	setOrientation(Qt::Horizontal);
}
