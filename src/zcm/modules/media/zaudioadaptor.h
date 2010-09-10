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

#ifndef ZAUDIOADAPTOR_H
#define ZAUDIOADAPTOR_H

#include <zdbusabstractadaptor.h>
#include <zaudiomanager.h>

class ZAudioAdaptor : public ZDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "net.gammazeta.zee.AudioManager")

public:
    ZAudioAdaptor(ZAudioManager *parent);
    ZAudioAdaptor(QString name, ZAudioManager *parent);

public slots:
    void play();
    void playSource(QString);
    void pause();
    void togglePlay();
    void stop();
    void next();
    void previous();
    void enqueue(QString);
    void clear();
    void mark();
    void setBookmarks(QString);

signals:
    void playing();
    void paused();
    void stopped();
    void loading();
    void buffering();
    void error();
    void reachedBookmark(qint64);

private:
    void init();
    ZAudioManager *instance();
    void _stateHandler(ZAudioManager::ZAudioState state);

private:
    ZAudioManager *_instance;
    QString _name;
};

#endif // ZAUDIOADAPTOR_H
