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

#ifndef ZTASKBAR_H
#define ZTASKBAR_H

#include <QtCore>
#include <QtGui>
#include <QX11Info>

#include <zutil.h>
#include <zui/zuiutils.h>
#include <zui/zwidget.h>
#include <zeventmanager.h>

#include "zxwindowlistmodel.h"
#include "zxwindowlistitem.h"

class ZTaskbar : public QListView, public ZWidget
{
  Q_OBJECT
  Q_PROPERTY(int itemWidth READ itemWidth WRITE setItemWidth)
  Q_PROPERTY(int itemHeight READ itemHeight WRITE setItemHeight)

public:
  ZTaskbar(const ZConfig &el, QWidget *parent = 0);
  ~ZTaskbar();
  QSize sizeHint();
  void setScreenPosition(ZXScreenEdge edge);
  int itemWidth(){ return _itemGrid.width(); };
  int itemHeight(){ return _itemGrid.height(); };
  void setItemWidth(int w){ _itemGrid.setWidth(w); setGridSize(_itemGrid); };
  void setItemHeight(int h){ _itemGrid.setHeight(h); setGridSize(_itemGrid); };

public slots:
  //! \deprecated
  virtual bool invoke(QString,QString,QString,QString,QString,QString,QString);

private slots:
  void activate(QModelIndex index);
  void refreshWindowList();
  void setWmProperties();

private:
  virtual void init();
  virtual void parse(const ZConfig&);

private:
   ZXScreenEdge _edge;
   ZXWindow *_currentWindow;
   QSize _itemGrid;

};

#endif // ZTASKBAR_H
