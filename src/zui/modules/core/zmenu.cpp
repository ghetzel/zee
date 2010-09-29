#include "zmenu.h"

ZMenu::ZMenu(const ZConfig &el, QWidget *parent)
    : QMenu(parent),
     ZWidget(el,this)
{
    parse(_config);
}

void ZMenu::parse(const ZConfig &el){

}
