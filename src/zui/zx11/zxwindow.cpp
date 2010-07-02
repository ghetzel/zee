#include "zxwindow.h"

ZXWindow::ZXWindow(Window winId, Display *display){
  z_log_debug("WINDOW: " + QVariant((int)winId).toString());
  _winId = winId;
  _display = display;

  updateValues();

//connect event notifications to updaters
  connect(this, SIGNAL(propertyNotify(QString)),
	  this, SLOT(updateValues(QString)));

//connect to application X11 events
  connect(qApp, SIGNAL(x11EventReceived(XEvent*)),
	  this, SLOT(eventSelect(XEvent*)));

  /*! \bug Currently cannot select window events for an arbitrary window
	   because this will break Qt's event loop if you exclude certain events
	   from the current application's window.  Add a check for whether we
	   are the app window and handle accordingly.
   */
  /*
//tell X to give this application certain events
  if(_winId == static_cast<ulong>(QX11Info::appRootWindow(QX11Info::appScreen()))){
    XSelectInput(_display, _winId, KeymapStateMask|EnterWindowMask|LeaveWindowMask|PropertyChangeMask);
  }else{
    XSelectInput(_display, _winId, PropertyChangeMask);
  }
  */
}

void ZXWindow::updateValues(QString property){
  if(property.isEmpty() || property == _NET_WM_WINDOW_TYPE)
    _type     = ZXWindow::type(_winId, _display);
  if(property.isEmpty() || property == _NET_WM_PID)
    _pid      = ZXWindow::pid(_winId, _display);
  if(property.isEmpty() || property == _NET_WM_NAME)
    _name     = ZXWindow::name(_winId, _display);
  if(property.isEmpty() || property == _NET_WM_ICON)
    _icon     = ZXWindow::icon(_winId, _display);
  if(property.isEmpty() || property == _NET_WM_DESKTOP)
    _desktop  = ZXWindow::desktop(_winId, _display);
  if(property.isEmpty() || property == _NET_WM_STATE)
    _state    = ZXWindow::state(_winId, _display);
  if(property.isEmpty())
  _screen   = ZXWindow::screen(_winId, _display);
  //if(property.isEmpty() || property == _NET_WM_USER_TIME)
  //_lastUserActivity = ??? (QTime from UNIX timestamp..?)
}


QIcon ZXWindow::icon(Window winId, Display *display){
  return ZXServer::getIcon(_NET_WM_ICON, winId, display);
}

QString ZXWindow::name(Window winId, Display *display){
  QString n = ZXServer::getString(_NET_WM_NAME, winId, display);
  z_log_debug("    Name:\t"+n);
  return n;
}

uint ZXWindow::pid(Window winId, Display *display){
  return ZXServer::getCardinal(_NET_WM_PID, winId, display);
}

int ZXWindow::desktop(Window winId, Display *display){
  return ZXServer::getCardinal(_NET_WM_DESKTOP, winId, display);
}

int ZXWindow::screen(Window, Display*){
//! \todo find out the actual EWMH property for this
  return QX11Info::appScreen();
}

ZXWindow::WindowType ZXWindow::type(Window winId, Display *display){
  QList<Atom> wtypes = ZXServer::getAtoms(_NET_WM_WINDOW_TYPE, winId, display);
//return the first type found
  foreach(Atom wtype, wtypes){
    if(wtype == ZXServer::atom(_NET_WM_WINDOW_TYPE_DESKTOP))
      return WMDesktop;
    else if(wtype == ZXServer::atom(_NET_WM_WINDOW_TYPE_DIALOG))
      return WMDialog;
    else if(wtype == ZXServer::atom(_NET_WM_WINDOW_TYPE_DOCK))
      return WMDock;
    else if(wtype == ZXServer::atom(_NET_WM_WINDOW_TYPE_MENU))
      return WMMenu;
    else if(wtype == ZXServer::atom(_NET_WM_WINDOW_TYPE_SPLASH))
      return WMSplash;
    else if(wtype == ZXServer::atom(_NET_WM_WINDOW_TYPE_TOOLBAR))
      return WMToolbar;
    else // _NET_WM_WINDOW_TYPE_NORMAL
      return WMNormal;
  }

  return WMNormal;
}

int ZXWindow::state(Window winId, Display *display)
{
  QList<Atom> wstates = ZXServer::getAtoms(_NET_WM_STATE, winId, display);
  int wstate = WSNone;

//return the first type found
  foreach(Atom ws, wstates){
//    z_log_debug("    State:\t"+QVariant((int)ws).toString());
    if(ws == ZXServer::atom(_NET_WM_STATE_ABOVE))
      wstate |= WSAbove;
    else if(ws == ZXServer::atom(_NET_WM_STATE_BELOW))
      wstate |= WSBelow;
    else if(ws == ZXServer::atom(_NET_WM_STATE_DEMANDS_ATTENTION))
      wstate |= WSDemandsAttn;
    else if(ws == ZXServer::atom(_NET_WM_STATE_FULLSCREEN))
      wstate |= WSFullscreen;
    else if(ws == ZXServer::atom(_NET_WM_STATE_HIDDEN))
      wstate |= WSHidden;
    else if(ws == ZXServer::atom(_NET_WM_STATE_MAXIMIZED_HORZ))
      wstate |= WSMaxHorz;
    else if(ws == ZXServer::atom(_NET_WM_STATE_MAXIMIZED_VERT))
      wstate |= WSMaxVert;
    else if(ws == ZXServer::atom(_NET_WM_STATE_MODAL))
      wstate |= WSModal;
    else if(ws == ZXServer::atom(_NET_WM_STATE_SHADED))
      wstate |= WSShaded;
    else if(ws == ZXServer::atom(_NET_WM_STATE_SKIP_PAGER))
      wstate |= WSSkipPager;
    else if(ws == ZXServer::atom(_NET_WM_STATE_SKIP_TASKBAR))
      wstate |= WSSkipTaskbar;
    else if(ws == ZXServer::atom(_NET_WM_STATE_STICKY))
      wstate |= WSSticky;
  }

  return wstate;
}


void ZXWindow::setState(int states, Window w, Display *d)
{
  QVector<Atom> _atoms;

  if((states&WSAbove) == WSAbove)
    _atoms.append(ZXServer::atom(_NET_WM_STATE_ABOVE));
  else if((states&WSAbove) == WSBelow)
    _atoms.append(ZXServer::atom(_NET_WM_STATE_BELOW));
  else if((states&WSAbove) == WSDemandsAttn )
    _atoms.append(ZXServer::atom(_NET_WM_STATE_DEMANDS_ATTENTION ));
  else if((states&WSAbove) == WSFullscreen )
    _atoms.append(ZXServer::atom(_NET_WM_STATE_FULLSCREEN ));
  else if((states&WSAbove) == WSHidden )
    _atoms.append(ZXServer::atom(_NET_WM_STATE_HIDDEN ));
  else if((states&WSAbove) == WSMaxHorz )
    _atoms.append(ZXServer::atom(_NET_WM_STATE_MAXIMIZED_HORZ ));
  else if((states&WSAbove) == WSMaxVert )
    _atoms.append(ZXServer::atom(_NET_WM_STATE_MAXIMIZED_VERT ));
  else if((states&WSAbove) == WSModal )
    _atoms.append(ZXServer::atom(_NET_WM_STATE_MODAL ));
  else if((states&WSAbove) == WSShaded )
    _atoms.append(ZXServer::atom(_NET_WM_STATE_SHADED ));
  else if((states&WSAbove) == WSSkipPager )
    _atoms.append(ZXServer::atom(_NET_WM_STATE_SKIP_PAGER ));
  else if((states&WSAbove) == WSSkipTaskbar )
    _atoms.append(ZXServer::atom(_NET_WM_STATE_SKIP_TASKBAR ));
  else if((states&WSAbove) == WSSticky )
    _atoms.append(ZXServer::atom(_NET_WM_STATE_STICKY ));

  XChangeProperty(d,w,
		  ZXServer::atom(_NET_WM_STATE),
		  ZXServer::atom(_NET_WM_STATE),
		  32,
		  PropModeReplace,
		  (u_char*)_atoms.constData(),
		  _atoms.count());

}

void ZXWindow::addStrut(QSize dimensions, ZXScreenEdge edge)
{
  ZXServer::addStrut(dimensions, edge, _winId, _display);
}


void ZXWindow::raise()
{
  raise(_winId);
}


void ZXWindow::raise(Window w, Display *d)
{
  XRaiseWindow(d, w);
}


void ZXWindow::setWindowType(ZXWindow::WindowType wt)
{
  ZXWindow::setWindowType(wt, _winId, _display);
}

void ZXWindow::setWindowType(ZXWindow::WindowType wt, Window w, Display *d)
{
  Atom wtype = NULL;

  switch(wt)
  {
  case WMDesktop:
    z_log_debug("Window: Desktop");
    wtype = X11_ATOM(_NET_WM_WINDOW_TYPE_DESKTOP);
    break;
  case WMDialog:
    z_log_debug("Window: Dialog");
    wtype = X11_ATOM(_NET_WM_WINDOW_TYPE_DIALOG);
    break;
  case WMDock:
    z_log_debug("Window: Dock");
    wtype = X11_ATOM(_NET_WM_WINDOW_TYPE_DOCK);
    break;
  case WMMenu:
    z_log_debug("Window: Menu");
    wtype = X11_ATOM(_NET_WM_WINDOW_TYPE_MENU);
    break;
  case WMSplash:
    z_log_debug("Window: Splash");
    wtype = X11_ATOM(_NET_WM_WINDOW_TYPE_SPLASH);
    break;
  case WMToolbar:
    z_log_debug("Window: Toolbar");
    wtype = X11_ATOM(_NET_WM_WINDOW_TYPE_TOOLBAR);
    break;
  default: // normal window
    z_log_debug("Window: Normal");
    wtype = X11_ATOM(_NET_WM_WINDOW_TYPE_NORMAL);
  }

 // z_log_debug("Set property: "+QVariant((int)wtype).toString());

  XChangeProperty(d,
		  w,
		  X11_ATOM(_NET_WM_WINDOW_TYPE),
		  XA_ATOM,
		  32,
		  PropModeReplace,
		  (u_char*)&wt,
		  1);
}

bool ZXWindow::eventSelect(XEvent *xe){
  switch(xe->type){
  case PropertyNotify:
    emit propertyNotify(XGetAtomName(_display,xe->xproperty.atom));
    return true;
  }

  return false;
}
