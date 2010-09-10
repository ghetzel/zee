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

#include "zexecutor.h"

ZExecutor::ZExecutor(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    parse(_config);
    zEvent->registerSignal(this, SIGNAL(executed(QString)));
    zEvent->registerSignal(this, SIGNAL(commandChanged(QString)));
    zEvent->registerSignal(this, SIGNAL(commandChanged(QString,QString)));
    zEvent->registerSlot(this, SLOT(exec()));
    zEvent->registerSlot(this, SLOT(setCommand(QString)));
}

ZExecutor::~ZExecutor(){
    _command = "";
}

void ZExecutor::parse(const ZConfig &el){
    if(el.text().isEmpty()){
	if(el.hasAttribute("value")){
	    _command = el.attribute("value");
	}
    }else{
	_command = el.text();
    }

    if(el.hasAttribute("oneline"))
	if(!el.attribute("oneline").isEmpty())
	    _oneLine = el.attribute("oneline");
}

void ZExecutor::exec(){
    if(_command.isEmpty()){
	z_log_error("ZExecutor: No command specified.");
	return;
    }else{
	if(_oneLine.isEmpty())
	    _lastOutput = ZUtil::exec(_command);
	else
	    _lastOutput = ZUtil::execln(_command,_oneLine);
    }

    emit executed(_lastOutput);
}

void ZExecutor::setCommand(QString command){
    QString oldCmd = _command;
    _command = command;
    emit commandChanged(command, oldCmd);
}
