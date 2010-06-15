#include "ztaskbar.h"

ZTaskbar::ZTaskbar(QWidget *parent)
  : QListView(parent)
{
  setScreenPosition(SouthEdge);
  init();
}

ZTaskbar::ZTaskbar(ZXScreenEdge edge, QWidget *parent)
  : QListView(parent)
{
  setScreenPosition(edge);
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


  connect(this, SIGNAL(clicked(QModelIndex)),
          this, SLOT(activate(QModelIndex)));

  connect(model(), SIGNAL(dataChanged()),
          this, SLOT(refreshWindowList()));
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

bool ZTaskbar::invoke(QString action, QString arg1, QString arg2, QString arg3,
                      QString arg4, QString arg5, QString arg6){

  return true;
}

