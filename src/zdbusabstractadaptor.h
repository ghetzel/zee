#ifndef ZDBUSABSTRACTADAPTOR_H
#define ZDBUSABSTRACTADAPTOR_H

#define ZDBUS_SVCNM   "net.gammazeta.zee"
#define ZDBUS_OPATH   "/net/gammazeta/zee/"

#include <QDBusAbstractAdaptor>
#include <QDBusConnection>
#include <zutil.h>

class ZDBusAbstractAdaptor : public QDBusAbstractAdaptor
{
public:
    ZDBusAbstractAdaptor(QObject *parent);
    ZDBusAbstractAdaptor(QString name, QObject *parent);
    void setInstance(QObject *instance);
    void registerService();

protected:
    void init();
    virtual QObject *instance(){ return _instance; };

private:
    QString _name;
    QObject *_instance;
};

#endif // ZDBUSABSTRACTADAPTOR_H
