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

#include "zshortcut.h"

ZShortcut::ZShortcut(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    zEvent->registerSignal(this, SIGNAL(triggered()));
    zEvent->registerSlot(this, SLOT(trigger()));
}

void ZShortcut::lateInit(){
    parse(_config);
}


void ZShortcut::parse(const ZConfig &el){
    if(el.hasAttribute("src")){
        _source = QCAST(QWidget*, zEvent->findObject(el.attribute("src"),true));
        if(_source){
            if(!el.attribute("value").isEmpty()){
                _shortcut = new QShortcut(_source);
                _shortcut->setKey(el.attribute("value"));

                connect(_shortcut, SIGNAL(activated()),
                        this, SLOT(_shortcutActivated()));

                z_log("ZShortcut: Registered '"+_shortcut->key().toString()+
                      "' to object '"+_source->objectName()+"'");
            }else{
                z_log_error("ZShortcut: No key sequence specified.");
            }
        }else{
            z_log_error("ZShortcut: Cannot find object '"+
                        el.attribute("src")+"'");
        }
    }
}

void ZShortcut::trigger(){
    _shortcutActivated();
}

void ZShortcut::_shortcutActivated(){
    z_log_debug("ZShortcut: Trigger "+_shortcut->key().toString() + " on " +
                _source->objectName());
    emit triggered();
}
