#include "zsqlquery.h"

ZSQLQuery::ZSQLQuery(const ZConfig &el, QObject *parent)
    : QSqlQueryModel(parent),
      ZConfigurable(el,this)
{
    //zEvent->registerSignal(this, SIGNAL(queryChanged()));
    zEvent->registerSignal(this, SIGNAL(queryChanged(QString)));
    zEvent->registerSlot(this, SLOT(execute()));
    zEvent->registerSlot(this, SLOT(setQuery(QString)));

    parse(_config);
}

ZSQLQuery::~ZSQLQuery(){
    if(_conn.isOpen())
        _conn.close();
    QSqlDatabase::removeDatabase(_conn.connectionName());
}

void ZSQLQuery::parse(const ZConfig &el){
    if(param("query").isValid()){
        if(1==2 && el.hasAttribute("connection")){
    //        _conn = QCAST(QSqlDatabase*,
    //                            zEvent->findObject(el.attribute("connection")));
    //        if(!_conn){
    //            z_log_error("ZSQLQuery: Connection '"+el.attribute("connection")+
    //                        "' not found or is not a database connection.");
    //        }else if(!_conn->isValid()){
    //            z_log_error("ZSQLQuery: Connection '"+el.attribute("connection")+
    //                        "' is invalid.");
    //        }

            return;
        }else if(el.hasAttribute("type")){
            if(param("username").isValid()){
                if(el.hasAttribute("name"))
                    _conn = QSqlDatabase::addDatabase(el.attribute("type"),
                                                       el.attribute("name"));
                else
                    _conn = QSqlDatabase::addDatabase(el.attribute("type"));

                _conn.setHostName(param("hostname").toString());
                _conn.setUserName(param("username").toString());
                _conn.setPassword(param("password").toString());
                _conn.setDatabaseName(param("database").toString());
            }
        }

        if(_conn.open())
            z_log_debug("ZSQLQuery: Connection Established '"+
                        _conn.userName()+"@"+_conn.hostName()+
                        ":"+_conn.databaseName());
        else
            z_log_error("ZSQLQuery: Connection Error: "+_conn.lastError().databaseText());

        setQuery(param("query").toString());

    }else{
        z_log_error("ZSQLQuery: No query specified");
    }
}

void ZSQLQuery::execute(){
    if(_conn.isOpen()){
        if(query().isValid()){
            z_log_debug("ZSQLQuery: Executing");
            query().exec();
        }
    }
}

void ZSQLQuery::setQuery(QString q){
    if(_conn.isOpen()){
        z_log_debug("ZSQLQuery: Changing query: "+q);
        QSqlQueryModel::setQuery(q, _conn);
        emit queryChanged(query().lastQuery());
    }
}
