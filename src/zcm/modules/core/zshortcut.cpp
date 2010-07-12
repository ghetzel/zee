#include "zshortcut.h"

ZShortcut::ZShortcut(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    parse(_config);
}

void ZShortcut::parse(const ZConfig &el){
    if(param("value").isValid()){
    }
}
