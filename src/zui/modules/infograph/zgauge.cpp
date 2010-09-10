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
