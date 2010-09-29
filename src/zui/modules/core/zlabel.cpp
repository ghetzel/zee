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

#include "zlabel.h"

ZLabel::ZLabel(const ZConfig &el, QWidget *parent)
    : QLabel(parent),
      ZWidget(el,this)
{
    init();
}

ZLabel::ZLabel(QString value, const ZConfig &el, QWidget *parent)
    : QLabel(parent),
      ZWidget(el,this)
{
    setText(value);
    init();
}

void ZLabel::init(){
    parse(_config);

    zEvent->registerSlot(this,SLOT(setText(QString)));
    zEvent->registerSlot(this,SLOT(setEnabled(bool)));
    zEvent->registerSlot(this,SLOT(reset()));
}

void ZLabel::parse(const ZConfig &el){
    if(el.hasAttribute("value"))
	setText(el.attribute("value"));
    else
	setText(el.text());
    _initValue = text();

    if(el.hasAttribute("align"))
        setAlignment(ZuiUtils::getAlignment(el.attribute("align")));
}

void ZLabel::reset(){
    setText(_initValue);
}
