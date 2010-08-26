#include "zspacer.h"

ZSpacer::ZSpacer(const ZConfig &el, QWidget *parent)
    : ZWidget<QFrame>(el,this,parent)
{
    parse(_config);
}

void ZSpacer::parse(const ZConfig&){
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
