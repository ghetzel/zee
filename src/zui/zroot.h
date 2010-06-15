#ifndef ZROOT_H
#define ZROOT_H

#include <QFrame>

/*!
  \class ZRoot
  \ingroup zeeapp
  \brief Represents the main window widget that all other widgets are
  descendants of.
*/
class ZRoot : public QFrame{
  Q_OBJECT

public:
  ZRoot(QWidget *parent=0) : QFrame(parent){};
};

#endif // ZROOT_H
