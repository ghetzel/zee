#include "zsplitter.h"

ZSplitter::ZSplitter(const ZConfig &el, QWidget *parent)
    : ZWidget<QSplitter>(el,this,parent)
{
    parse(_config);
}

void ZSplitter::parse(const ZConfig &el){
    if(el.attribute("direction") == "vertical")
        setOrientation(Qt::Vertical);
}
