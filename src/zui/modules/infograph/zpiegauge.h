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

#ifndef ZPIEGAUGE_H
#define ZPIEGAUGE_H

#define ZPIE_DEFAULT_RING_WIDTH         10

#define ZUI_PIEGAUGE			"zui:piegauge"

#include <zgenericdial.h>

class ZPieGauge : public ZGenericDial
{
    Q_OBJECT
    Q_PROPERTY(int ringWidth READ ringWidth WRITE setRingWidth)
public:
    ZPieGauge(const ZConfig &el, QWidget *parent=0);
    int ringWidth();
    void setRingWidth(int w);
    void resizeEvent(QResizeEvent *e);

private:
    void paintEvent(QPaintEvent *event);

private:
    int _ringWidth;
};

#endif // ZPIEGAUGE_H
