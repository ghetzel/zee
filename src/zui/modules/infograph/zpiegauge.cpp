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

#include "zpiegauge.h"

ZPieGauge::ZPieGauge(const ZConfig &el, QWidget *parent)
    : ZGenericDial(el,parent)
{
    _ringWidth = 50;
}

void ZPieGauge::paintEvent(QPaintEvent *event){
    ZGenericDial::paintEvent(event);
    QPainter *p = new QPainter(this);
    QPainterPath ring;
    qreal curAngle = (360.0/(_maxValue-_minValue))*_value;

    qreal c0,s0,c1,s1;
    qreal xRadius = (width()-(ZGENERIC_DIAL_X_PAD*2.0))/2.0;
    qreal yRadius = (height()-(ZGENERIC_DIAL_Y_PAD*2.0))/2.0;
    qreal innerXRadius = xRadius-_ringWidth;
    qreal innerYRadius = yRadius-_ringWidth;

    p->setRenderHint(QPainter::Antialiasing);

    QPen pp(Qt::red);
    QBrush pb(Qt::red);
    pp.setWidth(3);

    p->setPen(pp);
    //! \bug  The math below still causes fill artifacts
    //p->setBrush(pb);



    s0 = qSin(RADIANS(ZGENERIC_DIAL_ANNULAR_OFFSET+_offset));
    c0 = qCos(RADIANS(ZGENERIC_DIAL_ANNULAR_OFFSET+_offset));
    s1 = qSin(RADIANS(curAngle+ZGENERIC_DIAL_ANNULAR_OFFSET+_offset));
    c1 = qCos(RADIANS(curAngle+ZGENERIC_DIAL_ANNULAR_OFFSET+_offset));

//  move to start position    
    ring.moveTo(QPointF( innerXRadius*c0+xRadius+ZGENERIC_DIAL_X_PAD,
                         innerYRadius*s0+yRadius+ZGENERIC_DIAL_Y_PAD));

//  draw outer arc
    ring.arcTo(QRectF(ZGENERIC_DIAL_X_PAD,
                      ZGENERIC_DIAL_Y_PAD,
                      xRadius*2.0,
                      yRadius*2.0),
               -1*(ZGENERIC_DIAL_ANNULAR_OFFSET+_offset),
               -1*curAngle);
    
//  move to the end of the new arc
    ring.moveTo(QPointF( xRadius*c1+xRadius+ZGENERIC_DIAL_X_PAD,
                         yRadius*s1+yRadius+ZGENERIC_DIAL_Y_PAD));

//  draw the line marking the final value
    ring.lineTo(QPointF( innerXRadius*c1+xRadius+ZGENERIC_DIAL_X_PAD,
                         innerYRadius*s1+yRadius+ZGENERIC_DIAL_Y_PAD));

//  move back to start position
    ring.moveTo(QPointF( innerXRadius*c0+xRadius+ZGENERIC_DIAL_X_PAD,
                         innerYRadius*s0+yRadius+ZGENERIC_DIAL_Y_PAD));

//  draw inner arc
    ring.arcTo(QRectF(ZGENERIC_DIAL_X_PAD+_ringWidth,
                      ZGENERIC_DIAL_Y_PAD+_ringWidth,
                      innerXRadius*2.0,
                      innerYRadius*2.0),
               -1*(ZGENERIC_DIAL_ANNULAR_OFFSET+_offset),
               -1*curAngle);

    p->drawPath(ring);
    p->end();
}
