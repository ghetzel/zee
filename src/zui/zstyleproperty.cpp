#include "zstyleproperty.h"

ZStyleProperty::ZStyleProperty(ZStyleSection *parent)
    : QObject(RECAST(QObject*,parent))
{
    init();
}

ZStyleProperty::ZStyleProperty(QString value)
{
    _value = value.trimmed();
    init();
}

ZStyleProperty::ZStyleProperty(QString name, QString value, ZStyleSection *parent)
    : QObject(RECAST(QObject*,parent))
{
    _parent = parent;

    name = name.trimmed();
    value = value.trimmed();

//  if parent is not specified, allow blind creation
//  if parent IS specified, then we must have a name:value pair
    if(!parent || parent && !(name.isEmpty() && value.isEmpty())){
        _name = name;
        _value = value;
        init();
    }else{
        z_log_warn("ZStyleProperty: Property name and value must be specified.");
    }
}

void ZStyleProperty::init(){
    parse();
}

void ZStyleProperty::parse(){
    if(!_value.isEmpty()){
        bool ok;
        ZString res;

        if(ZUtil::in(_value, ZSTYLE_PROP_BOOL_TRUE)){
            _toBool = true;
        }else{
            _toBool = false;
        }

    //  lengths and box values
    //       1px; 1px 2px; 1em 2 3px; 1 2 3px 4px; etc...
        if(!(res = _value.match(QRegExp(ZSTYLE_PROP_MATCH_BOX))).isEmpty()){
            QStringList rs = res.split(QRegExp("("ZSTYLE_PROP_LENGTH")\\s*"), QString::SkipEmptyParts);
            switch(rs.length()){
            case 1:
                _quad.setTop(rs.at(0).toDouble());
                _quad.setRight(rs.at(0).toDouble());
                _quad.setBottom(rs.at(0).toDouble());
                _quad.setLeft(rs.at(0).toDouble());
                break;
            case 2:
                _quad.setTop(rs.at(0).toDouble());
                _quad.setRight(rs.at(1).toDouble());
                _quad.setBottom(rs.at(0).toDouble());
                _quad.setLeft(rs.at(1).toDouble());
                break;
            case 3:
                _quad.setTop(rs.at(0).toDouble());
                _quad.setRight(rs.at(1).toDouble());
                _quad.setBottom(rs.at(2).toDouble());
                _quad.setLeft(rs.at(1).toDouble());
                break;
            case 4:
                _quad.setTop(rs.at(0).toDouble());
                _quad.setRight(rs.at(1).toDouble());
                _quad.setBottom(rs.at(2).toDouble());
                _quad.setLeft(rs.at(3).toDouble());
                break;
            }
        }
    }
}

ZStyleSection *ZStyleProperty::section(){
    return _parent;
}

QString ZStyleProperty::toString(){
    if(!(_name.isEmpty() && _value.isEmpty()))
        return _name+": "+_value+";";
    return QString();
}

ZStyleProperty &ZStyleProperty::valueFrom(QString rawValue){
    ZStyleProperty rv(rawValue);
    return rv;
}
