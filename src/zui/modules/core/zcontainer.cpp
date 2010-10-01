#include "zcontainer.h"

ZContainer::ZContainer(const ZConfig &el, QWidget *parent)
    : QFrame(parent),
      ZContainerWidget2(el,this)
{
    parse(_config);
}

void ZContainer::parse(const ZConfig &el){

}
