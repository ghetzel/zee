#ifndef ZROOT_H
#define ZROOT_H

#include <zui/zcontainerwidget2.h>

/*!
  \class ZRoot
  \ingroup zeeapp
  \brief Represents the main window widget that all other widgets are
  descendants of.
*/
class ZRoot : public QFrame, public ZContainerWidget2{
  Q_OBJECT

public:
  ZRoot(const ZConfig &el, QWidget *parent)
      : QFrame(parent),
      ZContainerWidget2(el,this){};

private:
  void parse(const ZConfig&){};
};

#endif // ZROOT_H
