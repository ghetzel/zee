#include "zspacer.h"

ZSpacer::ZSpacer(const ZConfig &el, QWidget *parent)
    : QFrame(parent),
      ZWidget(el,this)
{
    parse(_config);
}

void ZSpacer::parse(const ZConfig &el){
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
