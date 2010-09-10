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

#include "zseekbar.h"

ZSeekbar::ZSeekbar(const ZConfig &el, QWidget *parent)
    : ZProgressBar(el,parent)
{
    init();
}

void ZSeekbar::init(){
    zEvent->registerSignal(this, SIGNAL(positionChanged(qint64)));
    zEvent->registerSlot(this, SLOT(addBookmark(qint64)));
    zEvent->registerSlot(this, SLOT(addBookmarks(QString)));
    zEvent->registerSlot(this, SLOT(reset()));
    parse(_config);
    reset();
}

void ZSeekbar::parse(const ZConfig&){

}

void ZSeekbar::reset(){
    _bookmarks.clear();
    ZProgressBar::reset();
}

void ZSeekbar::addBookmark(qint64 msec){
    z_log_debug("ZSeekbar: Adding bookmark at "+STR(msec));
    if(!_bookmarks.contains(msec)){
	_bookmarks.push_back(msec);
    }
    update();
}

void ZSeekbar::addBookmarks(QString marks){
    QStringList bmks = marks.split(QRegExp("\\D+"), QString::SkipEmptyParts);
    foreach(QString bm, bmks)
	addBookmark(bm.toULongLong());
}

void ZSeekbar::paintEvent(QPaintEvent *e){
    ZProgressBar::paintEvent(e);
    QPainter *p = new QPainter(this);
    QPen bookmarkPen;
    qint64 valRange = (maximum()-minimum());

    bookmarkPen.setColor(QColor(128,128,128,255));
    bookmarkPen.setWidth(3);

    p->setPen(bookmarkPen);

    foreach(qint64 bookmark, _bookmarks){
	int x = (CAST(qreal,bookmark)/valRange)*CAST(qreal,width());
	p->drawLine(x,0,x,height());
    }

    p->end();
}

void ZSeekbar::mousePressEvent(QMouseEvent *e){
    qreal valPerPx = (maximum()-minimum()) / width();
    setValue(valPerPx*e->x());
    emit positionChanged(value());
}

void ZSeekbar::mouseMoveEvent(QMouseEvent *e){
    qreal valPerPx = (maximum()-minimum()) / width();
    setValue(valPerPx*e->x());
}

void ZSeekbar::mouseReleaseEvent(QMouseEvent *e){
    qreal valPerPx = (maximum()-minimum()) / width();
    setValue(valPerPx*e->x());
    emit positionChanged(value());
}
