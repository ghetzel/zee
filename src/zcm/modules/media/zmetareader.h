#ifndef ZMETAREADER_H
#define ZMETAREADER_H

#define ZEE_METAREADER          "zee:metareader"

#include <QtCore>
#include <zconfigurable.h>
#include <zeventmanager.h>
#include <zmetadata.h>
#include <metareaders/zaudiometadata.h>

class ZMetaReader : public QObject, public ZConfigurable
{
    Q_OBJECT
public:
    ZMetaReader(const ZConfig &el, QObject *parent=0);
    void parse(const ZConfig &el);

public slots:
    void setFile(QString location);

signals:
    void fileChanged(QString);

private:
    void init();

private:    
    ZMetadata *_metadata;
};

#endif // ZMETAREADER_H
