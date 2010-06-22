#include "zmetareader.h"

ZMetaReader::ZMetaReader(QString location)
    : QObject(parent)
{
    setFilename(location);
    _metadata = NULL;
    init();
}

void ZMetaReader::init(){

}

void ZMetaReader::setFilename(QString location){
    if(QFile::exists(location)){
        _metadata = new ZAudioMetadata(location);
    }
}
