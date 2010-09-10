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
    : ZWidget<VideoPlayer>(el,this,parent)
{
    init();
}

void ZVideoWidget::init(){
    zEvent->registerSignal(this,SIGNAL(sourceChanged(QString)));
    zEvent->registerSlot(this, SLOT(play()));
    zEvent->registerSlot(this, SLOT(pause()));
    zEvent->registerSlot(this, SLOT(stop()));
    zEvent->registerSlot(this, SLOT(load(QString)));
    parse(_config);
}

void ZVideoWidget::parse(const ZConfig&){

}

void ZVideoWidget::load(QString location){
    _source = new MediaSource(location);
    VideoPlayer::load(*_source);
    emit sourceChanged(_source->fileName());
    z_log_debug("ZVideoWidget: "+STR(totalTime()));
}
