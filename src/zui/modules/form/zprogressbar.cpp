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
    : ZWidget<QProgressBar>(el,this,parent)
{
    parse(_config);
    init();
}

void ZProgressBar::parse(const ZConfig &el){
    if(el.hasAttribute("min"))
	setMinimum(el.attribute("min","0").toInt());
    if(el.hasAttribute("max"))
	setMaximum(el.attribute("max","0").toInt());
    if(el.hasAttribute("value"))
	setValue(el.attribute("value","0").toInt());
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
