#ifndef ZMETAPARSER_H
#define ZMETAPARSER_H

#include <QString>
#include <QVariant>
#include <QFile>

class ZMetaParser{
public:
    virtual void setFileName(QString location)=0;
    virtual QVariant field(QString name)=0;
    virtual QVariant fieldf(QString format)=0;
    virtual QString type()=0;

protected:
    QString _name;
    QFile _location;
};

#endif // ZMETAPARSER_H
