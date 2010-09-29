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

#include "ztaskbar.h"

ZTaskbar::ZTaskbar(const ZConfig &el, QWidget *parent)
  : QListView(parent),
    ZWidget(el,this)
{
  setScreenPosition(SouthEdge);
  init();
}

void ZTaskbar::setScreenPosition(ZXScreenEdge edge){
  _edge = edge;

  //! \todo need to reinit struts code
}

void ZTaskbar::init(){
  _currentWindow = new ZXWindow(QApplication::topLevelWidgets().first()->winId(),
				QX11Info::display());
  //setWmProperties();
  setModel(new ZXWindowListModel(this));
  setItemDelegate(new ZXWindowListItem);
  setSelectionMode(QListView::SingleSelection);
  setViewMode(QListView::IconMode);
  setGridSize(_itemGrid);
  setAutoScroll(false);
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  parse(_config);

  connect(this, SIGNAL(clicked(QModelIndex)),
	  this, SLOT(activate(QModelIndex)));

  connect(model(), SIGNAL(dataChanged()),
	  this, SLOT(refreshWindowList()));
}

void ZTaskbar::parse(const ZConfig&){

}

void ZTaskbar::setWmProperties(){
}

void ZTaskbar::refreshWindowList(){
  setModel(new ZXWindowListModel(this));
}

ZTaskbar::~ZTaskbar(){
}

QSize ZTaskbar::sizeHint(){
  return QSize(QApplication::desktop()->width(), layout()->geometry().height());
}

void ZTaskbar::activate(QModelIndex index){
  uint winId = model()->data(index, ZXWindowListModel::WindowID).toUInt();
  //! \bug windows will not raise if their state contains _NET_WM_STATE_HIDDEN
  //ZXWindow::setState(ZXWindow::WSMaxHorz|ZXWindow::WSMaxVert,winId); // doesn't work yet
  ZXWindow::raise(winId);
}

bool ZTaskbar::invoke(QString, QString, QString, QString, QString, QString,
		      QString){
  return true;
}

