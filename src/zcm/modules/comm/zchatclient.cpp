#include "zchatclient.h"

// init static variables
ZChatClient *ZChatClient::_instance = NULL;
QHash<int,ZTimedSource*> ZChatClient::_timers;
QHash<int,ZSocketSource*> ZChatClient::_sockets;

//==============================================================================
// libpurple Event Loop Callbacks
//  These functions serve as the bridge between internal event operations and
//  the Qt Event Loop.

/*!  zee_timeout_add (analagous to Glib's g_timeout_add)
        Assigns a \a function to be called on a given \a interval, optionally
        supplied with the \a data argument, or NULL

    \returns a unique id for this timeout
*/
static guint zee_timeout_add(guint interval, GSourceFunc function, gpointer data){
    int id = ZChatClient::_timers.count()+1;

    ZTimedSource *o = new ZTimedSource();

    o->setInterval(interval);
    o->setSourceFunc(function, data);
    o->start();

    ZChatClient::_timers.insert(id, o);
    return id;
}

/*! zee_timeout_remove (analagous to Glib's g_source_remove in context of timers)
        Destroys the timer at \a id
*/
static gboolean zee_timeout_remove(guint id){
    //    qDebug() << "REMOVE TIMER " << id;

    if(ZChatClient::_timers.contains(id)){
        ZChatClient::_timers.remove(id);
        return true;
    }

    return false;
}


/*! zee_input_add (analgous to Glib's g_io_add_watch_full)
      Assigns a function \a func to be called when socket \a fd is read or
      written to (depending on the conditions \a cond).  The function will be
      called with the supplied \a user_data, or NULL

      \returns a unique id for this notifier
 */
static guint zee_input_add(int fd, PurpleInputCondition cond,
                           PurpleInputFunction func, gpointer user_data){
    int id = ZChatClient::_sockets.count()+1;
    ZSocketSource *o = new ZSocketSource();

    o->setSourceFunc(func, user_data);

    if(cond & PURPLE_INPUT_READ)
        o->setReadNotify(fd);
    if(cond & PURPLE_INPUT_WRITE)
        o->setWriteNotify(fd);

    ZChatClient::_sockets.insert(id, o);

    return id;
}

/*! zee_timeout_remove (analagous to Glib's g_source_remove in context of sockets)
        Destroys the notifier at \a id
*/
static gboolean zee_input_remove(guint id){
    if(ZChatClient::_sockets.contains(id)){
        ZSocketSource *o = ZChatClient::_sockets.take(id);
        delete o;
        return true;
    }
    return false;
}



//==============================================================================
// libpurple Core UI Callbacks
//  These functions deliver status and notification events from the API core.

static void zee_core_ui_init(void){
    //purple_connections_set_ui_ops(&connection_uiops);
}



//==============================================================================
// libpurple Connection Status UI Callbacks
//  These functions deliver status and notification events related to connecting

static void zee_network_disconnected(void)
{
    z_log_debug("ZChatClient: This machine has been disconnected from the internet");
}

static void zee_report_disconnect_reason(PurpleConnection *gc, PurpleConnectionError reason, const char *text)
{
    PurpleAccount *account = purple_connection_get_account(gc);
    //qDebug("Connection disconnected: \"%s\" (%s)\n  >Error: %d\n  >Reason: %s\n", purple_account_get_username(account), purple_account_get_protocol_id(account), reason, text);
}

static void zee_connect_progress(PurpleConnection *gc,
                                 const char *text,
                                 size_t step,
                                 size_t step_count){

    z_log_debug("ZChatClient: Status "+STR(text));
}


//==============================================================================
// libpurple DNS Resolution Callbacks
//  These functions perform DNS host resolution.


static gboolean zee_dnsquery_resolve_host(PurpleDnsQueryData *query_data,
                                          PurpleDnsQueryResolvedCallback resolved,
                                          PurpleDnsQueryFailedCallback failed){
    z_log_debug("ZChatClient: RESOLVE ADDRESS "+STR(purple_dnsquery_get_host(query_data)));

//  async
//    QHostInfo::lookupHost(QString(purple_dnsquery_get_host(query_data)),
//                          ChatClient::instance(),
//                          SLOT(dnsResolved(QHostInfo)));

//  blocking
    QHostInfo host = QHostInfo::fromName(QString(purple_dnsquery_get_host(query_data)));

//  resolve succeeded
    if(host.error() == QHostInfo::NoError){
    //  host address(es) are stored as a linked list in pairs of
    //  length of address structure/address structure
        GSList *hosts = NULL;

        //  for each resolved address
        foreach(QHostAddress addr, host.addresses()){
        // allocate native socket structure
            struct sockaddr_in sin;

        //  if able to create a network numeric value from the address string...
            if(inet_aton(qstrdup(addr.toString().toAscii().data()), &sin.sin_addr))
            {
                sin.sin_family = AF_INET;                                       // ipv4 address
                sin.sin_port = htons(purple_dnsquery_get_port(query_data));     // use the originating port
                hosts = g_slist_append(hosts, GINT_TO_POINTER(sizeof(sin)));    // append the length of the struct
                hosts = g_slist_append(hosts, g_memdup(&sin, sizeof(sin)));     // append the struct itself
            }

            z_log_debug("ZChatClient: DNS APPENDED ADDRESS = "+STR(inet_ntoa(sin.sin_addr)));
        }

    //  we have successfully resolved a DNS address, inform the caller as such
        resolved(query_data, hosts);

//  resolve failed
    }else{
        failed(query_data, "resolution failed");
        return false;
    }

    return true;
}

static void zee_dnsquery_destroy(PurpleDnsQueryData *query_data){
}


static PurpleCoreUiOps core_uiops =
{
    NULL,                           /* preferences init     */
    NULL,                           /* debug init           */
    zee_core_ui_init,               /* core initialized     */
    NULL,                           /* core quitting        */
    NULL,                           /* get UI info          */
    NULL,                           /* reserved             */
    NULL,                           /* reserved             */
    NULL                            /* reserved             */
};

static PurpleEventLoopUiOps el_uiOps = {
    zee_timeout_add,                /* timeout add          */
    zee_timeout_remove,             /* timeout remove       */
    zee_input_add,                  /* input notifer add    */
    zee_input_remove,               /* input notify remove  */
    NULL,                           /* input_get_error      */
    NULL,                           /* timeout add (seconds)*/
    NULL,                           /* reserved             */
    NULL,                           /* reserved             */
    NULL                            /* reserved             */
};

static PurpleConnectionUiOps connection_uiops =
{
    zee_connect_progress,           /* connect_progress         */
    NULL,                           /* connected                */
    NULL,                           /* disconnected             */
    NULL,                           /* notice                   */
    NULL,                           /* report_disconnect        */
    NULL,                           /* network_connected        */
    zee_network_disconnected,       /* network_disconnected     */
    zee_report_disconnect_reason,   /* report_disconnect_reason */
    NULL,                           /* reserved                 */
    NULL,                           /* reserved                 */
    NULL                            /* reserved                 */
};

static PurpleDnsQueryUiOps dns_uiops = {
    zee_dnsquery_resolve_host,      /* resolve host             */
    zee_dnsquery_destroy,           /* destroy query (cancel?)  */
    NULL,                           /* reserved                 */
    NULL,                           /* reserved                 */
    NULL,                           /* reserved                 */
    NULL                            /* reserved                 */
};


ZChatClient::ZChatClient(const ZConfig &el, QObject *parent)
    : QObject(parent),
    ZComponent(el,this)
{
    _instance = this;

    z_log_debug("ZChatClient: Initializing");
    init();
}

void ZChatClient::parse(const ZConfig &el){
    QDomNodeList els = el.childNodes();

    for(int i = 0; i < els.count(); i++){
        QDomElement acct = els.at(i).toElement();

        if(acct.tagName() == ZCHAT_ACCOUNT){
            if(acct.hasAttribute("username") &&
               acct.hasAttribute("password") &&
               acct.hasAttribute("protocol")){
                _accounts.insert(acct.attribute("username"),
                                 new ZChatAccount(acct.attribute("username"),
                                                  acct.attribute("password"),
                                                  acct.attribute("protocol")));
            }
        }
    }
}

void ZChatClient::init(){
//  library init
    purple_util_set_user_dir("/dev/null");
    purple_debug_set_enabled(true);

    purple_core_set_ui_ops(&core_uiops);
    purple_eventloop_set_ui_ops(&el_uiOps);
    purple_dnsquery_set_ui_ops(&dns_uiops);

    purple_plugins_add_search_path("");

    if(!(_initalized = purple_core_init(ZEE_OBJNAME))){
        z_log_error("ZChatClient: Failed to initialize core, cannot proceed.");
    }else{
        z_log_debug("ZChatClient: libpurple "+STR(purple_core_get_version())+" initialized");
        parse(_config);
        connect();
    }
}

void ZChatClient::connect(){
//  wrapper: this will become ZChatContacts
    purple_set_blist(purple_blist_new());

//  wrapper: this will become ZChatPreferences
    purple_prefs_load();
    purple_plugins_load_saved("/purple/"ZEE_OBJNAME"/plugins/saved");
    purple_pounces_load();

//  connect account(s)
    foreach(ZChatAccount *account, _accounts){
        account->enable();
    }
}

ZChatClient *ZChatClient::instance(){
    Q_ASSERT(_instance);
    return _instance;
}
