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

#ifndef ZXWINDOWLISTMODEL_H
#define ZXWINDOWLISTMODEL_H

#include <QtCore>
#include <QtGui>
#include <QX11Info>

#include <zutil.h>
#include <zui/zx11/zxwindow.h>
#include <zui/zx11/zxrootwindow.h>


class ZXWindowListModel : public QAbstractListModel{
  Q_OBJECT

public:
  enum ZXWindowRoles{
    WindowID  = 1<<10,
    PID       = 1<<11,
    Name      = 1<<12,
    Desktop   = 1<<13,
    Screen    = 1<<14
  };

  ZXWindowListModel(QObject *parent =0);
  int rowCount(const QModelIndex&) const;
  QVariant data(const QModelIndex &index, int role) const;

private:
  void getClientList();
  ZXRootWindow *_rootWindow;
  QList<ZXWindow*> _clientList;

signals:
  void dataChanged();
};

#endif // ZXWINDOWLISTMODEL_H
