#ifndef ZCHATCLIENT_H
#define ZCHATCLIENT_H

#define ZCHAT_UI_NAME       "zee"

#include <QObject>
#include <zcomponent.h>
#include <zeventmanager.h>

#include <purple.h>
#include <glib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define PURPLE_GLIB_READ_COND  (G_IO_IN | G_IO_HUP | G_IO_ERR)
#define PURPLE_GLIB_WRITE_COND (G_IO_OUT | G_IO_HUP | G_IO_ERR | G_IO_NVAL)

typedef struct _PurpleGLibIOClosure {
        PurpleInputFunction function;
        guint result;
        gpointer data;
} PurpleGLibIOClosure;

typedef struct
{
        PurpleAccountRequestType type;
        PurpleAccount *account;
        void *ui_handle;
        char *user;
        gpointer userdata;
        PurpleAccountRequestAuthorizationCb auth_cb;
        PurpleAccountRequestAuthorizationCb deny_cb;
        guint ref;
} PurpleAccountRequestInfo;

class ZChatClient : public QObject, public ZComponent
{
    Q_OBJECT
public:
    ZChatClient(const ZConfig &el, QObject *parent=0);

signals:
    void signedOn();
    void signedOff(QString=QString());
    void messageReceived(QDateTime, QString, QString);

public slots:
    void sendMessage(QString);
    void sendMessage(QString,QString);

private: // glib/purple signals
    void _signedOn(PurpleConnection *c);
    void _imMessageReceived(PurpleAccount *acct, char *from, char *message,
                            PurpleConversation *conv, PurpleMessageFlags f);

private: // instance members
    void parse(const ZConfig &el);

private: // static members
    void init();
    void purpleConnect();
    void connectSignals();
};

#endif // ZCHATCLIENT_H
