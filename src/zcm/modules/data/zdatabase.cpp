#include "zdatabase.h"

ZDatabase::ZDatabase(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    parse(_config);
    init();
}

void ZDatabase::init(){
    zEvent->registerSlot(this, SLOT(connect()));
}

void ZDatabase::parse(const ZConfig &el){
    if(param("host").isValid()){
        if(param("name").isValid())
            _connectionName = param("name").toString();
        else
            _connectionName = objectName();

    //  set the driver, and since _connectionName is already set, that will get
    //  used and the connection will be setup automatically...YAY!
        setDriver(el.attribute("driver"));

    //  set host[:port]
        setHost(param("host").toString(), param("port").toInt());

    //  username
        if(param("username").isValid())
            setUsername(param("username").toString());

    //  password
        if(param("password").isValid())
            setPassword(param("password").toString());

    //  database name
        if(param("database").isValid())
            setDatabase(param("database").toString());

    //  autoconnect?
        if(param("autoconnect").isValid() && param("autoconnect").toBool()){
            _autoconnect = true;
            open();
        }
    }
}

QSqlDatabase &ZDatabase::connection(){
    return _database;
}

void ZDatabase::open(){
    _database.open();
}

void ZDatabase::close(){
    _database.close();
}

void ZDatabase::setupConnection(QString driver, QString connectionName){
    if(_database.isOpen())
        _database.close();

    _database.removeDatabase(connectionName);
    _database = QSqlDatabase::addDatabase(driver, connectionName);
}

void ZDatabase::setDatabaseProperty(ZDatabaseProperties property, QVariant value){
    bool reopen = false;
    if((reopen = _database.isOpen())){
        z_log_debug("ZDatabase: Database was open, closing...");
        _database.close();
    }

    z_log_debug("ZDatabase: Setting property: "+value.toString());

    switch(property){
    case Driver:
        setDriver(value.toString());
        break;
    case ConnectionName:
        setConnectionName(value.toString());
        break;
    case Hostname:
        _database.setHostName(value.toString());
        break;
    case Port:
        _database.setPort(value.toInt());
        break;
    case HostnamePort:
        _database.setHostName(value.toString().section(":",0,0));
        _database.setPort(value.toString().section(":",1,1).toInt());
        break;
    case Username:
        _database.setUserName(value.toString());
        break;
    case Password:
        _database.setPassword(value.toString());
        break;
    case DefaultDatabase:
        _database.setDatabaseName(value.toString());
        break;
    }

    if(reopen || _autoconnect){
        if(reopen)
            z_log_debug("ZDatabase: Reopening database...");
        else
            z_log_debug("ZDatabase: Auto-connecting database");

        _database.open();
    }
}

void ZDatabase::setConnectionName(QString value){
    _connectionName = value;
    setupConnection(_driver, _connectionName);
}

void ZDatabase::setDriver(QString value){
    _driver = "Q"+value.toUpper();
    setupConnection(_driver, _connectionName);
}

void ZDatabase::setHost(QString hostname, int port){
    if(port > 0)
        setDatabaseProperty(HostnamePort, hostname+":"+STR(port));
    else
        setDatabaseProperty(Hostname, hostname);
}

void ZDatabase::setUsername(QString value){
    setDatabaseProperty(Username, value);
}

void ZDatabase::setPassword(QString value){
    setDatabaseProperty(Password, value);
}

void ZDatabase::setCredentials(QString username, QString password){
    setUsername(username);
    setPassword(password);
}

void ZDatabase::setDatabase(QString value){
    setDatabaseProperty(DefaultDatabase, value);
}
