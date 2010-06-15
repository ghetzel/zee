#ifndef ZAUDIOMETADATA_H
#define ZAUDIOMETADATA_H

#define ZMETA_AUDIO_ARTIST          "artist"
#define ZMETA_AUDIO_ALBUM           "album"
#define ZMETA_AUDIO_TITLE           "title"
#define ZMETA_AUDIO_GENRE           "genre"
#define ZMETA_AUDIO_TRACK           "track"
#define ZMETA_AUDIO_DISC            "disc"
#define ZMETA_AUDIO_YEAR            "year"
#define ZMETA_AUDIO_BITRATE         "bitrate"
#define ZMETA_AUDIO_SAMPLERATE      "sample-rate"
#define ZMETA_AUDIO_COMMENT         "comment"

#include <QtCore>
#include <taglib/taglib.h>
#include <taglib/tag.h>
#include <taglib/tfile.h>
#include <taglib/fileref.h>
#include <taglib/audioproperties.h>
#include <zcm/modules/media/zmetadata.h>

class ZAudioMetadata : public QObject, public ZMetadata{
    Q_OBJECT

public:
    ZAudioMetadata();
    ZAudioMetadata(QString location);
    virtual QVariant property(QString name);

private:
    void init();

private:
    TagLib::File *_file;
    TagLib::AudioProperties *_properties;
    TagLib::Tag *_tag;
};

#endif // ZAUDIOMETADATA_H
