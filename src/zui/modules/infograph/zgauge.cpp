#include "zgauge.h"

ZGauge::ZGauge(const ZConfig &el, QWidget *parent)
    : ZGenericDial(el,parent)
{
    _indicator = NULL;
    parse(_config);
}

void ZGauge::parse(const ZConfig &el){
    if(el.hasAttribute("indicator")){
        _indicator = new QSvgRenderer(el.attribute("indicator"), this);
        connect(_indicator, SIGNAL(repaintNeeded()),
                this, SLOT(repaint()));
    }
}

void ZGauge::paintEvent(QPaintEvent *event){
    ZGenericDial::paintEvent(event);

    QPainter *p = new QPainter(this);
    qreal cX = (width()/2.0)-(ZGENERIC_DIAL_X_PAD);
    qreal cY = (height()/2.0)-(ZGENERIC_DIAL_Y_PAD);

    if(_indicator){
        _indicator->render(p, QRectF(
                    QPointF(cX-(width()/2.0),
                            cY-(height()/2.0)),
                    QSizeF(width(), height()))
                );
    }
}
