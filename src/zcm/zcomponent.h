#ifndef ZCOMPONENT_H
#define ZCOMPONENT_H

#include <zconfigurable.h>

class ZComponent : public ZConfigurable{

public:
    ZComponent(const ZConfig &el, QObject *self)
        : ZConfigurable(el,self){}
};

#endif // ZCOMPONENT_H
