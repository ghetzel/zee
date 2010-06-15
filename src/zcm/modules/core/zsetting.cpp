#include "zsetting.h"

ZSetting::ZSetting(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    parse(_config);
}

void ZSetting::parse(const ZConfig &el){}
