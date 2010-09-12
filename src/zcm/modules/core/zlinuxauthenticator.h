#ifndef ZLINUXAUTHENTICATOR_H
#define ZLINUXAUTHENTICATOR_H

#define	ZCM_LINUX_AUTH		"zee:linuxauth"

#define USE_SHADOW_FILE
#define USE_PAM

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>

#ifdef USE_SHADOW_FILE
#include <shadow.h>
#endif

#include <QObject>
#include <QString>

#include <zutil.h>
#include <zeventmanager.h>
#include <zconfigurable.h>

#ifdef USE_PAM
#include <security/pam_appl.h>
#include <security/pam_misc.h>
#endif

class ZLinuxAuthenticator : public QObject, public ZConfigurable
{
    Q_OBJECT

public:
    ZLinuxAuthenticator(const ZConfig &el, QObject *parent=0);

signals:
    void authenticating();
    void granted();
    void denied();

public slots:
    void authenticate(QString,QString);

private:
    void init();
    void parse(const ZConfig &el);

private:
    QString _serviceName;
#ifdef USE_PAM
    pam_handle_t *_pam;
    static int _pamCallback(int num_msg,
			    const struct pam_message **msgm,
			    struct pam_response **response,
			    void *appdata_ptr);
#endif
};

#endif // ZLINUXAUTHENTICATOR_H
