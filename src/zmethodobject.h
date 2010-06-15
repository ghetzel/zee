#ifndef ZMETHODOBJECT_H
#define ZMETHODOBJECT_H

#include <QObject>
#include <QStringList>
#include <zutil.h>

class ZMethodObject
{
public:
    ZMethodObject();
    ZMethodObject(QObject *object, const char *method);
    QObject *object();
    void setObject(QObject *object);
    void setMethod(const char *method);
    const char *method();
    QString name();
    QStringList args();
    QString signature();
    QList<QVariant::Type> argTypes();
    bool isValid();

public:
    static QString name(const char *method);
    static QStringList args(const char *method);
    static QString signature(const char *method);
    static QList<QVariant::Type> argTypes(const char *method);
private:
    QObject *_object;
    const char *_method;
    QString _name;
    QString _signature;
    bool _null;
};

#endif // ZMETHODOBJECT_H
