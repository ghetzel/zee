#include "zaudioadaptor.h"

ZAudioAdaptor::ZAudioAdaptor(ZAudioManager *parent)
    : ZDBusAbstractAdaptor(parent)
{
    init();
}

ZAudioAdaptor::ZAudioAdaptor(QString name, ZAudioManager *parent)
    : ZDBusAbstractAdaptor(name,parent)
{
    init();
}

void ZAudioAdaptor::init(){
    if(instance())
        connect(instance(), SIGNAL(reachedBookmark(qint64)),
                this, SIGNAL(reachedBookmark(qint64)));

    registerService();
}

ZAudioManager *ZAudioAdaptor::instance(){
    return QCAST(ZAudioManager*,ZDBusAbstractAdaptor::instance());
}

void ZAudioAdaptor::play(){
    if(instance())
	instance()->play();
}

void ZAudioAdaptor::playSource(QString location){
    if(instance())
	instance()->playSource(location);
}

void ZAudioAdaptor::pause(){
    if(instance())
	instance()->pause();
}

void ZAudioAdaptor::togglePlay(){
    if(instance())
	instance()->togglePlay();
}

void ZAudioAdaptor::stop(){
    if(instance())
	instance()->stop();
}

void ZAudioAdaptor::next(){
    if(instance())
	instance()->next();
}

void ZAudioAdaptor::previous(){
    if(instance())
        instance()->previous();
}

void ZAudioAdaptor::enqueue(QString location){
    z_log_debug("ZAudioAdaptor: Queue "+location);
    if(instance())
        instance()->enqueue(location);
}

void ZAudioAdaptor::clear(){
    if(instance())
        instance()->clear();
}

void ZAudioAdaptor::mark(){
    if(instance())
        instance()->mark();
}

void ZAudioAdaptor::setBookmarks(QString marks){
    if(instance())
        instance()->setBookmarks(marks);
}

void ZAudioAdaptor::_stateHandler(ZAudioManager::ZAudioState state){
    switch(state){
    case ZAudioManager::Playing:
	emit playing();
	break;
    case ZAudioManager::Paused:
	emit paused();
	break;
    case ZAudioManager::Stopped:
	emit stopped();
	break;
    case ZAudioManager::Buffering:
	emit buffering();
	break;
    case ZAudioManager::Loading:
	emit loading();
	break;
    case ZAudioManager::Error:
	emit error();
	break;
    default:
	return;
    }
}
