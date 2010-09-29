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

#include "zvideowidget.h"

ZVideoWidget::ZVideoWidget(const ZConfig &el, QWidget *parent)
    : QMPwidget(parent),
      ZWidget(el,this)
{
    init();
    QMPwidget::start();
}

void ZVideoWidget::init(){
    _dataObject = new QObject(this);
    _dataObject->setObjectName("data");

    connect(this, SIGNAL(mediaInfoUpdated(QMPwidget::MediaInfo)),
	    this, SLOT(_updateMediaInfo(QMPwidget::MediaInfo)));
    connect(this, SIGNAL(positionChanged(double)),
	    this, SLOT(_streamPositionChanged(double)));

    zEvent->registerSignal(this,SIGNAL(sourceChanged(QString)));
    zEvent->registerSignal(this, SIGNAL(positionChanged(qint64)));
    zEvent->registerSignal(this, SIGNAL(dataChanged()));
    zEvent->registerSlot(this, SLOT(play()));
    zEvent->registerSlot(this, SLOT(pause()));
    zEvent->registerSlot(this, SLOT(stop()));
    zEvent->registerSlot(this, SLOT(load(QString)));
    parse(_config);
}

void ZVideoWidget::parse(const ZConfig&){

}

void ZVideoWidget::_streamPositionChanged(double pos){
    emit positionChanged(pos*1000.0);
}

void ZVideoWidget::_updateMediaInfo(QMPwidget::MediaInfo info){
    if(info.ok){
	_dataObject->setProperty(ZVIDEO_AUDIO_BITRATE,	info.audioBitrate);
	_dataObject->setProperty(ZVIDEO_AUDIO_FORMAT,	info.audioFormat);
	_dataObject->setProperty(ZVIDEO_FPS,		info.framesPerSecond);
	_dataObject->setProperty(ZVIDEO_LENGTH,		info.length*1000.0);
	_dataObject->setProperty(ZVIDEO_AUDIO_CHANNELS,	info.numChannels);
	_dataObject->setProperty(ZVIDEO_SAMPLE_RATE,	info.sampleRate);
	_dataObject->setProperty(ZVIDEO_SEEKABLE,	info.seekable);
	//_dataObject->setProperty(ZVIDEO_TAGS,		info.tags);
	_dataObject->setProperty(ZVIDEO_BITRATE,	info.videoBitrate);
	_dataObject->setProperty(ZVIDEO_FORMAT,		info.videoFormat);
	_dataObject->setProperty(ZVIDEO_WIDTH,		info.size.width());
	_dataObject->setProperty(ZVIDEO_HEIGHT,		info.size.height());

	emit dataChanged();
    }
}
