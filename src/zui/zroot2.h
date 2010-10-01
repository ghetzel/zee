#ifndef ZROOT_H
#define ZROOT_H

#include <zcontainer.h>

/*!
  \class ZRoot
  \ingroup zeeapp
  \brief Represents the main window widget that all other widgets are
  descendants of.
*/
class ZRoot : public ZContainer{
  Q_OBJECT

public:
  ZRoot(const ZConfig &el, QWidget *parent) : ZContainer(el,parent){};

private:
  void parse(const ZConfig&){};
};

#endif // ZROOT_H
