#include "zseekbar.h"

ZSeekbar::ZSeekbar(const ZConfig &el, QWidget *parent)
    : ZProgressBar(el,parent)
{
    init();
}

void ZSeekbar::init(){
    zEvent->registerSignal(this, SIGNAL(positionChanged(qint64)));
    parse(_config);
}

void ZSeekbar::parse(const ZConfig&){

}

void ZSeekbar::paintEvent(QPaintEvent *e){
    ZProgressBar::paintEvent(e);
    QPainter *p = new QPainter(this);

    p->setPen(QColor(128,128,128,255));
    p->drawEllipse(width()/2,0,height(),height());

    p->end();
}

void ZSeekbar::mousePressEvent(QMouseEvent *e){
    qreal pxPerVal = (maximum()-minimum()) / width();
    setValue(pxPerVal*e->x());
    emit positionChanged(value());
}

void ZSeekbar::mouseMoveEvent(QMouseEvent *e){
    qreal pxPerVal = (maximum()-minimum()) / width();
    setValue(pxPerVal*e->x());
}

void ZSeekbar::mouseReleaseEvent(QMouseEvent *e){
    qreal pxPerVal = (maximum()-minimum()) / width();
    setValue(pxPerVal*e->x());
    emit positionChanged(value());
}
