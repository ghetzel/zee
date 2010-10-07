#include "zabstractscript.h"

ZAbstractScript::ZAbstractScript(const ZConfig &el, QObject *self, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,self)
{
    parse(_config);
}

void ZAbstractScript::parse(const ZConfig &el){
    if(ZuiUtils::attributeFalse("onstart"))
        _autorun = false;
    else
        _autorun = true;
}
