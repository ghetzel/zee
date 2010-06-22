#ifndef ZMETAREADER_H
#define ZMETAREADER_H

#include <QtCore>
#include <zmetadata.h>
#include <metareaders/zaudiometadata.h>

class ZMetaReader : public QObject
{
    Q_OBJECT
public:
    ZMetaReader(QString location);

private:
    void init();
    void setFilename(QString location);

private:    
    ZMetadata *_metadata;
};

#endif // ZMETAREADER_H
