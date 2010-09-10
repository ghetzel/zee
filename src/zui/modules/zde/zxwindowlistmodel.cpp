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

#include "zxwindowlistmodel.h"

ZXWindowListModel::ZXWindowListModel(QObject *parent)
  : QAbstractListModel(parent){
    _rootWindow = new ZXRootWindow;
    getClientList();

    connect(_rootWindow, SIGNAL(clientListChanged()), SIGNAL(dataChanged()));
}

int ZXWindowListModel::rowCount(const QModelIndex&) const{
  return _clientList.count();
}

QVariant ZXWindowListModel::data(const QModelIndex &index, int role) const{
  if(!index.isValid())
    return QVariant();

  if(index.row() >= _clientList.size())
    return QVariant();

  ZXWindow *wnd = _clientList.at(index.row());

  switch(role){
  case Qt::DecorationRole:
    return QVariant(wnd->icon());
  case Qt::DisplayRole:
  case ZXWindowListModel::Name:
  case Qt::ToolTipRole:
    return QVariant(wnd->name());
  case ZXWindowListModel::Desktop:
    return QVariant(wnd->desktop());
  case ZXWindowListModel::WindowID:
    return QVariant(static_cast<uint>(wnd->winId()));
  case ZXWindowListModel::PID:
    return QVariant(wnd->pid());
  }

  return QVariant();
}


void ZXWindowListModel::getClientList(){
  _clientList = _rootWindow->clientList();
}
