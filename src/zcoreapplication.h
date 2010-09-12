#ifndef ZCOREAPPLICATION_H
#define ZCOREAPPLICATION_H

#include <QVariant>

class ZCoreApplication{
public:
    virtual QVariant arg(QString key)=0;
    virtual bool hasArg(QString key)=0;
};

#endif // ZCOREAPPLICATION_H
