#include "zxrootwindow.h"

ZXRootWindow::ZXRootWindow(Display *d){
  _display = d;
  _rootWindow = RootWindow(d, QX11Info::appScreen());

  updateValues();

  connect(this, SIGNAL(propertyNotify(QString)),
          this, SLOT(updateValues(QString)));

  connect(qApp, SIGNAL(x11EventReceived(XEvent*)),
          this, SLOT(eventSelect(XEvent*)));

//select property change and structure notify events on this root window
  XSelectInput(_display, _rootWindow, PropertyChangeMask|StructureNotifyMask);


}


void ZXRootWindow::addStrut(QSize dimensions, ZXScreenEdge edge)
{
  ZXServer::addStrut(dimensions, edge, _rootWindow, _display);
}

void ZXRootWindow::updateValues(QString property){
  if(property.isEmpty() || property == _NET_CLIENT_LIST)
    p_clientList();
}

void ZXRootWindow::p_clientList(){
  QList<Window> clientIds = ZXServer::getWindows(_NET_CLIENT_LIST,
                                                 _rootWindow,
                                                 _display);

  ZXWindow *cwin = NULL;

  _clientList.clear();
  foreach(Window w, clientIds){
    cwin = new ZXWindow(w,_display);
    if(cwin->type() == ZXWindow::WMNormal){
      if(ZUtil::hasFlag(ZXWindow::WSSkipPager,cwin->state()) ||
         ZUtil::hasFlag(ZXWindow::WSSkipTaskbar,cwin->state())){
        continue;
      }else{
        _clientList.insert(w, cwin);
      }
    }
  }

  emit clientListChanged();
}

QList<ZXWindow*> ZXRootWindow::clientList(){
  return _clientList.values();
}

bool ZXRootWindow::eventSelect(XEvent *xe){
  switch(xe->type){
  case PropertyNotify:
    emit propertyNotify(XGetAtomName(_display,xe->xproperty.atom));
    return true;
  }

  return false;
};
