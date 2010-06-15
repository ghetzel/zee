#ifndef ZEVENT_
#define ZEVENT_

#include <QObject>
#include <QString>
#include <QVariant>

/*!
  \class ZEvent
  \ingroup zeeapp
  \brief An interface for objects the utilize the Zee event system.

*/

class ZEvent
{
  public:
    virtual bool invoke(QString action,
                        QString arg1="",QString arg2="",QString arg3="",
                        QString arg4="",QString arg5="",QString arg6="") =0;
    virtual QVariant query(QString property){ return QVariant(); };
};

#endif
