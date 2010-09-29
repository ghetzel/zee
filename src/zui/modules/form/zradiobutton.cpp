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

#include "zradiobutton.h"

ZRadioButton::ZRadioButton(const ZConfig &el, QWidget *parent)
    : QRadioButton(parent),
      ZWidget(el,this)
{
    parse(_config);
}

void ZRadioButton::parse(const ZConfig &el){
    if(!el.text().isEmpty())
	setText(el.text());
    if(el.hasAttribute("value"))
	_value = QVariant(el.attribute("value"));
}
