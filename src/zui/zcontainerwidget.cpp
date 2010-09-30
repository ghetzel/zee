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

ZContainerWidget::ZContainerWidget(const ZConfig &el, QWidget *self)
    : ZWidget(el,self)
{
//    if(!widgetName().isEmpty())
//        ZuiUtils::registerContainerElement(widgetName());

    parse(_config);

}

void ZContainerWidget::parse(const ZConfig &el){
    if(!widget()->layout())
        widget()->setLayout(ZuiUtils::getLayout(
                el.attribute("layout", ZUI_DEFAULT_LAYOUT)));
}

Qt::Alignment ZContainerWidget::alignment(){
    if(widget()->layout())
        return widget()->layout()->alignment();
    return (Qt::AlignTop | Qt::AlignLeft);
}

void ZContainerWidget::setAlignment(QString alignment){
    if(widget()->layout())
        widget()->layout()->setAlignment(ZuiUtils::getAlignment(alignment));
}

void ZContainerWidget::setAlignment(Qt::Alignment alignment){
    if(widget()->layout())
        widget()->layout()->setAlignment(alignment);
}
