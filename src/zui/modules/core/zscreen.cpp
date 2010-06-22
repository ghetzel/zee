#include "zscreen.h"

ZScreen::ZScreen(const ZConfig &el, ZScreenManager *manager)
    : ZContainerWidget(el,this)
{
    _manager = manager;
    parse(_config);
}

void ZScreen::parse(const ZConfig &el){
    _manager->addScreen(this,el.attribute("name"));
}
