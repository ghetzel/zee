#include "zmetareader.h"

ZMetaReader::ZMetaReader(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    _metadata = NULL;
    init();
}

void ZMetaReader::init(){
    parse(_config);

    zEvent->registerSignal(this, SIGNAL(fileChanged(QString)));
    zEvent->registerSlot(this, SLOT(setFile(QString)));
}

void ZMetaReader::parse(const ZConfig &el){
}

void ZMetaReader::setFile(QString location){
    if(QFile::exists(location)){
        _metadata = new ZAudioMetadata(location);
        emit fileChanged(location);
    }
}
