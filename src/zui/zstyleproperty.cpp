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

ZStyleProperty::ZStyleProperty(const ZStyleProperty &other){
    _parent = other._parent;
    _name = other._name;
    _value = other._value;
    _width = other._width;
    _height = other._height;
    _quad = other._quad;
    _style = other._style;
    _color = other._color;
    _pen = other._pen;
    _brush = other._brush;
    _toBool = other._toBool;
}

ZStyleProperty::~ZStyleProperty(){

}

void ZStyleProperty::init(){
    parse();
}

void ZStyleProperty::parse(){
    if(!_value.isEmpty()){
        bool ok;
        ZString res;
        QRegExp rx;

        if(ZUtil::in(_value, ZSTYLE_PROP_BOOL_TRUE)){
            _toBool = true;
        }else{
            _toBool = false;
        }

    //  lengths and box values
    //       1px; 1px 2px; 1em 2 3px; 1 2 3px 4px; etc...
        rx = QRegExp(ZSTYLE_PROP_MATCH_BOX);
        if(_value.match(rx)){
            res = _value.find(rx);
            QStringList rs = res.split(QRegExp("("ZSTYLE_PROP_LENGTH")\\s*"), QString::SkipEmptyParts);
            switch(rs.length()){
            case 1:
                _width = rs.at(0).toDouble();
                _height = rs.at(0).toDouble();
                _quad.setTop(rs.at(0).toDouble());
                _quad.setRight(rs.at(0).toDouble());
                _quad.setBottom(rs.at(0).toDouble());
                _quad.setLeft(rs.at(0).toDouble());
                break;
            case 2:
                _width = rs.at(0).toDouble();
                _height = rs.at(1).toDouble();
                _quad.setTop(rs.at(0).toDouble());
                _quad.setRight(rs.at(1).toDouble());
                _quad.setBottom(rs.at(0).toDouble());
                _quad.setLeft(rs.at(1).toDouble());
                break;
            case 3:
                _width = rs.at(0).toDouble();
                _height = rs.at(1).toDouble();
                _quad.setTop(rs.at(0).toDouble());
                _quad.setRight(rs.at(1).toDouble());
                _quad.setBottom(rs.at(2).toDouble());
                _quad.setLeft(rs.at(1).toDouble());
                break;
            case 4:
                _width = rs.at(0).toDouble();
                _height = rs.at(1).toDouble();
                _quad.setTop(rs.at(0).toDouble());
                _quad.setRight(rs.at(1).toDouble());
                _quad.setBottom(rs.at(2).toDouble());
                _quad.setLeft(rs.at(3).toDouble());
                break;
            }
        }


    //  colors
        rx = QRegExp(ZSTYLE_PROP_COLOR_HEX);
        if(_value.match(rx)){
            ZString hex = rx.cap(1);
            if(!hex.isEmpty()){
                int alpha = 255;
                QString val;

                switch(hex.length()){
                case 3:
                    val = hex.left(1).repeat(2)+hex.substring(1,1).repeat(2)+hex.right(1).repeat(2);
                    break;
                case 4:
                    val = hex.left(1).repeat(2)+hex.substring(1,1).repeat(2)+hex.substring(2,1).repeat(2);
                    alpha = hex.right(1).repeat(2).toInt(&ok,16);
                    _color = QColor("#"+val);
                    if(ok)
                        _color.setAlpha(alpha);
                    break;
                case 6:
                    _color = QColor("#"+hex);
                    break;
                case 8:
                    _color = QColor("#"+hex.left(6));
                    alpha = hex.right(2).toInt(&ok,16);
                    if(ok)
                        _color.setAlpha(alpha);
                    break;
                }
            }
        }else{
            rx = QRegExp(ZSTYLE_PROP_COLOR_RGB);
            if(_value.match(rx) && rx.captureCount() == 3){
                _color = QColor(ZString(rx.cap(1)).fromPercent(256),
                                ZString(rx.cap(2)).fromPercent(256),
                                ZString(rx.cap(3)).fromPercent(256));
            }else{
                rx = QRegExp(ZSTYLE_PROP_COLOR_RGBA);
                if(_value.match(rx)){
                    _color = QColor(ZString(rx.cap(1)).fromPercent(256),
                                    ZString(rx.cap(2)).fromPercent(256),
                                    ZString(rx.cap(3)).fromPercent(256),
                                    ZString(rx.cap(4)).fromPercent(256));
                }
            }
        }
    }
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

ZStyleProperty &ZStyleProperty::valueFrom(QString rawValue){
    ZStyleProperty rv(rawValue);
    return rv;
}
