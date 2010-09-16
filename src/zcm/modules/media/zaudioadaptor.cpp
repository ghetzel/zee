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
    if(instance()){
        connect(instance(), SIGNAL(bookmarkAdded(qint64)),
                this,       SIGNAL(bookmarkAdded(qint64)));
        connect(instance(), SIGNAL(bufferChanged(int)),
                this,       SIGNAL(bufferChanged(int)));
        connect(instance(), SIGNAL(buffering()),
                this,       SIGNAL(buffering()));
        connect(instance(), SIGNAL(durationChanged(qint64)),
                this,       SIGNAL(durationChanged(qint64)));
        connect(instance(), SIGNAL(loading()),
                this,       SIGNAL(loading()));
        connect(instance(), SIGNAL(paused()),
                this,       SIGNAL(paused()));
        connect(instance(), SIGNAL(playing()),
                this,       SIGNAL(playing()));
        connect(instance(), SIGNAL(positionChanged(double)),
                this,       SIGNAL(positionChanged(double)));
        connect(instance(), SIGNAL(queueChanged()),
                this,       SIGNAL(queueChanged()));
        connect(instance(), SIGNAL(queueCleared()),
                this,       SIGNAL(queueCleared()));
        connect(instance(), SIGNAL(queuedSongChanged(int)),
                this,       SIGNAL(queuedSongChanged(int)));
	connect(instance(), SIGNAL(reachedBookmark(qint64)),
                this,       SIGNAL(reachedBookmark(qint64)));
        connect(instance(), SIGNAL(sourceChanged(QString)),
                this,       SIGNAL(sourceChanged(QString)));
        connect(instance(), SIGNAL(stopped()),
                this,       SIGNAL(stopped()));
        connect(instance(), SIGNAL(timeChanged(qint64)),
                this,       SIGNAL(timeChanged(qint64)));
    }

    registerService();
}

ZAudioManager *ZAudioAdaptor::instance(){
    return QCAST(ZAudioManager*,ZDBusAbstractAdaptor::instance());
}

void ZAudioAdaptor::changeTo(QString location){
    if(instance()) instance()->changeTo(location);                           }

void ZAudioAdaptor::clear(){
    if(instance()) instance()->clear();                                      }

void ZAudioAdaptor::clearBookmarks(){
    if(instance()) instance()->clearBookmarks();                             }

void ZAudioAdaptor::clearQueue(){
    if(instance()) instance()->clearQueue();                                 }

void ZAudioAdaptor::enqueue(QString location){
    if(instance()) instance()->enqueue(location);                            }

void ZAudioAdaptor::mark(){
    if(instance()) instance()->mark();                                       }

void ZAudioAdaptor::next(){
    if(instance()) instance()->next();                                       }

void ZAudioAdaptor::pause(){
    if(instance()) instance()->pause();                                      }

void ZAudioAdaptor::play(){
    if(instance()) instance()->play();                                       }

void ZAudioAdaptor::playSource(QString location){
    if(instance()) instance()->playSource(location);                         }

void ZAudioAdaptor::previous(){
    if(instance()) instance()->previous();                                   }

void ZAudioAdaptor::remove(QString location){
    if(instance()) instance()->remove(location);                             }

void ZAudioAdaptor::seek(qint64 position){
    if(instance()) instance()->seek(position);                               }

void ZAudioAdaptor::setBookmarks(QString marks){
    if(instance()) instance()->setBookmarks(marks);                          }

void ZAudioAdaptor::setCrossfade(int msec){
    if(instance()) instance()->setCrossfade(msec);                           }

void ZAudioAdaptor::setGapless(){
    if(instance()) instance()->setGapless();                                 }

void ZAudioAdaptor::setSource(QString location){
    if(instance()) instance()->setSource(location);                          }

void ZAudioAdaptor::stop(){
    if(instance()) instance()->stop();                                       }

void ZAudioAdaptor::togglePlay(){
    if(instance()) instance()->togglePlay();                                 }

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
