#include "zscreenmanager.h"

ZScreenManager::ZScreenManager(const ZConfig &el, QWidget *parent)
  : QStackedWidget(parent),
    ZWidget(el,this){
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
  screens.insert(id, stackId);

//if we just added the default screen, switch to it
//! \bug I have no idea why this isnt working...
  if(id == _defaultScreen)
   jump();

  return stackId;
}

void ZScreenManager::setDefaultScreen(QString screen)
{
  _defaultScreen = screen;
}

void ZScreenManager::jump(QString screen){
    z_log_debug("Jumping: '"+screen+"'");
    if(screen.isEmpty())
	_currentScreen = _defaultScreen;
    else
	_currentScreen = screen;
    setCurrentIndex(screens.value(_currentScreen));
}

QString ZScreenManager::screen(){
    return _currentScreen;
}
