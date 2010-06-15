#include "zeventobject.h"

ZEventObject::ZEventObject(QObject *object, const char *method)
{
    _object = object;
    if(object && method)
        addMethod(method);
}

QList<ZMethodObject> ZEventObject::methods(QString key){
    if(_methods.isEmpty() || !_methods.contains(key))
        return QList<ZMethodObject>();
    return _methods.values(key);
}

void ZEventObject::setObject(QObject *object){
    if(object){
        _object = object;
        _methods.clear();
    }
}

QObject *ZEventObject::object(){
    return _object;
}

bool ZEventObject::isValid(){
    return (_object && !_methods.isEmpty());
}

void ZEventObject::addMethod(const char *method){
    z_log_debug("ZEventObject: Add method "+QString(method));
    _methods.insertMulti(ZMethodObject::name(method),
                    ZMethodObject(_object,method));
}

ZEventObject::ZMethodPair ZEventObject::match(QString localAlias,
                                              QString remoteAlias,
                                              ZEventObject &remoteObject){
// for each method in this object (keyed by localAlias), search remoteObject
// for methods keyed by remoteAlias, and return the pair of method objects that
// match.

    QList<ZMethodObject> local = methods(localAlias);
    QList<ZMethodObject> remote = remoteObject.methods(remoteAlias);
    ZMethodObject rv1, rv2;

    foreach(ZMethodObject l, local){
        foreach(ZMethodObject r, remote){
            if(l.args() == r.args()){
                rv1 = l;
                rv2 = r;
            }
        }
    }

    return qMakePair(rv1,rv2);
}
