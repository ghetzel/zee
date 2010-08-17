#ifndef ZAUDIOMETAPARSER_H
#define ZAUDIOMETAPARSER_H

#define ZMETA_TYPE_AUDIO            "audio"

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
#include <taglib/audioproperties.h>
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
