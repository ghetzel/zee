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

void ZTaskbar::parse(const ZConfig &el){

}

void ZTaskbar::setWmProperties(){
  if(_currentWindow){
  //  _currentWindow->addStrut(QSize(width(),height()-2), _edge);
  }
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

