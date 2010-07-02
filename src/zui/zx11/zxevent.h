#ifndef ZXEVENT_H
#define ZXEVENT_H

#include <QtCore>
#include <X11/Xlib.h>

class ZXEvent{

public:
  virtual bool eventSelect(XEvent*){ return false; };
  virtual void updateValues(QString){ return; };
};

#endif // ZXEVENT_H
