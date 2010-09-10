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

#include "zxserver.h"

QHash<QString,Atom> ZXServer::_atoms;
QList<QString> ZXServer::_atomNames;
Display *ZXServer::_display;

/*-- Most of this is just here for reference and will be going away
// UTF-8 string
static Atom UTF8_STRING              = 0;

// Root Window Properties
static Atom XSupported               = 0;
static Atom XClientList              = 0;
static Atom XClientListStacking      = 0;
static Atom XDesktopGeometry         = 0;
static Atom XDesktopViewport         = 0;
static Atom XCurrentDesktop          = 0;
static Atom XDesktopNames            = 0;
static Atom XDesktopCount            = 0;
static Atom XActiveWindow            = 0;
static Atom XWorkArea                = 0;
static Atom XSupportingWMCheck       = 0; // ???
static Atom XVirtualRoots            = 0;
static Atom XShowingDesktop          = 0;

// Root Window Messages
static Atom XMsgCloseWindow          = 0;
static Atom XMsgRestackWindow        = 0;
static Atom XMsgMoveResize           = 0;
static Atom XMsgMoveResizeWindow     = 0;

// Application Window Properties
static Atom WindowName               = 0;
static Atom WindowVisibleName        = 0;
static Atom WindowIconName           = 0;
static Atom WindowVisibleIconName    = 0;
static Atom WindowDesktop            = 0;
static Atom WindowType               = 0;
static Atom WindowState              = 0;
static Atom WindowStrut              = 0;
static Atom WindowStrutPartial       = 0;
static Atom WindowIconGeometry       = 0;
static Atom WindowIcon               = 0;
static Atom WindowPID                = 0;
static Atom WindowUserTime           = 0;
static Atom WindowHandledIcons       = 0;
static Atom WindowStartupId          = 0;
static Atom WindowAllowedActions     = 0;
static Atom WindowRole               = 0;
static Atom WindowFrameExtents       = 0;

// Protocols
static Atom AppProtocols             = 0;
static Atom AppPing                  = 0;
static Atom AppTakeActivity          = 0;

// Window Types
static Atom WindowTypeNormal         = 0;
static Atom WindowTypeDesktop        = 0;
static Atom WindowTypeDock           = 0;
static Atom WindowTypeToolbar        = 0;
static Atom WindowTypeMenu           = 0;
static Atom WindowTypeDialog         = 0;
static Atom WindowTypeUtility        = 0;
static Atom WindowTypeSplash         = 0;

// Window State
static Atom WindowStateModal         = 0;
static Atom WindowStateSticky        = 0;
static Atom WindowStateMaxVert       = 0;
static Atom WindowStateMaxHorz       = 0;
static Atom WindowStateShaded        = 0;
static Atom WindowStateSkipTaskbar   = 0;
static Atom WindowStateSkipPager     = 0;
static Atom WindowStateHidden        = 0;
static Atom WindowStateFullscreen    = 0;
static Atom WindowStateAbove         = 0;
static Atom WindowStateBelow         = 0;
static Atom WindowStateDemandsAttn   = 0;

// Allowed Actions
static Atom ActionMove               = 0;
static Atom ActionResize             = 0;
static Atom ActionMinimize           = 0;
static Atom ActionShade              = 0;
static Atom ActionStick              = 0;
static Atom ActionMaxVert            = 0;
static Atom ActionMaxHorz            = 0;
static Atom ActionFullscreen         = 0;
static Atom ActionChangeDesktop      = 0;
static Atom ActionClose              = 0;
*/


void ZXServer::initialize(Display *d){
  initAtoms();
  _display = d;
}


Atom ZXServer::atom(QString key){
  if(_atoms.contains(key)){
//    z_log_debug("Get Atom '" + key + "'");
    return _atoms[key];
  }else{
    z_log_debug("Missing Atom '" + key + "'");
  }

  return NULL;
}

WindowPropertyReturn ZXServer::getProperty(QString key, Window w, Display *d){

  WindowPropertyReturn retval;
  retval.data.asChar = NULL;
  retval.data.asShort = NULL;
  retval.data.asLong = NULL;
  retval.rawData = NULL;

  unsigned char *tempdata = NULL;

  if(_atoms.contains(key)){
    retval.result = XGetWindowProperty(d,
		       w,
		       _atoms[key],
		       0,
		       0x7fffffff,
		       0,
		       AnyPropertyType,
		       &retval.returnType,
		       &retval.bitFormat,
		       &retval.itemsReturned,
		       &retval.bytesRemaining,
		       &tempdata);

    retval.rawData = tempdata;

    if(retval.result == Success){
      if(retval.bitFormat == 8)
	retval.data.asChar = (char*)tempdata;
      else if(retval.bitFormat == 16)
	retval.data.asShort = (short*)tempdata;
      else if(retval.bitFormat == 32)
	retval.data.asLong = (long*)tempdata;
    }

    //z_log_debug("Key: "+QVariant(XGetAtomName(QX11Info::display(),_atoms[key])).toString());
    //z_log_debug("Format: "+QVariant(retval.bitFormat).toString());
    //z_log_debug("Type: "+QVariant(XGetAtomName(QX11Info::display(),retval.returnType)).toString());
    //z_log_debug("Items: "+QVariant((int)retval.itemsReturned).toString());
  }

  return retval;
}



QString ZXServer::getString(QString key, Window w, Display *d){
  WindowPropertyReturn r = getProperty(key,w,d);

  if(r.data.asChar && r.returnType == _atoms[UTF8_STRING])
    return QString(r.data.asChar);

  return QString();
}

unsigned int ZXServer::getCardinal(QString key, Window w, Display *d){
  WindowPropertyReturn r = getProperty(key,w,d);

  if(r.data.asLong && r.returnType == XA_CARDINAL)
    return static_cast<uint>(*r.data.asLong);

  return 0;
}

Atom ZXServer::getAtom(QString key, Window w, Display *d){
  WindowPropertyReturn r = getProperty(key,w,d);

  if(r.data.asLong && r.returnType == XA_ATOM)
    return static_cast<Atom>(*r.data.asLong);

  return 0;
}

QList<Atom> ZXServer::getAtoms(QString key, Window w, Display *d){
  WindowPropertyReturn r = getProperty(key,w,d);
  QList<Atom> retval;

//  z_log_debug("[ZXServer::getAtoms]  "+QVariant(key).toString()+".itemsReturned: " + QVariant((int)r.itemsReturned).toString());
  if(r.data.asLong && r.itemsReturned){
    for(uint i = 0; i < r.itemsReturned; i++){
      retval.append(static_cast<Atom>(r.data.asLong[i]));
    }
  }

  return retval;
}


QIcon ZXServer::getIcon(QString key, Window w, Display *d){
  WindowPropertyReturn r = getProperty(key,w,d);
  QIcon retval;


  if(r.data.asLong && r.returnType == XA_CARDINAL){
    int w,h;
    int ptr = 0;
    int len = r.itemsReturned;

//    z_log_debug("ICON: "+QVariant(len).toString());

    while(ptr < len)
    {
      w = r.data.asLong[ptr]; // item 0: width
      h = r.data.asLong[ptr+1]; // item 1: height

//      z_log_debug("  ITER: ("+QVariant(w).toString()+"x"+QVariant(h).toString()+") - "
//                  +QVariant(ptr).toString()+"/"+QVariant(len).toString());

      CARD32 *d = new CARD32[w*h];                          // allocate W*H worth of data
      memcpy(d,(r.data.asLong+ptr+2),(w*h)*sizeof(CARD32)); // copy the data, excluding items 0,1
      QImage im((uchar*)d,w,h,QImage::Format_ARGB32);       // decode the image
      QPixmap p = QPixmap::fromImage(im);                   // pixmap it

      //if(w > 22 || h > 22){
      //  p = p.scaled(QSize(22,22),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
      //}

      retval.addPixmap(p);                                  // add pixmap to icon
      ptr += (w*h)+2;                                       // move pointer to end
    }
  }

  return retval;
}


Window ZXServer::getWindow(QString key, Window w, Display *d){
  WindowPropertyReturn r = getProperty(key,w,d);

  if(r.data.asLong && r.returnType == XA_WINDOW)
    return static_cast<Atom>(*r.data.asLong);

  return 0;
}

QList<Window> ZXServer::getWindows(QString key, Window w, Display *d){
  WindowPropertyReturn r = getProperty(key,w,d);
  QList<Window> retval;

  if(r.data.asLong && r.itemsReturned){
    for(uint i = 0; i < r.itemsReturned; i++){
      retval.append(static_cast<Window>(r.data.asLong[i]));
    }
  }

  return retval;
}

void ZXServer::initAtoms(){
//types
  _atomNames << UTF8_STRING;

//root properties
  _atomNames << _NET_CLIENT_LIST;
  _atomNames << _NET_WM_STRUT;
  _atomNames << _NET_WM_STRUT_PARTIAL;

//properties
  _atomNames << _NET_WM_STATE;
  _atomNames << _NET_WM_WINDOW_TYPE;
  _atomNames << _NET_WM_NAME;
  _atomNames << _NET_WM_PID;
  _atomNames << _NET_WM_DESKTOP;
  _atomNames << _NET_WM_ICON;

//states
  _atomNames << _NET_WM_STATE_ABOVE;
  _atomNames << _NET_WM_STATE_BELOW;
  _atomNames << _NET_WM_STATE_DEMANDS_ATTENTION;
  _atomNames << _NET_WM_STATE_FULLSCREEN;
  _atomNames << _NET_WM_STATE_HIDDEN;
  _atomNames << _NET_WM_STATE_MAXIMIZED_HORZ;
  _atomNames << _NET_WM_STATE_MAXIMIZED_VERT;
  _atomNames << _NET_WM_STATE_MODAL;
  _atomNames << _NET_WM_STATE_SHADED;
  _atomNames << _NET_WM_STATE_SKIP_PAGER;
  _atomNames << _NET_WM_STATE_SKIP_TASKBAR;
  _atomNames << _NET_WM_STATE_STICKY;

//window types
  _atomNames << _NET_WM_WINDOW_TYPE_DESKTOP;
  _atomNames << _NET_WM_WINDOW_TYPE_DIALOG;
  _atomNames << _NET_WM_WINDOW_TYPE_DOCK;
  _atomNames << _NET_WM_WINDOW_TYPE_MENU;
  _atomNames << _NET_WM_WINDOW_TYPE_NORMAL;
  _atomNames << _NET_WM_WINDOW_TYPE_SPLASH;
  _atomNames << _NET_WM_WINDOW_TYPE_TOOLBAR;


  foreach(QString aname, _atomNames){
    Atom aa = X11_ATOM(aname.toAscii());
    _atoms[aname] = aa;
    //z_log_debug("X: " + QString(aname) + " = " + QVariant((qreal)aa).toString());
  }

}


void ZXServer::addStrut(QSize dimensions, ZXScreenEdge edge, Window w, Display *d)
{
  QDesktopWidget *qDt = qApp->desktop();

//  _NET_WM_STRUT_PARTIAL
//
//  _NET_WM_STRUT_PARTIAL, left, right, top, bottom, left_start_y, left_end_y,
//  right_start_y, right_end_y, top_start_x, top_end_x, bottom_start_x,
//  bottom_end_x,CARDINAL[12]/32
  long strut[12] = {0,0,0,0,0,0,0,0,0,0,0,0};

  switch(edge)
  {
  case NorthEdge:
    z_log_debug("NORTH strut: "+QVariant(dimensions.height()).toString());
    strut[2] = dimensions.height();
    strut[8] = 1;
    strut[9] = qDt->width() - 1;
    break;
  case SouthEdge:
    z_log_debug("SOUTH strut: "+QVariant(dimensions.height()).toString());
    strut[3] = dimensions.height();
    strut[10] = 1;
    strut[11] = qDt->width() - 1;
    break;
  case EastEdge:
    z_log_debug("EAST strut: "+QVariant(dimensions.width()).toString());
    strut[1] = dimensions.width();
    strut[6] = 1;
    strut[7] = qDt->height() - 1;
    break;
  case WestEdge:
    z_log_debug("WEST strut: "+QVariant(dimensions.width()).toString());
    strut[0] = dimensions.width();
    strut[4] = 1;
    strut[5] = qDt->height() - 1;
    break;
  default:
    return;
  }

  z_log_debug("Add Strut: "+QVariant(dimensions.width()).toString() + "x"
	      + QVariant(dimensions.height()).toString());

  XChangeProperty(d,
		  w,
		  ZXServer::atom(_NET_WM_STRUT_PARTIAL),
		  XA_CARDINAL,
		  32,
		  PropModeReplace,
		  (unsigned char*)&strut,
		  12);
}
