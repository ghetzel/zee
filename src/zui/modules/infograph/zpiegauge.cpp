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
}

void ZPieGauge::paintEvent(QPaintEvent *event){
    ZGenericDial::paintEvent(event);
    QPainter *p = new QPainter(this);

    if(p->isActive()){
	p->setRenderHint(QPainter::Antialiasing);

	//qreal cX = (width()/2.0)-(ZGENERIC_DIAL_X_PAD);
	//qreal cY = (height()/2.0)-(ZGENERIC_DIAL_Y_PAD);
	qreal vTheta = (ZGENERIC_DIAL_ANNULAR_OFFSET+offset()+
		       (range()/(maximum()-minimum()))/value()); // brainfail

	p->drawPie(rect(), (ZGENERIC_DIAL_ANNULAR_OFFSET+offset())*16,vTheta*16);
    }
}
