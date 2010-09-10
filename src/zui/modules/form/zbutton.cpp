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

#include "zbutton.h"

using namespace std;

ZButton::ZButton(const ZConfig &el, QWidget *parent)
    : ZWidget<QPushButton>(el,this,parent){
    parse(_config);
    zEvent->registerSignal(this,SIGNAL(clicked()));
}

ZButton::ZButton(const QString &text, const ZConfig &el, QWidget *parent)
    : ZWidget<QPushButton>(el,this,parent)
{
    parse(_config);
    setText(text);
    zEvent->registerSignal(this,SIGNAL(clicked()));
}

ZButton::ZButton(const QString &icon, const QString &text, const ZConfig &el, QWidget *parent)
    : ZWidget<QPushButton>(el,this,parent)
{
    setText(text);
    zSetIcon(icon);
    parse(_config);
    zEvent->registerSignal(this,SIGNAL(clicked()));
}

void ZButton::zSetIcon(QString name){
    setIcon(ZuiUtils::getIcon(name));
}

void ZButton::parse(const ZConfig &el){
    if(!el.text().isEmpty())
	setText(el.text());
    else if(!el.attribute("value","").isEmpty())
	setText(el.attribute("value"));

    if(el.hasAttribute("icon"))
	zSetIcon(el.attribute("icon"));
}
