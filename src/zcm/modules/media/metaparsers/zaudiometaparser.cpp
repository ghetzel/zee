#include "zaudiometaparser.h"

ZAudioMetaParser::ZAudioMetaParser(QString location)
{
    setFileName(location);
    init();
}

void ZAudioMetaParser::init(){}

void ZAudioMetaParser::setFileName(QString location){
    _file = TagLib::FileRef::create(location.toAscii().data(),true);
    _properties = NULL;
    _tag = NULL;

    if(_file && _file->isValid()){
        _properties = _file->audioProperties();
        _tag = _file->tag();
    }
}

QVariant ZAudioMetaParser::field(QString name){
    if(_tag){
        if(name == ZMETA_AUDIO_ARTIST){
            return QVariant(_tag->artist().toCString());
        }else if(name == ZMETA_AUDIO_ALBUM){
            return QVariant(_tag->album().toCString());
        }else if(name == ZMETA_AUDIO_TITLE){
            return QVariant(_tag->title().toCString());
        }else if(name == ZMETA_AUDIO_GENRE){
            return QVariant(_tag->genre().toCString());
        }else if(name == ZMETA_AUDIO_YEAR){
            return (_tag->year() == 0 ? QVariant("") : QVariant(_tag->year()));
        }else if(name == ZMETA_AUDIO_TRACK){
            return (_tag->track() == 0 ? QVariant("") : QVariant(_tag->track()));
        }else if(name == ZMETA_AUDIO_COMMENT){
            return QVariant(_tag->comment().toCString());
        }else if(name == ZMETA_AUDIO_LENGTH){
            if(_properties)
                return QVariant(_properties->length());
        }else if(name == ZMETA_AUDIO_BITRATE){
            if(_properties)
                return QVariant(_properties->bitrate());
        }else if(name == ZMETA_AUDIO_SAMPLERATE){
            if(_properties)
                return QVariant(_properties->sampleRate());
        }else if(name == ZMETA_AUDIO_CHANNELS){
            if(_properties)
                return QVariant(_properties->channels());
        }else{
            return QVariant();
        }
    }

    return QVariant();
}

QString ZAudioMetaParser::type(){
    return ZMETA_TYPE_AUDIO;
}
