#ifndef ZXWINDOW_H
#define ZXWINDOW_H

#include <QtCore>
#include <QIcon>
#include <QApplication>
#include <QX11Info>
#include <X11/Xlib.h>
#include "zxevent.h"
#include "zxserver.h"

/*!
  \class ZXWindow
  \ingroup zui_zx11
  \brief Represents an X11 Window
*/
class ZXWindow : public QObject, public ZXEvent{
  Q_OBJECT
  Q_ENUMS(WindowState)
  Q_ENUMS(WindowType)

public:
//! Corresponds to valid values of _NET_WM_WINDOW_TYPE
  enum WindowType{
    WMDesktop   = 1<<1,
    WMDialog    = 1<<2,
    WMDock      = 1<<3,
    WMMenu      = 1<<4,
    WMNormal    = 1<<5,
    WMSplash    = 1<<6,
    WMToolbar   = 1<<7
  };

//! Corresponds to valid values of _NET_WM_STATE
//! \note incomplete
  enum WindowState{
    WSNone         = 0,     // 0
    WSAbove        = 1,     // 1
    WSBelow        = 1<<1,  // 2
    WSDemandsAttn  = 1<<2,  // 4
    WSFullscreen   = 1<<3,  // 8
    WSHidden       = 1<<4,  // 16
    WSMaxHorz      = 1<<5,  // 32
    WSMaxVert      = 1<<6,  // 64
    WSModal        = 1<<7,  // 128
    WSShaded       = 1<<8,  // 256
    WSSkipPager    = 1<<9,  // 512
    WSSkipTaskbar  = 1<<10, // 1024
    WSSticky       = 1<<11, // 2048
  };

public:
//! Construct a new ZXWindow from \a winId on \a display.
  ZXWindow(Window winId, Display *display = QX11Info::display());

//! Return the current states of the window as an OR'd set of \c WindowStates
  int state()                 { return _state; };

//! Return the current window's ID.
  Window winId()              { return _winId; };

//! Return the current window's name.
  QString name()              { return _name; };

//! Return the current window's desktop number.
  int desktop()               { return _desktop; };

//! Return the current window's screen number.
  int screen()                { return _screen; };

//! Return the current window's icon(s)
  QIcon icon()                { return _icon; };

//! Return the current window types as an OR'd set of \c WindowTypes
  WindowType type()           { return _type; };

//! Return the PID of the current window.
  uint pid()                  { return _pid; };

//! Return the date/time of the last user activity on this window.
//! \todo currently a placeholder value, actually implement this
  QDateTime lastUserActivity(){ return QDateTime::currentDateTime(); };

//! Creates a strut of given dimensions along a given edge
  void addStrut(QSize dimensions, ZXScreenEdge edge);  

//! Raises this window
  void raise();

//! Sets the type of this window, taking an OR'd list of WindowTypes
  void setWindowType(WindowType type);

public:
//! Return the name of \a winId
  static QString name(Window winId, Display *display = QX11Info::display());

//! Return the desktop number of \a winId
  static int desktop(Window winId, Display *display = QX11Info::display());

//! Return the screen number of \a winId
  static int screen(Window winId, Display *display = QX11Info::display());

//! Return the icon(s) from \a winId
  static QIcon icon(Window winId, Display *display = QX11Info::display());

//! Return the PID of \a winId
  static uint pid(Window winId, Display *display = QX11Info::display());

//! Return the type of \a winId as an OR'd set of WindowTypes
  static WindowType type(Window winId, Display *display = QX11Info::display());

//! Return the state of \a winId as an OR'd set of WindowStates
  static int state(Window winId, Display *display = QX11Info::display());

//! Raises window \a winId
  static void raise(Window w, Display *d = QX11Info::display());

//! Sets the type of window \a winId, taking an OR'd list of WindowTypes
  static void setWindowType(WindowType wt, Window w, Display *d = QX11Info::display());

//! Sets the state of the window, taking an OR'd list of WindowStates
  static void setState(int states, Window w, Display *d = QX11Info::display());

public slots:
//! XEvent handler for this window
  bool eventSelect(XEvent *xe);

//! updates window data for \a property or all properties if left empty.
  void updateValues(QString property = "");

signals:
//! signal that the specified property has changed
  void propertyNotify(QString);


private:
  Display *_display;
  Window _winId;
  uint _pid;
  int _desktop;
  int _screen;
  QString _name;
  QIcon _icon;
  QDateTime _lastUserActivity;
  WindowType _type;
  int _state;


};

#endif // ZXWINDOW_H
