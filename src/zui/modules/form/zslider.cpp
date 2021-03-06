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

#include "zslider.h"

ZSlider::ZSlider(const ZConfig &el, QWidget *parent)
    : QSlider(parent),
      ZWidget(el,this)
{
    init();
}

void ZSlider::init(){
    parse(_config);

    zEvent->registerSignal(this, SIGNAL(valueChanged(int)));
    zEvent->registerSignal(this, SIGNAL(sliderPressed()));
    zEvent->registerSignal(this, SIGNAL(sliderReleased()));
    zEvent->registerSlot(this, SLOT(setValue(int)));
}

void ZSlider::parse(const ZConfig &el){
//! @direction - the lateral orientation of the slider
    if(el.attribute("direction","horizontal") == "vertical")
        setOrientation(Qt::Vertical);
    else
        setOrientation(Qt::Horizontal);

    if(el.hasAttribute("min"))
        setMinimum(el.attribute("min").toInt());

    if(el.hasAttribute("max"))
        setMaximum(el.attribute("max").toInt());
}
