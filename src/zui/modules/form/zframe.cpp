#include "zframe.h"

ZFrame::ZFrame(const ZConfig &el, QWidget *parent)
    : ZWidget<QGroupBox>(el,this,parent)
{
    parse(_config);
}

void ZFrame::parse(const ZConfig &el){
    if(el.hasAttribute("title"))
        setTitle(el.attribute("title"));
}

