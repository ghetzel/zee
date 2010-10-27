#include "ztimedsource.h"

ZTimedSource::ZTimedSource(QObject *parent)
    : QObject(parent)
{
    _timer = new QTimer(this);

    connect(_timer, SIGNAL(timeout()),
            this,   SLOT(timeout()));
}

ZTimedSource::~ZTimedSource(){
//    qDebug() << "KILL TIMER";
    if(_timer->isActive())
        _timer->stop();
}

void ZTimedSource::setInterval(int msec){
    _timer->setInterval(msec);
}

void ZTimedSource::setIntervalSec(int sec){
    _timer->setInterval(sec*1000);
}

void ZTimedSource::setSourceFunc(GSourceFunc func, gpointer data){
    _func = func;
    _data = data;
}

void ZTimedSource::start(){
//    qDebug() << "STARTING TIMER";
    _timer->start();
}

void ZTimedSource::stop(){
    if(_timer->isActive())
        _timer->stop();
}

void ZTimedSource::timeout(){
    if(_func){
        gboolean rv = _func(_data);

//      stop the timer if func returns false
        if(!rv){
//            qDebug() << "STOPPING TIMER";
            delete this;
        }
    }
}


