#ifndef ZFORMATTERINTERFACE_H
#define ZFORMATTERINTERFACE_H

#include <QVariant>

class ZFormatterInterface : public QObject{
    Q_OBJECT

public:
    ZFormatterInterface(QObject *parent=0) : QObject(parent){};

public slots:
    virtual QVariant transform(QVariant)=0;
};

#endif // ZFORMATTERINTERFACE_H
