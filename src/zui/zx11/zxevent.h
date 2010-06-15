#ifndef ZXEVENT_H
#define ZXEVENT_H

#include <QtCore>
#include <X11/Xlib.h>

class ZXEvent{

public:
  virtual bool eventSelect(XEvent *xe){ return false; };
  virtual void updateValues(QString property = ""){ return; };
};

#endif // ZXEVENT_H
