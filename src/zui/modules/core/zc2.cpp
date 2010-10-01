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

#include "zcontainer.h"

ZContainer::ZContainer(const ZConfig &el, QWidget *parent)
    : QFrame(parent),
      ZContainerWidget(el,this)
{
    parse(_config);
    zEvent->registerSlot(this, SLOT(hide()));
    zEvent->registerSlot(this, SLOT(show()));
    zEvent->registerSlot(this, SLOT(toggle()));
}

void ZContainer::parse(const ZConfig &el){}

void ZContainer::toggle(){
    if(isHidden())
        show();
    else
        hide();
}

Qt::Alignment ZContainer::alignment(){
    if(layout())
        return layout()->alignment();
    return (Qt::AlignTop | Qt::AlignLeft);
}

void ZContainer::setAlignment(Qt::Alignment alignment){
    if(layout())
        layout()->setAlignment(alignment);
}
