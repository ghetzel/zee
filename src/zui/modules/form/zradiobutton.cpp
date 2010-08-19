#include "zradiobutton.h"

ZRadioButton::ZRadioButton(const ZConfig &el, QWidget *parent)
    : ZWidget<QRadioButton>(el,this,parent)
{
    parse(_config);
}

void ZRadioButton::parse(const ZConfig &el){
    if(!el.text().isEmpty())
        setText(el.text());
    if(el.hasAttribute("value"))
        _value = QVariant(el.attribute("value"));
}
