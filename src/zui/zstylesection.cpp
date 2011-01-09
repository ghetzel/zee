#include "zstylesection.h"

ZStyleSection::ZStyleSection(ZStyle *parent)
{
    _parent = parent;
}

ZStyleSection::ZStyleSection(QString rule, QString data, ZStyle *parent){
    _parent = parent;

    rule = rule.trimmed();
    data = data.trimmed();

    if(!rule.isEmpty()){
        _rule = rule;
        _data = data;
        parse(data);
    }else{
        z_log_warn("ZStyleSection: Cannot specify a section without a rule.");
    }
}

void ZStyleSection::parse(QString data){
    QRegExp rx("([A-Za-z0-9\\s>_-]*)(?:\\s*:\\s*)([^;]*)(?:\\s*;\\s*)");
    bool stripSubControl = false;
    int i = 0;
    while((i = rx.indexIn(data,i)) != -1){
        QString propname = rx.cap(1).trimmed();

        if(0){
#ifdef ZSTYLE_SUBCONTROLS
        }else if(ZUtil::in(_rule.rightOfLast("::"), ZSTYLE_SUBCONTROLS)){
            stripSubControl = true;
            QString qpSub = "qproperty-"+ZString::camelize(_rule.rightOfLast("::")+"_"+propname);
            _properties.insert(qpSub, new ZStyleProperty(qpSub, rx.cap(2),this));
#endif
#ifdef ZSTYLE_PROPSUB_AG_FIXED_HEIGHT
        }else if(propname == ZSTYLE_PROPSUB_AG_FIXED_HEIGHT){
            _properties.insert("min-height", new ZStyleProperty("min-height",rx.cap(2),this));
            _properties.insert("max-height", new ZStyleProperty("max-height",rx.cap(2),this));
#endif
#ifdef ZSTYLE_PROPSUB_AG_FIXED_WIDTH
        }else if(propname == ZSTYLE_PROPSUB_AG_FIXED_WIDTH){
            _properties.insert("min-width", new ZStyleProperty("min-width",rx.cap(2),this));
            _properties.insert("max-width", new ZStyleProperty("max-width",rx.cap(2),this));
#endif
        }else{
            _properties.insert(propname, new ZStyleProperty(propname,rx.cap(2),this));
        }
        i += rx.matchedLength();
    }

    if(stripSubControl)
        _rule = _rule.leftOfLast("::");
}

ZStyle *ZStyleSection::style(){
    return _parent;
}

void ZStyleSection::pushProperty(ZStyleProperty *property){
    if(property)
        if(!property->name().isEmpty())
            _properties.insert(property->name(), property);
}

ZStyleSection &ZStyleSection::merge(const ZStyleSection &first, const ZStyleSection &second){
    ZStyleSection rv;

    foreach(ZStyleProperty *property, first._properties){
        rv.pushProperty(property);
    }

    foreach(ZStyleProperty *property, second._properties){
        rv.pushProperty(property);
    }

    return rv;
}

ZStyleSection &ZStyleSection::merge(const ZStyleSection &other){
    return ZStyleSection::merge(*this, other);
}

QString ZStyleSection::toString(){
    QString rv = _rule+"{\n";

    foreach(ZStyleProperty *property, _properties.values()){
        rv += "\t" + property->toString()+"\n";
    }

    return rv+"}";
}
