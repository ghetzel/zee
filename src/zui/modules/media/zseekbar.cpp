#include "zseekbar.h"

ZSeekbar::ZSeekbar(const ZConfig &el, QWidget *parent)
    : ZProgressBar(el,parent)
{
    init();
}

void ZSeekbar::init(){
    zEvent->registerSignal(this, SIGNAL(positionChanged(qint64)));
    zEvent->registerSlot(this, SLOT(addBookmark(qint64)));
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
    if(!_bookmarks.contains(msec)){
        _bookmarks.push_back(msec);
        z_log_debug("ZSeekbar: Adding bookmark at "+STR(msec));
    }
    update();
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
