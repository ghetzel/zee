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

#ifndef ZSLIDER_H
#define ZSLIDER_H

#define ZUI_SLIDER	"zui:slider"

#include <zutil.h>
#include <zui/zwidget.h>


class ZSlider : public QSlider, public ZWidget
{
    Q_OBJECT

public:
    ZSlider(const ZConfig &el, QWidget *parent);

private:
    void init();
    void parse(const ZConfig &el);
};

#endif // ZSLIDER_H
