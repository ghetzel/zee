#include "zxwindowlistmodel.h"

ZXWindowListModel::ZXWindowListModel(QObject *parent)
  : QAbstractListModel(parent){
    _rootWindow = new ZXRootWindow;
    getClientList();

    connect(_rootWindow, SIGNAL(clientListChanged()), SIGNAL(dataChanged()));
}

int ZXWindowListModel::rowCount(const QModelIndex &parent) const{
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
