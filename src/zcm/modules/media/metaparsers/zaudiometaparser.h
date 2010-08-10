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
