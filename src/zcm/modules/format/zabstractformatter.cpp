#include "zabstractformatter.h"

ZAbstractFormatter::ZAbstractFormatter(QObject *parent)
    : ZFormatterInterface(parent){
}

ZAbstractFormatter::ZAbstractFormatter(QString method, QObject *parent)
    : ZFormatterInterface(parent){
    setMethod(method);
}

void ZAbstractFormatter::setMethod(QString method){
    _method = method;
}

QString ZAbstractFormatter::method() const{
    return _method;
}


void ZAbstractFormatter::setParam(QString key, QVariant val){
    _args.insert(key, val);
}


QVariant ZAbstractFormatter::arg(QString key, QString fallback){
    if(_args.contains(key))
        return _args.value(key);
    else
        return _args.value(fallback);
}
