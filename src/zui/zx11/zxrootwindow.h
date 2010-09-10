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

#ifndef ZXROOTWINDOW_H
#define ZXROOTWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QX11Info>

#include <X11/Xlib.h>
#include <X11/Xatom.h>

#include "zxevent.h"
#include "zxwindow.h"

/*!
  \class ZXRootWindow
  \ingroup zui_zx11
  \brief Represents the root window of a given X11 display.
*/
class ZXRootWindow : public QObject, public ZXEvent{
  Q_OBJECT

public:
//! Creates a new accessor for the root window of display \a d
  ZXRootWindow(Display *d = QX11Info::display());
//! Returns the list of client windows of this display.
  QList<ZXWindow*> clientList();
//! Creates a strut of given dimensions along a given edge
  void addStrut(QSize dimensions, ZXScreenEdge edge);

public:
  void p_clientList();

public slots:
//! XEvent handler for this window
  bool eventSelect(XEvent *xe);

//! updates window data for \a property or all properties if left empty.
  void updateValues(QString property = "");

private:
//! \internal
//! initializes this root window's information
  void init();

private:
  Display *_display;
  Window _rootWindow;
  QHash<Window,ZXWindow*> _clientList;

signals:
//! signal that the specified property has changed
  void propertyNotify(QString);
//! signal that the list of clients has changed
  void clientListChanged();
};

#endif // ZXROOTWINDOW_H
