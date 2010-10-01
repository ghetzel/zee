#ifndef ZROOT_H
#define ZROOT_H

#include <zui/zcontainerwidget.h>

/*!
  \class ZRoot
  \ingroup zeeapp
  \brief Represents the main window widget that all other widgets are
  descendants of.
*/
class ZRoot : public QFrame, public ZContainerWidget{
  Q_OBJECT

public:
  ZRoot(const ZConfig &el, QWidget *parent)
      : QFrame(parent),
      ZContainerWidget(el,this){};

private:
  void parse(const ZConfig&){};
};

#endif // ZROOT_H
