#include "zsound.h"

ZSound::ZSound(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    _output = new AudioOutput(Phonon::MusicCategory);
    _mediaObject = new MediaObject(this);

    parse(_config);
}

void ZSound::parse(const ZConfig &el){
    if(el.hasAttribute("src")){
        _mediaObject->setCurrentSource(MediaSource(el.attribute("src")));
    }
}
