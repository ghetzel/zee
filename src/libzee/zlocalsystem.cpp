#include "zlocalsystem.h"

ZLocalSystem *ZLocalSystem::_instance = NULL;

ZLocalSystem::ZLocalSystem(){
}

QDateTime ZLocalSystem::systemTime(){
    return QDateTime::currentDateTime();
}

qint64 ZLocalSystem::systemTimeEpoch(){
    QDateTime sdt = systemTime();
    return ((qint64)sdt.toTime_t()*(qint64)1000)+(qint64)sdt.time().msec();
}

ZLocalSystem::SystemLoad ZLocalSystem::systemLoad(){

}

qint64 ZLocalSystem::uptime(){

}



ZLocalSystem *ZLocalSystem::instance(){
    if(!_instance)
	_instance = new ZLocalSystem();
    return _instance;
}
