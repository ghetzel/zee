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

#include "zscreenmanager.h"

ZScreenManager::ZScreenManager(const ZConfig &el, QWidget *parent)
  : QStackedWidget(parent),
    ZContainerWidget(el,this){
    parse(_config);
    zEvent->registerSlot(this,SLOT(jump(QString)));
}

void ZScreenManager::parse(const ZConfig &el){
//  set default screen, if specified
    if(el.hasAttribute("default"))
      setDefaultScreen(el.attribute("default"));
}

int ZScreenManager::addScreen(QWidget *widget, QString id)
{
  int stackId = addWidget(widget);
  _screens.insert(id, stackId);

  z_log_debug("ZScreenManager: Adding screen '"+id+"' as index "+STR(stackId));

//if we just added the default screen, switch to it
//! \bug I have no idea why this isnt working...
  if(id == _defaultScreen)
   jump(_defaultScreen);

  return stackId;
}

void ZScreenManager::setDefaultScreen(QString screen)
{
  _defaultScreen = screen;
}

void ZScreenManager::jump(QString screen){
    if(screen.isEmpty())
        _currentScreen = _defaultScreen;
    else
        _currentScreen = screen;

    z_log_debug("ZScreenManager: Jumping: '"+_currentScreen+"' ("+STR(_screens.value(_currentScreen))+")");
    setCurrentIndex(_screens.value(_currentScreen));
}

QString ZScreenManager::screen(){
    return _currentScreen;
}
