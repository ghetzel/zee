#ifndef ZMETAPARSER_H
#define ZMETAPARSER_H

#include <QString>
#include <QVariant>
#include <QFile>

class ZMetaParser{
public:
    ZMetaParser(){}
    ZMetaParser(QString location){
        setFileName(location);
    }

    void setFileName(QString location){
        _location.setFileName(location);
    }

    virtual QVariant field(QString name)=0;
    virtual QString type()=0;

protected:
    QString _name;
    QFile _location;
};

#endif // ZMETAPARSER_H
