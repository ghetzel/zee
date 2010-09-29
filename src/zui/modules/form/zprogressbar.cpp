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

#include "zprogressbar.h"

ZProgressBar::ZProgressBar(const ZConfig &el, QWidget *parent)
    : QProgressBar(parent),
      ZWidget(el,this)
{
    parse(_config);
    init();
}

void ZProgressBar::parse(const ZConfig &el){
//! @min - the lowest value of the bar [default: 0]
    if(el.hasAttribute("min"))
        setMinimum(qRound(el.attribute("min","0").toFloat()));
//! @max - the highest value of the bar [default: 100]
    if(el.hasAttribute("max"))
        setMaximum(qRound(el.attribute("max","100").toFloat()));

//! @value - the starting value
    if(el.hasAttribute("value"))
        setValue(qRound(el.attribute("value","0").toFloat()));

//! @align (left|right|center) - alignment of the text indicator [default: left]
    if(el.hasAttribute("align"))
        setAlignment(ZuiUtils::getAlignment(el.attribute("align")));
}

void ZProgressBar::init(){
    zEvent->registerSignal(this,SIGNAL(valueChanged(int)));
    zEvent->registerSlot(this,SLOT(setEnabled(bool)));
    zEvent->registerSlot(this,SLOT(setMinimum(int)));
    zEvent->registerSlot(this,SLOT(setMaximum(int)));
    zEvent->registerSlot(this,SLOT(setRange(int,int)));
    zEvent->registerSlot(this,SLOT(setValue(int)));
    zEvent->registerSlot(this,SLOT(reset()));
}
