#include "zstyleproperty.h"

ZStyleProperty::ZStyleProperty(ZStyleSection *parent)
    : QObject(RECAST(QObject*,parent))
{
    init();
}

ZStyleProperty::ZStyleProperty(QString name, QString value, ZStyleSection *parent)
    : QObject(RECAST(QObject*,parent))
{
    _parent = parent;

    name = name.trimmed();
    value = value.trimmed();

    if(parent && !(name.isEmpty() && value.isEmpty())){
        _name = name;
        _value = value;
        init();
    }else{
        z_log_warn("ZStyleProperty: Property name and value must be specified.");
    }
}

ZStyleProperty::ZStyleProperty(const ZStyleProperty &other){
    _parent = other._parent;
    _name = other._name;
    _value = other._value;
}

ZStyleProperty::~ZStyleProperty(){

}

void ZStyleProperty::init(){
}

ZStyleSection *ZStyleProperty::section(){
    return _parent;
}

QString ZStyleProperty::name(){
    return _name;
}

ZString ZStyleProperty::rawValue(){
    return _value;
}

QString ZStyleProperty::toString(){
    if(!(_name.isEmpty() && _value.isEmpty()))
        return _name+": "+_value+";";
    return QString();
}
