#ifndef ZTASKBAR_H
#define ZTASKBAR_H

#include <QtCore>
#include <QtGui>
#include <QX11Info>

#include <zutil.h>
#include <zui/zuiutils.h>
#include <zui/zwidget.h>

#include "zxwindowlistmodel.h"
#include "zxwindowlistitem.h"

class ZTaskbar : public QListView
{
  Q_OBJECT
  Q_PROPERTY(int itemWidth READ itemWidth WRITE setItemWidth)
  Q_PROPERTY(int itemHeight READ itemHeight WRITE setItemHeight)

public:
  ZTaskbar(ZXScreenEdge edge, QWidget *parent = 0);
  ZTaskbar(QWidget *parent = 0);
  ~ZTaskbar();
  QSize sizeHint();
  void setScreenPosition(ZXScreenEdge edge);
  int itemWidth(){ return _itemGrid.width(); };
  int itemHeight(){ return _itemGrid.height(); };
  void setItemWidth(int w){ _itemGrid.setWidth(w); setGridSize(_itemGrid); };
  void setItemHeight(int h){ _itemGrid.setHeight(h); setGridSize(_itemGrid); };

public slots:
  virtual bool invoke(QString action, QString arg1, QString arg2, QString arg3,
                      QString arg4, QString arg5, QString arg6);

private slots:
  void activate(QModelIndex index);
  void refreshWindowList();
  void setWmProperties();

private:
  virtual void init();

private:
   ZXScreenEdge _edge;
   ZXWindow *_currentWindow;
   QSize _itemGrid;

};

#endif // ZTASKBAR_H
