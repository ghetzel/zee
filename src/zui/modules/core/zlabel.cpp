#include "zlabel.h"

ZLabel::ZLabel(const ZConfig &el, QWidget *parent)
    : ZWidget<QLabel>(el,this,parent)
{
    init();
}

ZLabel::ZLabel(QString value, const ZConfig &el, QWidget *parent)
    : ZWidget<QLabel>(el,this,parent)
{
    setText(value);
    init();
}

void ZLabel::init(){
    parse(_config);

    zEvent->registerSlot(this,SLOT(setText(QString)));
    zEvent->registerSlot(this,SLOT(setEnabled(bool)));
    zEvent->registerSlot(this,SLOT(reset()));
}

void ZLabel::parse(const ZConfig &el){
    if(el.hasAttribute("value"))
        setText(el.attribute("value"));
    else
        setText(el.text());
    _initValue = text();
}

void ZLabel::reset(){
    setText(_initValue);
}
