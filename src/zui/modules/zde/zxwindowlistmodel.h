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
  int rowCount(const QModelIndex &parent) const;
  QVariant data(const QModelIndex &index, int role) const;

private:
  void getClientList();
  ZXRootWindow *_rootWindow;
  QList<ZXWindow*> _clientList;

signals:
  void dataChanged();
};

#endif // ZXWINDOWLISTMODEL_H
