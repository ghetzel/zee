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
            if(_tag->title().isEmpty())
                return QVariant(QString(_file->name()).section("/",-1,-1).section(".",0,-2));
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

QVariant ZAudioMetaParser::fieldf(QString format){
    QStringList matches = format.split(QRegExp("\\b"));
    QString out = format;
    foreach(QString match, matches){
	QString pattern = match.remove('%');
	QVariant val;

	if(pattern == ZMETA_AUDIO_ALBUM_FMT){
	    val = field(ZMETA_AUDIO_ALBUM);
	}else if(pattern == ZMETA_AUDIO_ARTIST_FMT){
	    val = field(ZMETA_AUDIO_ARTIST);
	}else if(pattern == ZMETA_AUDIO_BITRATE_FMT){
	    val = field(ZMETA_AUDIO_BITRATE);
	}else if(pattern == ZMETA_AUDIO_CHANNELS_FMT){
	    val = field(ZMETA_AUDIO_CHANNELS);
	}else if(pattern == ZMETA_AUDIO_COMMENT_FMT){
	    val = field(ZMETA_AUDIO_COMMENT);
	}else if(pattern == ZMETA_AUDIO_DISC_FMT){
	    val = field(ZMETA_AUDIO_DISC);
	}else if(pattern == ZMETA_AUDIO_GENRE_FMT){
	    val = field(ZMETA_AUDIO_GENRE);
	}else if(pattern == ZMETA_AUDIO_LENGTH_FMT){
	    val = field(ZMETA_AUDIO_LENGTH);
	}else if(pattern == ZMETA_AUDIO_SAMPLERATE_FMT){
	    val = field(ZMETA_AUDIO_SAMPLERATE);
	}else if(pattern == ZMETA_AUDIO_TITLE_FMT){
	    val = field(ZMETA_AUDIO_TITLE);
	}else if(pattern == ZMETA_AUDIO_TRACK_FMT){
	    val = field(ZMETA_AUDIO_TRACK);
	}else if(pattern == ZMETA_AUDIO_YEAR_FMT){
	    val = field(ZMETA_AUDIO_YEAR);
	}

	if(!val.isValid())
	    out.replace(match, val.toString());
    }

    z_log("ZAudioMetaParser: fieldf = '"+out+"'");
    return QVariant(out);
}

QString ZAudioMetaParser::type(){
    return ZMETA_TYPE_AUDIO;
}
