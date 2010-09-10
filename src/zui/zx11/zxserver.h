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

#ifndef ZXSERVER_H
#define ZXSERVER_H

#include <QtCore>
#include <QApplication>
#include <QIcon>
#include <QDesktopWidget>
#include <QX11Info>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xmd.h>

#include <zutil.h>

// X11_ATOM macro
//    gets the current internal value of the Xserver's Atoms
#define X11_ATOM(a)                       XInternAtom(QX11Info::display(),a,0)

// Types
#define UTF8_STRING                       "UTF8_STRING"

// Root Window Properties
#define _NET_CLIENT_LIST                  "_NET_CLIENT_LIST"
#define _NET_WM_STRUT                     "_NET_WM_STRUT"
#define _NET_WM_STRUT_PARTIAL             "_NET_WM_STRUT_PARTIAL"

// Properties
#define _NET_WM_STATE                     "_NET_WM_STATE"
#define _NET_WM_WINDOW_TYPE               "_NET_WM_WINDOW_TYPE"
#define _NET_WM_NAME                      "_NET_WM_NAME"
#define _NET_WM_PID                       "_NET_WM_PID"
#define _NET_WM_DESKTOP                   "_NET_WM_DESKTOP"
#define _NET_WM_ICON                      "_NET_WM_ICON"

// States (via _NET_WM_STATE)
#define _NET_WM_STATE_ABOVE               "_NET_WM_STATE_ABOVE"
#define _NET_WM_STATE_BELOW               "_NET_WM_STATE_BELOW"
#define _NET_WM_STATE_DEMANDS_ATTENTION   "_NET_WM_STATE_DEMANDS_ATTENTION"
#define _NET_WM_STATE_FULLSCREEN          "_NET_WM_STATE_FULLSCREEN"
#define _NET_WM_STATE_HIDDEN              "_NET_WM_STATE_HIDDEN"
#define _NET_WM_STATE_MAXIMIZED_HORZ      "_NET_WM_STATE_MAXIMIZED_HORZ"
#define _NET_WM_STATE_MAXIMIZED_VERT      "_NET_WM_STATE_MAXIMIZED_VERT"
#define _NET_WM_STATE_MODAL               "_NET_WM_STATE_MODAL"
#define _NET_WM_STATE_SHADED              "_NET_WM_STATE_SHADED"
#define _NET_WM_STATE_SKIP_PAGER          "_NET_WM_STATE_SKIP_PAGER"
#define _NET_WM_STATE_SKIP_TASKBAR        "_NET_WM_STATE_SKIP_TASKBAR"
#define _NET_WM_STATE_STICKY              "_NET_WM_STATE_STICKY"

// Window Types (via _NET_WM_WINDOW_TYPE)
#define _NET_WM_WINDOW_TYPE_DESKTOP       "_NET_WM_WINDOW_TYPE_DESKTOP"
#define _NET_WM_WINDOW_TYPE_DIALOG        "_NET_WM_WINDOW_TYPE_DIALOG"
#define _NET_WM_WINDOW_TYPE_DOCK          "_NET_WM_WINDOW_TYPE_DOCK"
#define _NET_WM_WINDOW_TYPE_MENU          "_NET_WM_WINDOW_TYPE_MENU"
#define _NET_WM_WINDOW_TYPE_NORMAL        "_NET_WM_WINDOW_TYPE_NORMAL"
#define _NET_WM_WINDOW_TYPE_SPLASH        "_NET_WM_WINDOW_TYPE_SPLASH"
#define _NET_WM_WINDOW_TYPE_TOOLBAR       "_NET_WM_WINDOW_TYPE_TOOLBAR"

struct WindowPropertyReturn{
  int bitFormat;
  unsigned long bytesRemaining;
  struct {
    char *asChar;
    short *asShort;
    long *asLong;
  } data;
  unsigned char *rawData;
  unsigned long itemsReturned;
  int result;
  Atom returnType;
};


enum ZXScreenEdge{
  NorthEdge,
  SouthEdge,
  EastEdge,
  WestEdge
};


/*!
  \class ZXServer
  \ingroup zui_zx11
  \brief Provides basic utility functions for interacting with an X11 server.

*/
class ZXServer{

private:
  static QHash<QString,Atom> _atoms;
  static QList<QString> _atomNames;
  static Display *_display;

/*!
  \internal

  Initializes and retrieves the actual values of named Atoms from the X server.
*/
  static void initAtoms();

public:
  static WindowPropertyReturn getProperty(QString key,
					  Window w,
					  Display *d=QX11Info::display());

public:
/*!
  Prepares the class for working with and talking to X11.
*/
  static void initialize(Display *d = QX11Info::display());

/*!
  Returns the current XServer representation of the Atom \a key or NULL if not
  found or is invalid.
*/
  static Atom atom(QString key);

/*!
  Retrieves property \a key as an integral value or 0 if not found or is
  invalid.
*/
  static unsigned int getCardinal(QString key,
				  Window w,
				  Display *d=QX11Info::display());

/*!
  Retrieves property \a key as a UTF8 encoded string or an empty string if not
  found or is invalid.
*/
  static QString getString(QString key,
			   Window w,
			   Display *d=QX11Info::display());

/*!
  Returns \a key as an Atom or NULL if not found or is invalid.
*/
  static Atom getAtom(QString key,
		      Window w,
		      Display *d=QX11Info::display());

/*!
  Retrieves property \a key as a list of Atoms or an empty list if not found
  or is invalid.
*/
  static QList<Atom> getAtoms(QString key,
			      Window w,
			      Display *d=QX11Info::display());

/*!
  Retrieves property \a key as a valid X window ID or NULL if not found or is
  invalid.
*/
  static Window getWindow(QString key,
			  Window w,
			  Display *d=QX11Info::display());

/*!
  Retrieves property \a key as a list of valid X window IDs or an empty list if
  not found or is invalid.
*/
  static QList<Window> getWindows(QString key,
				  Window w,
				  Display *d=QX11Info::display());

/*!
  Retrieves property \a key as a QIcon or and empty QIcon if not found or is
  invalid.
  \bug this still needs work to get multiple icons out of the _NET_WM_ICON
  property
*/
  static QIcon getIcon(QString key,
		       Window w,
		       Display *d=QX11Info::display());

//! Creates a strut of given dimensions along a given edge
  static void addStrut(QSize dimensions,
		       ZXScreenEdge edge,
		       Window winId,
		       Display *display = QX11Info::display());


/*-- Most of this is just here for reference and will be going away
public:
// UTF-8 string
  static Atom UTF8_STRING;

// Root Window Properties
  static Atom XSupported;
  static Atom XClientList;
  static Atom XClientListStacking;
  static Atom XDesktopGeometry;
  static Atom XDesktopViewport;
  static Atom XCurrentDesktop;
  static Atom XDesktopNames;
  static Atom XDesktopCount;
  static Atom XActiveWindow;
  static Atom XWorkArea;
  static Atom XSupportingWMCheck; // ???
  static Atom XVirtualRoots;
  static Atom XShowingDesktop;

// Root Window Messages
  static Atom XMsgCloseWindow;
  static Atom XMsgRestackWindow;
  static Atom XMsgMoveResize;
  static Atom XMsgMoveResizeWindow;

// Application Window Properties
  static Atom WindowName;
  static Atom WindowVisibleName;
  static Atom WindowIconName;
  static Atom WindowVisibleIconName;
  static Atom WindowDesktop;
  static Atom WindowType;
  static Atom WindowState;
  static Atom WindowStrut;
  static Atom WindowStrutPartial;
  static Atom WindowIconGeometry;
  static Atom WindowIcon;
  static Atom WindowPID;
  static Atom WindowUserTime;
  static Atom WindowHandledIcons;
  static Atom WindowStartupId;
  static Atom WindowAllowedActions;
  static Atom WindowRole;
  static Atom WindowFrameExtents;

// Protocols
  static Atom AppProtocols;
  static Atom AppPing;
  static Atom AppTakeActivity;

// Window Types
  static Atom WindowTypeNormal;
  static Atom WindowTypeDesktop;
  static Atom WindowTypeDock;
  static Atom WindowTypeToolbar;
  static Atom WindowTypeMenu;
  static Atom WindowTypeDialog;
  static Atom WindowTypeUtility;
  static Atom WindowTypeSplash;

// Window State
  static Atom WindowStateModal;
  static Atom WindowStateSticky;
  static Atom WindowStateMaxVert;
  static Atom WindowStateMaxHorz;
  static Atom WindowStateShaded;
  static Atom WindowStateSkipTaskbar;
  static Atom WindowStateSkipPager;
  static Atom WindowStateHidden;
  static Atom WindowStateFullscreen;
  static Atom WindowStateAbove;
  static Atom WindowStateBelow;
  static Atom WindowStateDemandsAttn;

// Allowed Actions
  static Atom ActionMove;
  static Atom ActionResize;
  static Atom ActionMinimize;
  static Atom ActionShade;
  static Atom ActionStick;
  static Atom ActionMaxVert;
  static Atom ActionMaxHorz;
  static Atom ActionFullscreen;
  static Atom ActionChangeDesktop;
  static Atom ActionClose;
*/


};

#endif // ZXSERVER_H
