#include "zaudiomanager.h"

ZAudioManager::ZAudioManager(const ZConfig &el, QObject *parent)
    : QAbstractListModel(parent),
      ZConfigurable(el,this)
{
    init();
}

void ZAudioManager::parse(const ZConfig &el){
    setCrossfade(param("crossfade").toInt());
}

void ZAudioManager::init(){
    _state = Loading;
    _currentQueueSource = 0;
    _output = new Phonon::AudioOutput(Phonon::MusicCategory, this);
    _mediaObject = new Phonon::MediaObject(this);
    _resolver = new Phonon::MediaObject(this);

    parse(_config);

    _mediaObject->setTickInterval(500);
    Phonon::createPath(_mediaObject, _output);

    connect(_mediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)),
	    this, SLOT(stateHandler(Phonon::State,Phonon::State)));
    connect(_mediaObject, SIGNAL(currentSourceChanged(Phonon::MediaSource)),
	    this, SLOT(_currentSourceChanged(Phonon::MediaSource)));
    connect(_mediaObject, SIGNAL(tick(qint64)),
	    this, SLOT(tick(qint64)));
    connect(_mediaObject, SIGNAL(aboutToFinish()),
	    this, SLOT(_songFinishing()));
    connect(_mediaObject, SIGNAL(prefinishMarkReached(qint32)),
	    this, SLOT(_reachedBookmark(qint32)));
    connect(_mediaObject, SIGNAL(totalTimeChanged(qint64)),
	    this, SLOT(setCurrentBookmark()));

    zEvent->registerSignal(this,SIGNAL(buffering()));
    zEvent->registerSignal(this,SIGNAL(playing()));
    zEvent->registerSignal(this,SIGNAL(paused()));
    zEvent->registerSignal(this,SIGNAL(stopped()));
    zEvent->registerSignal(this,SIGNAL(loading()));
    zEvent->registerSignal(this,SIGNAL(positionChanged(double)));
    zEvent->registerSignal(this,SIGNAL(timeChanged(qint64)));
    zEvent->registerSignal(this,SIGNAL(durationChanged(qint64)));
    zEvent->registerSignal(this,SIGNAL(sourceChanged(QString)));
    zEvent->registerSignal(this,SIGNAL(queueChanged()));
    zEvent->registerSignal(this,SIGNAL(queueCleared()));
    zEvent->registerSignal(this,SIGNAL(queuedSongChanged(int)));
    zEvent->registerSignal(this, SIGNAL(reachedBookmark(qint64)));
    zEvent->registerSlot(this, SLOT(play()));
    zEvent->registerSlot(this, SLOT(pause()));
    zEvent->registerSlot(this, SLOT(stop()));
    zEvent->registerSlot(this, SLOT(next()));
    zEvent->registerSlot(this, SLOT(togglePlay()));
    zEvent->registerSlot(this, SLOT(playSource(QString)));
    zEvent->registerSlot(this, SLOT(playSource(QUrl)));
    zEvent->registerSlot(this, SLOT(setSource(QString)));
    zEvent->registerSlot(this, SLOT(setSource(QUrl)));
    zEvent->registerSlot(this, SLOT(changeTo(QString)));
    zEvent->registerSlot(this, SLOT(changeTo(QUrl)));
    zEvent->registerSlot(this, SLOT(enqueue(QStringList)));
    zEvent->registerSlot(this, SLOT(enqueue(QString)));
    zEvent->registerSlot(this, SLOT(setQueue(QStringList)));
    zEvent->registerSlot(this, SLOT(clearQueue()));
    zEvent->registerSlot(this, SLOT(clearBookmarks()));
    zEvent->registerSlot(this, SLOT(clear()));
    zEvent->registerSlot(this, SLOT(setCrossfade(int)));
    zEvent->registerSlot(this, SLOT(setGapless()));
    zEvent->registerSlot(this, SLOT(setBookmark(qint64)));
}

void ZAudioManager::stateHandler(Phonon::State is, Phonon::State){
    switch(is){
    case Phonon::ErrorState:
	_state = Error;
	if(_mediaObject->errorType() == Phonon::FatalError)
	    z_log_crit("ZAudioManager: "+_mediaObject->errorString());
	else
	    z_log_error("ZAudioManager: "+_mediaObject->errorString());
	break;
    case Phonon::PlayingState:
	_state = Playing;
	emit playing();
	break;
    case Phonon::PausedState:
	_state = Paused;
	emit paused();
	break;
    case Phonon::StoppedState:
	_state = Stopped;
	emit stopped();
	break;
    case Phonon::BufferingState:
	_state = Buffering;
	emit buffering();
	break;
    case Phonon::LoadingState:
	_state = Loading;
	emit loading();
	break;
    default:
	return;
    }

    emit stateChanged(_state);
}

void ZAudioManager::_currentSourceChanged(Phonon::MediaSource newSrc){
    emit sourceChanged(newSrc.url().toString());
    emit queuedSongChanged(_currentQueueSource);
}

void ZAudioManager::tick(qint64){
    switch(_mediaObject->state()){
    case Phonon::PlayingState:
	qint64 ct, tt;
	ct = _mediaObject->currentTime();
	tt = _mediaObject->totalTime();
	emit positionChanged((100.0/tt)*ct);
	emit timeChanged(ct);
	emit durationChanged(tt);
	break;
    }
}

void ZAudioManager::play(){
    if(_mediaObject){
	switch(_mediaObject->state()){
	case Phonon::BufferingState:
	case Phonon::ErrorState:
	    z_log_error("ZAudioManager: "+_mediaObject->errorString());
	    return;
	case Phonon::LoadingState:  //
	case Phonon::PlayingState:  // will restart current song if called again
	case Phonon::StoppedState:  // we're stopped, clear to go
	    if(!_sourceQueue.isEmpty()){
		QString cqs = currentQueueSource();
		if(!cqs.isEmpty()){ // if in range...
		    _mediaObject->setCurrentSource(cqs);
		    emit sourceChanged(_mediaObject->currentSource().url().toString());
		    emit queuedSongChanged(_currentQueueSource);
		}else{
		    z_log_debug("ZAudioManager: Cannot play source "+STR(_currentQueueSource)+", does not exist");
		}
	    }else{
		z_log_debug("ZAudioManager: Cannot play, nothing in queue");
	    }
	default:
	    _mediaObject->play();
	}
    }
}

void ZAudioManager::pause(){
    if(_mediaObject)
	_mediaObject->pause();
}

void ZAudioManager::togglePlay(){
    if(_state == Playing)
	pause();
    else
	play();
}

void ZAudioManager::stop(){
    if(_mediaObject){
	_mediaObject->queue().clear();
	_mediaObject->stop();
    }
}

void ZAudioManager::next(){
    stop();
//  if the next source exists, increment the counter and play
    if((_currentQueueSource+1) < _sourceQueue.size()){
	++_currentQueueSource;
    }else{
	z_log_debug("ZAudioManager: Cannot go next, nothing next");
	return;
    }
    play();
}

void ZAudioManager::setSource(QString location){
    setSource(QUrl::fromUserInput(location));
}

void ZAudioManager::setSource(QUrl location){
    if(_mediaObject){
//        if(!_sourceQueue.contains(location.toString()))
//            _sourceQueue.clear();
        _mediaObject->setCurrentSource(Phonon::MediaSource(location.toString()));
	emit sourceChanged(_mediaObject->currentSource().url().toString());
    }
}

void ZAudioManager::playSource(QString location){
    playSource(QUrl::fromUserInput(location));
}

void ZAudioManager::playSource(QUrl location){
    setSource(location.toString());
    play();
}

void ZAudioManager::changeTo(QString location){
    changeTo(QUrl::fromUserInput(location));
}

void ZAudioManager::changeTo(QUrl location){
    if(!_sourceQueue.isEmpty()){
	if(_sourceQueue.contains(location.toString())){
	    _currentQueueSource = _sourceQueue.indexOf(location.toString());
	    emit queuedSongChanged(_currentQueueSource);
	}
    }
    play();
}

void ZAudioManager::enqueue(QStringList locations){
    foreach(QString loc, locations)
	enqueue(loc);
}

void ZAudioManager::enqueue(QString location){
    enqueue(QUrl::fromUserInput(location));
}

void ZAudioManager::enqueue(QUrl location){
    z_log_debug("ZAudioManager: NQU: "+location.toString());

    if(location.scheme() == "file")
        if(!QFile::exists(location.toLocalFile()))
            return;

    QFileInfo f(location.path());
    if(f.isDir()){
        QDir qed(location.path());
        foreach(QFileInfo i, qed.entryInfoList(QDir::Readable|QDir::Files))
            enqueue(i.absoluteFilePath());
    }else{
        bool wasEmpty = _sourceQueue.isEmpty();
        z_log("ZAudioManager: Enqueueing "+location.toString());
         beginInsertRows(QModelIndex(),
                         _sourceQueue.size()-1,
                         _sourceQueue.size()-1);
         _sourceQueue.push_back(location.toString());
        endInsertRows();
        emit queueChanged();

        if(wasEmpty)
            setSource(_sourceQueue.first());
    }
}

void ZAudioManager::setQueue(QStringList locations){
    clearQueue();
    foreach(QString l, locations)
	enqueue(l);
    emit queueChanged();
}

void ZAudioManager::clearQueue(){
    if(_mediaObject){
	stop();
	beginRemoveRows(QModelIndex(),
			0,
			_sourceQueue.size()-1);
	_sourceQueue.clear();
	_currentQueueSource = 0;
	endRemoveRows();
	z_log("ZAudioManager: Clear Queue");
	emit queueCleared();
    }
}

void ZAudioManager::clearBookmarks(){
    _bookmarks.clear();
    if(_mediaObject)
	_mediaObject->setPrefinishMark(0);
}

void ZAudioManager::clear(){
    clearQueue();
    clearBookmarks();
    if(_mediaObject)
        _mediaObject->clear();
}

void ZAudioManager::setCrossfade(int ms){
    if(_mediaObject)
	_mediaObject->setTransitionTime(-1*abs(ms));
}

void ZAudioManager::setGapless(){
    setCrossfade(0);
}

void ZAudioManager::setBookmark(qint64 position){
    if(_currentQueueSource < _sourceQueue.size())
	setBookmark(_sourceQueue.at(_currentQueueSource), position);
}

void ZAudioManager::setBookmark(QString file, qint64 position){
    z_log_debug("ZAudioManager: Setting bookmark at "+STR(position)+" on "+file);
    _bookmarks.insertMulti(file, position);
    setCurrentBookmark();
}

void ZAudioManager::_reachedBookmark(qint32 position){
    if(_mediaObject){
	position = _mediaObject->totalTime()-position;
	qint64 findMark = -1;
//	because the mark will likely be fired a little before or after the
//	exact point of the bookmark, we need to do a heuristic search to find
//	the most probable bookmark this is referring to
	foreach(qint64 m, _bookmarks.values(currentQueueSource())){
	    if(position >= (m-ZAUDIO_BM_ERROR) &&
	       position <= (m+ZAUDIO_BM_ERROR))
		findMark = m;
	}

	if(findMark >= 0){
	    z_log_debug("ZAudioManager: Reached mark at "+STR(findMark));
	    emit reachedBookmark(CAST(qint64,findMark));
    //	if the current source index exists
	    if(_currentQueueSource < _sourceQueue.size()){
		setCurrentBookmark(false, findMark);
	    }
	}
    }
}

void ZAudioManager::setCurrentBookmark(bool first, qint32 position){
    if(_mediaObject){
//	pull the list of all bookmarks
	QList<qint64> bm = _bookmarks.values(currentQueueSource());
	qSort(bm); // sort them (will do this better...i promise)
	if(!bm.isEmpty()){
	    if(first){
		_mediaObject->setPrefinishMark(_mediaObject->totalTime()-bm.first());
//		z_log_debug("ZAudioManager: Setting first mark at "+STR(bm.first())+" vf: "+STR(_mediaObject->prefinishMark())+", len="+STR(_mediaObject->totalTime()));
	    }else{
		if(position >= 0){
		    int nidx = bm.indexOf(position)+1; // get the next index
		    if(nidx < bm.size()){ // if that index exists
//			z_log_debug("ZAudioManager: Prepping next mark at ("+STR(nidx)+") "+STR(bm.at(nidx)));
			_mediaObject->setPrefinishMark(_mediaObject->totalTime()-bm.at(nidx)); // set the next mark
		    }
		}
	    }
	}
    }
}

ZAudioManager::ZAudioState ZAudioManager::state(){
    return _state;
}

void ZAudioManager::setAdaptor(ZAudioAdaptor *adaptor){
    _adaptor = adaptor;
}

QStringList ZAudioManager::queue(){
    return _sourceQueue;
}

QString ZAudioManager::currentQueueSource(){
    if(_currentQueueSource < _sourceQueue.size())
	return _sourceQueue.at(_currentQueueSource);
    return QString();
}

qint64 ZAudioManager::currentTime(){
    if(_mediaObject)
	return _mediaObject->currentTime();
    return -1;
}

int ZAudioManager::rowCount(const QModelIndex &parent) const{
    return _sourceQueue.size();
}

QVariant ZAudioManager::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
	return QVariant();
    if(index.row() >= _sourceQueue.size())
	return QVariant();
    switch(role){
    case Qt::DisplayRole:
        return QVariant(_sourceQueue.at(index.row()));
    case Qt::UserRole+1:
        return QVariant(_sourceQueue.at(index.row()));
    default:
	return QVariant();
    }
}

QVariant ZAudioManager::headerData(int section, Qt::Orientation orientation,
				   int role) const
{
    if(role != Qt::DisplayRole)
	return QVariant();
    if(orientation == Qt::Horizontal)
	return QString("Column %1").arg(section);
    else
	return QString("Row %1").arg(section);
}

//bool ZAudioManager::insertRows(int row, int count, const QModelIndex &parent){
//    if(!_mediaObject)
//        return false;
//    //beginInsertRows(QModelIndex(),_mediaObject->queue().count());
//
//    //endInsertRows();
//    return true;
//}


void ZAudioManager::_songFinishing(){
//  if there is a source after this, enqueue it
    z_log_debug("ZAudioManager: Current song finishing");
    if((_currentQueueSource+1) < _sourceQueue.size()){
	_mediaObject->enqueue(_sourceQueue.at(++_currentQueueSource));
	z_log_debug("ZAudioManager: Next in line: " + STR(_currentQueueSource));
    }else{
	z_log_debug("ZAudioManager: Cannot queue next, nothing left in queue");
    }
}


ZAudioManager::~ZAudioManager(){
    if(_mediaObject)
	_mediaObject->deleteLater();
}
