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

#include "ztogglebutton.h"

ZToggleButton::ZToggleButton(const ZConfig &el, QWidget *parent)
    : ZButton(el, parent)
{
    init();
}

ZToggleButton::ZToggleButton(const QString &text, const ZConfig &el, QWidget *parent)
    : ZButton(text, el, parent)
{
    init();
}

ZToggleButton::ZToggleButton(const QString &icon, const QString &text, const ZConfig &el, QWidget *parent)
    : ZButton(icon, text, el, parent)
{
    init();
}

void ZToggleButton::init(){
    setCheckable(true);
    parse(_config);

    connect(this, SIGNAL(toggled(bool)), this, SLOT(_toggled(bool)));

    zEvent->registerSignal(this, SIGNAL(checked()));
    zEvent->registerSignal(this, SIGNAL(unchecked()));
    zEvent->registerSignal(this, SIGNAL(toggled(bool)));
    zEvent->registerSlot(this, SLOT(check()));
    zEvent->registerSlot(this, SLOT(uncheck()));
    zEvent->registerSlot(this, SLOT(toggle()));
}


void ZToggleButton::parse(const ZConfig &el){
    if(el.hasAttribute("value2"))
	_otherLabel = el.attribute("value2");
}

void ZToggleButton::check(){
    emit toggled(true);
}

void ZToggleButton::uncheck(){
    emit toggled(false);
}

void ZToggleButton::toggle(){
    if(isChecked())
	uncheck();
    else
	check();
}

void ZToggleButton::toggleLabel(){
    QString t = text();
    setText(_otherLabel);
    _otherLabel = t;
}

void ZToggleButton::_toggled(bool on){
    if(on){
	emit checked();
    }else{
	emit unchecked();
    }
    toggleLabel();
}
