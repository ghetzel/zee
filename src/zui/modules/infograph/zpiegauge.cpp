#include "zpiegauge.h"

ZPieGauge::ZPieGauge(const ZConfig &el, QWidget *parent)
    : ZGenericDial(el,parent)
{
}

void ZPieGauge::paintEvent(QPaintEvent *event){
    ZGenericDial::paintEvent(event);
    QPainter *p = new QPainter(this);

    if(p->isActive()){
        p->setRenderHint(QPainter::Antialiasing);

        qreal cX = (width()/2.0)-(ZGENERIC_DIAL_X_PAD);
        qreal cY = (height()/2.0)-(ZGENERIC_DIAL_Y_PAD);
        qreal vTheta = (ZGENERIC_DIAL_ANNULAR_OFFSET+offset()+
                       (range()/(maximum()-minimum()))/value()); // brainfail

        p->drawPie(rect(), (ZGENERIC_DIAL_ANNULAR_OFFSET+offset())*16,vTheta*16);
    }
}
