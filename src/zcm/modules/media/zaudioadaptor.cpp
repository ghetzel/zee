#include "zaudioadaptor.h"

ZAudioAdaptor::ZAudioAdaptor(ZAudioManager *parent)
    : QDBusAbstractAdaptor(parent),
      _instance(parent)
{
    init();
}

ZAudioAdaptor::ZAudioAdaptor(QString name, ZAudioManager *parent)
    : QDBusAbstractAdaptor(parent),
      _instance(parent)
{
    if(name.isEmpty())
        _name = name;
    init();
}

void ZAudioAdaptor::init(){
//  if name isn't set yet...
    if(_name.isEmpty())
        if(_instance && !_instance->objectName().isEmpty())
            _name = _instance->objectName();
        else
            _name = ZAUDIO_DBUS_NAME;

    if(_instance){
        QDBusConnection::sessionBus().registerObject(ZAUDIO_DBUS_OPATH+_name,
                                                     _instance);
        QDBusConnection::sessionBus().registerService(ZAUDIO_DBUS_SVCNM);
    }
}

void ZAudioAdaptor::play(){
    if(_instance){
        _instance->play();
    }
}

void ZAudioAdaptor::pause(){
    if(_instance){
        _instance->pause();
    }
}

void ZAudioAdaptor::togglePlay(){
    if(_instance){
        _instance->togglePlay();
    }
}

void ZAudioAdaptor::stop(){
    if(_instance)
        _instance->stop();
}

void ZAudioAdaptor::next(){
    if(_instance)
        _instance->next();
}

void ZAudioAdaptor::previous(){
//    if(_instance)
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
