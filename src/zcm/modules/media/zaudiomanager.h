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

#ifndef ZAUDIOMANAGER_H
#define ZAUDIOMANAGER_H
#define ZEE_AUDIO	    "zee:media"
#define	ZAUDIO_BM_ERROR	    1000    // error margin (in ms) for bookmark detects


#include <QtCore>
#include <QAbstractListModel>
#include <phonon/audiooutput.h>
#include <phonon/mediaobject.h>
#include <phonon/mediasource.h>
#include <zconfigurable.h>
#include <zeventmanager.h>
#include <metaparsers/zaudiometaparser.h>

class ZAudioAdaptor;

class ZAudioManager : public QAbstractListModel, public ZConfigurable
{
    Q_OBJECT
    Q_ENUMS(ZAudioState)
    Q_PROPERTY(QStringList queue READ queue)
    Q_PROPERTY(qint64 currentTime READ currentTime)
    Q_PROPERTY(qint64 position READ currentTime)
    Q_PROPERTY(ZAudioState state READ state)

public:
    enum ZAudioState{
        Playing,
        Paused,
        Stopped,
        Loading,
        Buffering,
        Error
    };

public:
    ZAudioManager(const ZConfig &el, QObject *parent=0);
    virtual ~ZAudioManager();
    void parse(const ZConfig&);
    QStringList queue();
    int rowCount(const QModelIndex&) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QString currentQueueSource();
    ZAudioState state();
    void setAdaptor(ZAudioAdaptor *adaptor);
    //bool removeRow(int row, const QModelIndex &parent=QModelIndex());


public slots:
    void play();
    void pause();
    void stop();
    void next();
    void togglePlay();
    void previous();
    void mark();
    void seek(qint64 position);
    void playSource(QString location);
    void playSource(QUrl location);
    void setSource(QString location);
    void setSource(QUrl location);
    void changeTo(QString location);
    void changeTo(QUrl location);
    void enqueue(QStringList locations);
    void enqueue(QString location);
    void enqueue(QUrl location);
    void remove(QString location);
    void remove(QUrl location);
    void setQueue(QStringList locations);
    void clearQueue();
    void clearBookmarks();
    void clear();
    void setGapless();
    void setCrossfade(int);
    void setBookmark(qint64);
    void setBookmark(QString,qint64);
    void setBookmarks(QString);
    void setBookmarks(QString,QString);


signals:
    void playing();
    void paused();
    void stopped();
    void buffering();
    void loading();
    void stateChanged(ZAudioState);
    void positionChanged(double);
    void elapsed(qint64);
    void remaining(qint64);
    void durationChanged(qint64);
    void bufferChanged(int);
    void sourceChanged(QString);
    void queuedSongChanged(int);
    void queueCleared();
    void queueChanged();
    void bookmarkAdded(qint64);
    void reachedBookmark(qint64);

private:
    Phonon::AudioOutput *_output;
    Phonon::MediaObject *_mediaObject;
    Phonon::MediaObject *_resolver;
    QStringList _sourceQueue;
    QHash<QString,QString> _displayTexts;
    QHash<QString,qint64> _bookmarks;
    QHash<QString,QIODevice*> _buffer;
    int _currentQueueSource;
    ZAudioState _state;
    ZAudioAdaptor *_adaptor;

private:
    void init();
    qint64 currentTime();

private slots:
    void setCurrentBookmark(bool first=true, qint32 position=-1);
    void _songFinishing();
    void stateHandler(Phonon::State is, Phonon::State);
    void _currentSourceChanged(Phonon::MediaSource newSrc);
    void _reachedBookmark(qint32);
    void _bufferStatus(int);
    void tick(qint64);
};

#endif // ZAUDIOMANAGER_H
