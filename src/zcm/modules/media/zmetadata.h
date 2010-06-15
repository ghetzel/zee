#ifndef ZMETADATA_H
#define ZMETADATA_H

#include <QString>
#include <QVariant>
#include <QFile>

class ZMetadata{
public:
    ZMetadata(){}
    ZMetadata(QString location){
        setFileName(location);
    }
    void setFileName(QString location){
        _location.setFileName(location);
    }
    virtual QVariant property(QString name)=0;

protected:
    QFile _location;
};

#endif // ZMETADATA_H
