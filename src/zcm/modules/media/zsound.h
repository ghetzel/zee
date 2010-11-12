#ifndef ZSOUND_H
#define ZSOUND_H

#include <zconfigurable.h>
#include <zeventmanager.h>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>

using namespace Phonon;

class ZSound : public QObject, public ZConfigurable
{
public:
    ZSound(const ZConfig &el, QObject *parent=0);

private:
    void parse(const ZConfig &el);

private:
    QString _file;
    AudioOutput *_output;
    MediaObject *_mediaObject;
};

#endif // ZSOUND_H
