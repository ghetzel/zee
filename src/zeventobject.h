#ifndef ZEVENTOBJECT_H
#define ZEVENTOBJECT_H

#include <QtCore>
#include <zutil.h>
#include <zmethodobject.h>

class ZEventObject
{
public:
    typedef QPair<ZMethodObject,ZMethodObject> ZMethodPair;
    ZEventObject(QObject *object=0, const char *method=0);
    QList<ZMethodObject> methods(QString key);
    void setObject(QObject *object);
    QObject *object();
    void addMethod(const char *method);
    bool isValid();
    ZMethodPair match(QString localAlias,
                      QString remoteAlias,
                      ZEventObject &remoteObject);
    static ZMethodPair matchMethodsBySignature(QList<ZMethodObject> signal,
                                               QList<ZMethodObject> slot,
                                               bool ignoreTypes=false);

private:
    QObject *_object;
    QHash<QString, ZMethodObject> _methods;

private:
    void init();
};

#endif // ZEVENTOBJECT_H
