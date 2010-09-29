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

#include "zterminal.h"

ZTerminal::ZTerminal(const ZConfig &el, QWidget *parent)
    : QFrame(parent),
      ZWidget(el,this)
{
    init();
}

void ZTerminal::init(){
    zEvent->registerSignal(this, SIGNAL(finished()));

    setLayout(new QHBoxLayout);
    _terminal = new QTermWidget(1, this);

    QFont f = font();
    f.setFamily(ZTERM_DEFAULT_FONT_FAMILY);
    f.setFixedPitch(true);
    if(f.fixedPitch())
	_terminal->setTerminalFont(f);

    connect(_terminal, SIGNAL(finished()),
	    this, SIGNAL(finished()));

    parse(_config);

    layout()->setContentsMargins(0,0,0,0);
    layout()->addWidget(_terminal);
}

void ZTerminal::parse(const ZConfig&){
}
