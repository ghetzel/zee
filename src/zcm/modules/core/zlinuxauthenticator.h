#ifndef ZLINUXAUTHENTICATOR_H
#define ZLINUXAUTHENTICATOR_H

#define	ZCM_LINUX_AUTH		"zee:linuxauth"

#define USE_SHADOW_FILE

#include <shadow.h>
#include <sys/types.h>
#include <pwd.h>
#include <QObject>
#include <QString>
#include <zutil.h>
#include <zeventmanager.h>
#include <zconfigurable.h>

class ZLinuxAuthenticator : public QObject, public ZConfigurable
{
    Q_OBJECT

public:
    ZLinuxAuthenticator(const ZConfig &el, QObject *parent=0);

signals:
    void granted();
    void denied();

public slots:
    void authenticate(QString,QString);

private:
    void init();
    void parse(const ZConfig &el);
};

#endif // ZLINUXAUTHENTICATOR_H
