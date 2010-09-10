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

#include "zhtmllistmodel.h"

ZHTMLListModel::ZHTMLListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    init();
}

ZHTMLListModel::ZHTMLListModel(QUrl base, QObject *parent)
    : QAbstractListModel(parent){
    setBaseUrl(base);
    init();
}

void ZHTMLListModel::init(){
    _matchRx.setPattern(ZHTML_LIST_DEFAULT_MATCH_RX);
    _excludeRx.setPattern(ZHTML_LIST_DEFAULT_EXCLD_RX);

    connect(&_net, SIGNAL(finished(QNetworkReply*)),
	    this, SLOT(_finished(QNetworkReply*)));
}

void ZHTMLListModel::setBaseUrl(QUrl base){
    _base = base;
    fetchBase();
}

void ZHTMLListModel::setMatchExpression(QRegExp rx){
    if(rx.isValid())
	_matchRx = rx;
}

void ZHTMLListModel::setMatchExpression(QString rx){
    QRegExp trx(rx);
    if(trx.isValid())
	_matchRx = trx;
}

void ZHTMLListModel::setExcludeExpression(QRegExp rx){
    if(rx.isValid())
	_excludeRx = rx;
}

void ZHTMLListModel::setExcludeExpression(QString rx){
    QRegExp erx(rx);
    if(erx.isValid())
	_excludeRx = erx;
}


int ZHTMLListModel::rowCount(const QModelIndex &parent) const{
    return _data.size();
}

QVariant ZHTMLListModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid())
	return QVariant();
    if(index.row() >= _data.size())
	return QVariant();

    switch(role){
    case Qt::DisplayRole:
	return _labels.value(_data.at(index.row()));
    case Qt::UserRole+1:
	return _data.at(index.row());
    default:
	return QVariant();
    }
}

QVariant ZHTMLListModel::headerData(int section,
				    Qt::Orientation orientation,
				    int role) const{
    return QVariant("__HEADER__");
}

void ZHTMLListModel::fetchBase(){
    if(_base.isValid()){
	_data.clear();
	_labels.clear();

	if(_cache.contains(_base.toString())){
	    _processReplyData(_cache.value(_base.toString()));
	}else{
	    QNetworkRequest req;
	    req.setUrl(_base);
	    downloadStarted();
	    _net.get(req);
	}
    }
}

void ZHTMLListModel::_finished(QNetworkReply *r){

    if(!r->error()){
	QString data(r->readAll());
	_cache.insert(_base.toString(), data);
	_processReplyData(data);
    }else{

    }

    r->deleteLater();
}

void ZHTMLListModel::_downloadProgress(qint64 in, qint64 total){
    qreal perc = (100.0 / total) * in;
    emit downloadProgress(perc);
}

void ZHTMLListModel::_processReplyData(QString data){
    int pos = 0;
    while( (pos = _matchRx.indexIn(data,pos)) != -1){
	QString d = _matchRx.cap(1);
	QUrl du;

	if(_excludeRx.isValid() && _excludeRx.indexIn(d) == -1){
	    du.setUrl(d);
	    if(d[0]=='/')
		du = _base.scheme()+"://"+_base.authority()+d;
	    else if(QUrl(d).isRelative())
		du = _base.toString()+d;

	    qDebug() << "URL: " << du.toString();
	    _data.append(du.toString());
	    _labels.insert(du.toString(), du.toString());
	}

	pos += _matchRx.matchedLength();
    }

    reset();
    downloadFinished();
}
