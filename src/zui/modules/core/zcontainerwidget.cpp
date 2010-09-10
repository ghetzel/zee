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

#include "zcontainerwidget.h"

ZContainerWidget::ZContainerWidget(const ZConfig &el, QWidget *parent)
    : ZWidget<QFrame>(el,this,parent)
{
    parse(_config);
    zEvent->registerSlot(this, SLOT(hide()));
    zEvent->registerSlot(this, SLOT(show()));
    zEvent->registerSlot(this, SLOT(toggle()));
}

void ZContainerWidget::parse(const ZConfig &el){
  setLayout(ZuiUtils::getLayout(
	  el.attribute("layout", ZUI_DEFAULT_LAYOUT)));
  if(el.hasAttribute("align"))
      setProperty("align",el.attribute("align"));
}

void ZContainerWidget::toggle(){
    if(isHidden())
	show();
    else
	hide();
}

Qt::Alignment ZContainerWidget::alignment(){
    if(layout())
	return layout()->alignment();
    return (Qt::AlignTop | Qt::AlignLeft);
}

void ZContainerWidget::setAlignment(Qt::Alignment alignment){
    if(layout())
	layout()->setAlignment(alignment);
}
