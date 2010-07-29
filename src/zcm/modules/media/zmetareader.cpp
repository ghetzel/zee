#include "zmetareader.h"

ZMetaReader::ZMetaReader(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    _dataObject = new QObject(this);
    _dataObject->setObjectName("data");

    parse(_config);
    init();
}

void ZMetaReader::init(){
    zEvent->registerSignal(this, SIGNAL(fileChanged(QString)));
    zEvent->registerSignal(this, SIGNAL(dataChanged()));
    zEvent->registerSlot(this, SLOT(setFileName(QString)));
}

void ZMetaReader::parse(const ZConfig &el){
    QDomNodeList children = el.childNodes();
    QDomElement elem;
    QString metatype;

    for(int i = 0; i < children.count(); i++){
        if(!(elem = children.item(i).toElement()).isNull()){
            if(elem.tagName() == ZCM_METAPROPERTY){
                if(!(metatype = elem.attribute("type")).isEmpty() &&
                   elem.hasAttribute("name") &&
                   elem.hasAttribute("key"))
                {
                    ZMetadata md;
                    md.name = elem.attribute("name");
                    md.type = metatype;
                    md.key = elem.attribute("key");
                    _fields.append(md);

                    //z_log_debug("ZMetaReader: Register metadata parser for type '"+metatype+"'");

                    if(!_parsers.contains(md.type)){
                        if(0){
    #ifdef ZMETA_TYPE_AUDIO
                        }else if(metatype == ZMETA_TYPE_AUDIO){
                            _parsers.insert(md.type, new ZAudioMetaParser(_source.fileName()));
    #endif
    #ifdef ZMETA_TYPE_IMAGE
                        }else if(metatype == ZMETA_TYPE_IMAGE){
    #endif
    #ifdef ZMETA_TYPE_IMAGE_EXIF
                        }else if(metatype == ZMETA_TYPE_IMAGE_EXIF){
    #endif
                        }
                    }
                }
            }
        }
    }
}

void ZMetaReader::setFileName(QString location){
    location = QUrl(location).path();

    if(QFile::exists(location)){
        _source.setFileName(location);

        foreach(ZMetaParser *p, _parsers.values())
            p->setFileName(location);
        emit fileChanged(location);
        fetchMetadata();
    }else{
        z_log_error("ZMetaReader: Cannot find file '"+location+"'");
    }
}

void ZMetaReader::fetchMetadata(){
    ZMetaParser *parser = NULL;

    if(_dataObject){
        foreach(ZMetadata meta, _fields){
            parser = _parsers.value(meta.type);

            if(parser){
                _dataObject->setProperty(qstrdup(meta.name.toAscii().data()),
                                         parser->field(meta.key));
                if(_dataObject->property(qstrdup(meta.name.toAscii().data())).isValid())
                    z_log_debug("ZMetaReader: Property updated -> "+meta.name+"="+
                            _dataObject->property(qstrdup(meta.name.toAscii().data())).toString());
            }else{
                z_log_error("ZMetaReader: Parser for type '"+meta.type+"' not found.");
            }
        }

        emit dataChanged();
    }
}
