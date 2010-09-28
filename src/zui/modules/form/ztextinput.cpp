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

#include "ztextinput.h"

ZTextInput::ZTextInput(const ZConfig &el, QWidget *parent)
    : ZWidget<QLineEdit>(el,this,parent)
{
    _lastCursorPosition = 0;
    init();
}

void ZTextInput::init(){
    parse(_config);

    zEvent->registerSignal(this,SIGNAL(returnPressed()));
    zEvent->registerSignal(this,SIGNAL(textChanged(QString)));
    zEvent->registerSignal(this,SIGNAL(textEdited(QString)));
    zEvent->registerSignal(this,SIGNAL(selectionChanged()));
//    zEvent->registerSignal(this,SIGNAL(cursorPositionChanged(int,int)));

//    connect(this, SIGNAL(cursorPositionChanged(int,int)),
//	    this, SLOT(_cursorPosition(int,int)));

    zEvent->registerSlot(this,SLOT(setText(QString)));
    zEvent->registerSlot(this,SLOT(setDisabled(bool)));
    zEvent->registerSlot(this,SLOT(clear()));
    zEvent->registerSlot(this,SLOT(cut()));
    zEvent->registerSlot(this,SLOT(copy()));
    zEvent->registerSlot(this,SLOT(paste()));
    zEvent->registerSlot(this,SLOT(update()));
}

void ZTextInput::parse(const ZConfig &el){
//! @type - the type of text input field
    QString fieldtype = el.attribute("type");

//! @type#password - a password entry field
    if(fieldtype == "password"){
	setEchoMode(QLineEdit::Password);
    }

    if(!el.text().isEmpty()) //! default text
	setText(el.text());

//! @align - the text alignment of the field
    if(el.hasAttribute("align"))
        setAlignment(ZuiUtils::getAlignment(el.attribute("align")));

//! @disabled - whether the field is initially disabled
    if(ZuiUtils::attributeTrue(el.attribute("disabled"))) //! disabled
	setDisabled(true);

//! @maxlength - the maximum number of characters the field will accept
    if(el.hasAttribute("maxlength")) //! max character length
	setMaxLength(el.attribute("maxlength").toInt());

//! @mask - the text mask to format the input to
    if(el.hasAttribute("mask")) //! See QLineEdit#inputMask for mask examples
	setInputMask(el.attribute("mask"));
}


void ZTextInput::_cursorPosition(int o, int){
    _lastCursorPosition = o;
}

int ZTextInput::lastCursorPosition(){
   return _lastCursorPosition;
}
