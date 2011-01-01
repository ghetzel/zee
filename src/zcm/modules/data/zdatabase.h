#ifndef ZDATABASE_H
#define ZDATABASE_H


#define ZCM_DATABASE        "zee:database"

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZDatabase : public QObject, public ZConfigurable
{
    Q_OBJECT

public:
    ZDatabase(const ZConfig &el, QObject *parent=0);
    void parse(const ZConfig &el);
    QSqlDatabase &connection();

public slots:
    void open();
    void close();
    void setConnectionName(QString);
    void setDriver(QString);
    void setHost(QString,int=-1);
    void setUsername(QString);
    void setPassword(QString);
    void setCredentials(QString,QString=QString());
    void setDatabase(QString);

private slots:
    void setupConnection(QString,QString=QString());

private:
    enum ZDatabaseProperties {
        Driver,
        Hostname,
        Port,
        HostnamePort,
        Username,
        Password,
        UsernamePassword,
        DefaultDatabase,
        ConnectionName
    };

    void init();
    void setDatabaseProperty(ZDatabaseProperties property, QVariant value);

private:
    QSqlDatabase _database;
    QString _connectionName;
    QString _driver;
    QString _username;
    QString _password;
    QString _defaultDatabase;
    bool _autoconnect;
};

#endif // ZDATABASE_H
