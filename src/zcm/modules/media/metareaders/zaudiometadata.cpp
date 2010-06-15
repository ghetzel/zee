#include "zaudiometadata.h"

ZAudioMetadata::ZAudioMetadata(QString location)
    : ZMetadata(location)
{
    _file = TagLib::FileRef::create(location.toAscii().data(),true);;
    _properties = NULL;
    _tag = NULL;

    init();
}

void ZAudioMetadata::init(){
    if(_file && _file->isValid()){
        _properties = _file->audioProperties();
        _tag = _file->tag();
    }
}

QVariant ZAudioMetadata::property(QString name){
    if(name == ZMETA_AUDIO_ARTIST)
        return QVariant(_tag->artist().toCString());
    else if(name == ZMETA_AUDIO_ALBUM)
        return QVariant(_tag->album().toCString());
    else if(name == ZMETA_AUDIO_TITLE)
        return QVariant(_tag->title().toCString());
    else if(name == ZMETA_AUDIO_GENRE)
        return QVariant(_tag->genre().toCString());
    else if(name == ZMETA_AUDIO_YEAR)
        return (_tag->year() == 0 ? QVariant("") : QVariant(_tag->year()));
    else if(name == ZMETA_AUDIO_TRACK)
        return (_tag->track() == 0 ? QVariant("") : QVariant(_tag->track()));
    else if(name == ZMETA_AUDIO_COMMENT)
        return QVariant(_tag->comment().toCString());
    else
        return QVariant();
}
