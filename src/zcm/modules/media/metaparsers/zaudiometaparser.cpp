/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

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
	//  Arbitrary Field Name Tag Query
	//
	//  A little dirty, but it gets the job done.
	//
	//  Test for specific kinds of tags, because certain tags
	//  are just name-value pairs, which let's us pull out
	//  field names not explcitly defined above.
	//  An example of this are Xiph Comments, which can contain any
	//  field name.  If a given key is requested, check to see if it is a
	//  tag type that can be queried like this, then do so.
	    TagLib::String tlKeyName(name.toUpper().toLatin1().data());

	//  FLAC Xiph Tag
	    if(DCAST(TagLib::FLAC::File*,_file)){
	    //	if the tag contains the field name...
		if(DCAST(TagLib::FLAC::File*,_file)->xiphComment(0)->contains(
			tlKeyName)){
		//  grab the STL map of all fields
		    TagLib::Ogg::FieldListMap flm = DCAST(
			    TagLib::FLAC::File*,
			    _file)->xiphComment(0)->fieldListMap();
		//  find the field name, grab its iterator
		    TagLib::Ogg::FieldListMap::ConstIterator i =
			    flm.find(tlKeyName);
		//  if the field came back, return the joined output of all tags
		    if(i != flm.end()){
			return QVariant(i->second.toString(
				ZMETA_AUDIO_FIELD_SEP).toCString());
		    }
		}
		    z_log_debug("ZAudioMetaParser: FLAC");
		    return QVariant();
	    }
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
