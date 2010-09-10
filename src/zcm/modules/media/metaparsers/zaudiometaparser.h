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

#ifndef ZAUDIOMETAPARSER_H
#define ZAUDIOMETAPARSER_H

#define ZMETA_TYPE_AUDIO            "audio"

#define	ZMETA_AUDIO_FIELD_SEP	    "|"

#define ZMETA_AUDIO_ARTIST          "artist"
#define ZMETA_AUDIO_ALBUM           "album"
#define ZMETA_AUDIO_TITLE           "title"
#define ZMETA_AUDIO_GENRE           "genre"
#define ZMETA_AUDIO_TRACK           "track"
#define ZMETA_AUDIO_DISC            "disc"
#define ZMETA_AUDIO_YEAR            "year"
#define ZMETA_AUDIO_COMMENT         "comment"
#define ZMETA_AUDIO_LENGTH          "length"
#define ZMETA_AUDIO_BITRATE         "bitrate"
#define ZMETA_AUDIO_SAMPLERATE      "sample-rate"
#define ZMETA_AUDIO_CHANNELS        "channels"

#define ZMETA_AUDIO_ARTIST_FMT	    "a"
#define ZMETA_AUDIO_ALBUM_FMT       "A"
#define ZMETA_AUDIO_TITLE_FMT       "T"
#define ZMETA_AUDIO_GENRE_FMT       "G"
#define ZMETA_AUDIO_TRACK_FMT       "t"
#define ZMETA_AUDIO_DISC_FMT        "d"
#define ZMETA_AUDIO_YEAR_FMT        "y"
#define ZMETA_AUDIO_COMMENT_FMT     "C"
#define ZMETA_AUDIO_LENGTH_FMT      "l"
#define ZMETA_AUDIO_BITRATE_FMT     "b"
#define ZMETA_AUDIO_SAMPLERATE_FMT  "s"
#define ZMETA_AUDIO_CHANNELS_FMT    "c"

#include <QtCore>
#include <zutil.h>
#include <taglib/taglib.h>
#include <taglib/tag.h>
#include <taglib/tfile.h>
#include <taglib/fileref.h>
#include <taglib/flacfile.h>
#include <taglib/oggflacfile.h>
#include <taglib/oggfile.h>
#include <taglib/audioproperties.h>
#include <taglib/tmap.h>
#include <zcm/modules/media/zmetaparser.h>

class ZAudioMetaParser : public QObject, public ZMetaParser{
    Q_OBJECT

public:
    ZAudioMetaParser();
    ZAudioMetaParser(QString location);
    virtual void setFileName(QString location);
    virtual QVariant field(QString name);
    virtual QVariant fieldf(QString format);
    virtual QString type();

private slots:
    void _fileChanged();

private:
    void init();

private:
    TagLib::File *_file;
    TagLib::AudioProperties *_properties;
    TagLib::Tag *_tag;
};

#endif // ZAUDIOMETAPARSER_H
