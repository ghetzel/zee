#ifndef ZCHATCLIENT_H
#define ZCHATCLIENT_H

#define ZCM_CHAT            "zee:chatclient"
#define ZCHAT_ACCOUNT       "zee:chataccount"

#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <purple.h>
#include <glib.h>

#include <QObject>
#include <QHostInfo>
#include <zcomponent.h>
#include <zeventmanager.h>
#include <ztimedsource.h>
#include <zsocketsource.h>
#include <zchataccount.h>


class ZChatClient : public QObject, public ZComponent
{
    Q_OBJECT
public:
    ZChatClient(const ZConfig &el, QObject *parent=0);

public:
    static ZChatClient *instance();

signals:
    void signedOn();
    void signedOff(QString=QString());
    void messageReceived(QDateTime, QString, QString);

public slots:
    void sendMessage(QString);
    void sendMessage(QString,QString);

private: // purple signals
    void _signedOn(PurpleConnection *c);
    void _imMessageReceived(PurpleAccount *acct, char *from, char *message,
                            PurpleConversation *conv, PurpleMessageFlags f);

private: // instance members
    void parse(const ZConfig &el);

private:
    void init();
    void connect();

private:
    bool _initalized;
    QHash<QString,ZChatAccount*> _accounts;

private: // static variables
    static ZChatClient *_instance;
    static QHash<int,ZTimedSource*> _timers;
    static QHash<int,ZSocketSource*> _sockets;
};

#endif // ZCHATCLIENT_H
