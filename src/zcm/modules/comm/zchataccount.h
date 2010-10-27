#ifndef ZCHATACCOUNT_H
#define ZCHATACCOUNT_H

#define ZCHAT_PURPLE_PROTO_TAG      "prpl"

#include <QString>
#include <zutil.h>
#include <libzee/zstring.h>
#include <purple.h>

class ZChatAccount : public QObject
{
    Q_OBJECT
public:
    ZChatAccount();
    ZChatAccount(QString user, QString pass, QString protocol);
    const char *username();
    const char *password();
    const char *protocol();
    PurpleAccount *account();

public slots:
    void setUsername(QString user);
    void setPassword(QString pass);
    void setProtocol(QString protocol);
    void enable();
    void disable();
    void setState(bool);

private:
    void checkAndSetAccount();

private:
    QString _username;
    QString _password;
    QString _protocol;
    PurpleAccount *_account;
};

#endif // ZCHATACCOUNT_H
