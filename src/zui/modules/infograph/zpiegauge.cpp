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
    _ringWidth = 10;
}

void ZPieGauge::paintEvent(QPaintEvent *event){
    ZGenericDial::paintEvent(event);
    QPainter *p = new QPainter(this);
    QStyleOption style;
    QPainterPath ring;

    if(_value > 0){
        qreal curAngle = (360.0/(_maxValue-_minValue))*_value;

        qreal c0,s0,c1,s1;
        qreal xRadius = (width()-(ZGENERIC_DIAL_X_PAD*2.0))/2.0;
        qreal yRadius = (height()-(ZGENERIC_DIAL_Y_PAD*2.0))/2.0;
        qreal innerXRadius = xRadius-_ringWidth;
        qreal innerYRadius = yRadius-_ringWidth;

        style.initFrom(this);
        p->setRenderHint(QPainter::Antialiasing);


        QPen pp(style.palette.windowText().color());
        pp.setWidth(3);

        p->setPen(pp);
        p->setBrush(style.palette.alternateBase());


    //    z_log_debug("ZPieGauge: PALETTE BG "+style.palette.background().color().name());
    //    z_log_debug("ZPieGauge: PALETTE BASE "+style.palette.base().color().name());
    //    z_log_debug("ZPieGauge: PALETTE BRIGHT "+style.palette.brightText().color().name());
    //    z_log_debug("ZPieGauge: PALETTE BTN "+style.palette.button().color().name());
    //    z_log_debug("ZPieGauge: PALETTE BTNTXT "+style.palette.buttonText().color().name());
    //    z_log_debug("ZPieGauge: PALETTE DARK "+style.palette.dark().color().name());
    //    z_log_debug("ZPieGauge: PALETTE FG "+style.palette.foreground().color().name());
    //    z_log_debug("ZPieGauge: PALETTE HLITE"+style.palette.highlight().color().name());
    //    z_log_debug("ZPieGauge: PALETTE HLITETXT "+style.palette.highlightedText().color().name());
    //    z_log_debug("ZPieGauge: PALETTE LIGHT "+style.palette.light().color().name());
    //    z_log_debug("ZPieGauge: PALETTE LINK "+style.palette.link().color().name());
    //    z_log_debug("ZPieGauge: PALETTE VLINK "+style.palette.linkVisited().color().name());
    //    z_log_debug("ZPieGauge: PALETTE MID "+style.palette.mid().color().name());
    //    z_log_debug("ZPieGauge: PALETTE MIDLIGHT "+style.palette.midlight().color().name());
    //    z_log_debug("ZPieGauge: PALETTE SHDW "+style.palette.shadow().color().name());
    //    z_log_debug("ZPieGauge: PALETTE TEXT "+style.palette.text().color().name());
    //    z_log_debug("ZPieGauge: PALETTE TTBASE "+style.palette.toolTipBase().color().name());
    //    z_log_debug("ZPieGauge: PALETTE TTTXT "+style.palette.toolTipText().color().name());
    //    z_log_debug("ZPieGauge: PALETTE WIN "+style.palette.window().color().name());
    //    z_log_debug("ZPieGauge: PALETTE WINTXT"+style.palette.windowText().color().name());


    //  calculate components for starting outer point
        s0 = qSin(RADIANS(ZGENERIC_DIAL_ANNULAR_OFFSET+_offset));
        c0 = qCos(RADIANS(ZGENERIC_DIAL_ANNULAR_OFFSET+_offset));
    //  calculate components for ending outer point
        s1 = qSin(RADIANS(curAngle+ZGENERIC_DIAL_ANNULAR_OFFSET+_offset));
        c1 = qCos(RADIANS(curAngle+ZGENERIC_DIAL_ANNULAR_OFFSET+_offset));


    //  move to start position (outer)
        ring.moveTo(QPointF(xRadius*c0+xRadius+ZGENERIC_DIAL_X_PAD,
                             yRadius*s0+yRadius+ZGENERIC_DIAL_Y_PAD));


    //  draw start line (outer-to-inner)
        ring.lineTo(QPointF(innerXRadius*c0+xRadius+ZGENERIC_DIAL_X_PAD,
                                 innerYRadius*s0+yRadius+ZGENERIC_DIAL_Y_PAD));

    //  draw inner arc
        ring.arcTo(QRectF(ZGENERIC_DIAL_X_PAD+_ringWidth,
                          ZGENERIC_DIAL_Y_PAD+_ringWidth,
                          innerXRadius*2.0,
                          innerYRadius*2.0),
                   -1*(ZGENERIC_DIAL_ANNULAR_OFFSET+_offset),
                   -1*curAngle);

    //  draw end line (inner-to-outer)
        ring.lineTo(QPointF(xRadius*c1+xRadius+ZGENERIC_DIAL_X_PAD,
                                 yRadius*s1+yRadius+ZGENERIC_DIAL_Y_PAD));

    //  draw outer arc (from end line back to start point
        ring.arcTo(QRectF(ZGENERIC_DIAL_X_PAD,
                          ZGENERIC_DIAL_Y_PAD,
                          xRadius*2.0,
                          yRadius*2.0),
                   -1*(ZGENERIC_DIAL_ANNULAR_OFFSET+_offset+curAngle),
                   curAngle);

    //  close path
        ring.closeSubpath();

        p->drawPath(ring);
    }

    p->end();
}
