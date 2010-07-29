#ifndef ZMETAREADER_H
#define ZMETAREADER_H

#define ZCM_METAREADER      "zee:metareader"
#define ZCM_METAPROPERTY    "zee:metaproperty"

#include <QtCore>
#include <zeventmanager.h>
#include <zconfigurable.h>
#include <zmetaparser.h>
#include <metaparsers/zaudiometaparser.h>

struct ZMetadata{
    QString name;
    QString type;
    QString key;
};

class ZMetaReader : public QObject, public ZConfigurable
{
    Q_OBJECT
public:
    ZMetaReader(const ZConfig &el, QObject *parent=0);

public slots:
    void setFilename(QString location);

signals:
    void fileChanged(QString location);
    void dataChanged();

private:
    void init();
    void parse(const ZConfig &el);
    void fetchMetadata();

private:    
    QList<ZMetadata> _fields;
    QHash<QString,ZMetaParser*> _parsers;
    QFile _source;
    QObject *_dataObject;
};

#endif // ZMETAREADER_H
