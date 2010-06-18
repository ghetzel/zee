#ifndef ZEEADAPTOR_H
#define ZEEADAPTOR_H

#include <zdbusabstractadaptor.h>
#include <zee.h>

class ZeeAdaptor : public ZDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "net.gammazeta.zee.Zee")

public:
    ZeeAdaptor(Zee *parent);
    ZeeAdaptor(QString name, Zee *parent);

public slots:
    void reloadStyleSheet();
    void log(QString);
    void logWarning(QString);
    void logError(QString);
    void logCritical(QString);
    void logDebug(QString);

signals:
    void styleReloaded();

private:
    void init();
    Zee *instance();
};

#endif // ZEEADAPTOR_H
