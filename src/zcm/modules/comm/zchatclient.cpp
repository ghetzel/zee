#include "zchatclient.h"

void purple_glib_io_destroy(gpointer data)
{
        g_free(data);
}

gboolean purple_glib_io_invoke(GIOChannel *source, GIOCondition condition,
                               gpointer data)
{
        PurpleGLibIOClosure *closure = (PurpleGLibIOClosure *)data;
        int purple_cond = 0;

        if (condition & PURPLE_GLIB_READ_COND)
                purple_cond |= PURPLE_INPUT_READ;
        if (condition & PURPLE_GLIB_WRITE_COND)
                purple_cond |= PURPLE_INPUT_WRITE;

        closure->function(closure->data, g_io_channel_unix_get_fd(source),
                          (PurpleInputCondition)purple_cond);

        return true;
}

guint glib_input_add(gint fd, PurpleInputCondition condition, PurpleInputFunction function,
                                                           gpointer data)
{
        PurpleGLibIOClosure *closure = g_new0(PurpleGLibIOClosure, 1);
        GIOChannel *channel;
        int cond;

        closure->function = function;
        closure->data = data;

        if (condition & PURPLE_INPUT_READ)
                cond |= PURPLE_GLIB_READ_COND;
        if (condition & PURPLE_INPUT_WRITE)
                cond |= PURPLE_GLIB_WRITE_COND;

        channel = g_io_channel_unix_new(fd);
        closure->result = g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, (GIOCondition)cond,
                                              purple_glib_io_invoke, closure, purple_glib_io_destroy);

        g_io_channel_unref(channel);
        return closure->result;
}

static PurpleEventLoopUiOps glib_eventloops =
{
        g_timeout_add,
        g_source_remove,
        glib_input_add,
        g_source_remove,
        NULL,
#if GLIB_CHECK_VERSION(2,14,0)
        g_timeout_add_seconds,
#else
        NULL,
#endif

        /* padding */
        NULL,
        NULL,
        NULL
};

ZChatClient::ZChatClient(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZComponent(el,this)
{
    z_log_debug("ZChatClient: Init");
    parse(_config);
    _gLibMainLoop = g_main_loop_new(NULL, false);
    init();

    _account = purple_account_new("crazysexybabyxox", "prpl-aim");
    purple_account_set_password(_account, "ncc74656");
    purple_accounts_add(_account);
    purple_account_set_enabled(_account, ZCHAT_UI_NAME, true);
    g_main_loop_run(_gLibMainLoop);
}

void ZChatClient::parse(const ZConfig &el){

}

void ZChatClient::init(){

//  initialize the purple libs and connect
    purpleConnect();

//  make connections to GLib/Purple signals
    connectSignals();
}

void ZChatClient::purpleConnect(){
    purple_util_set_user_dir("/dev/null");
    purple_debug_set_enabled(true);
    //purple_core_set_ui_ops(&core_uiops);
    purple_eventloop_set_ui_ops(&glib_eventloops);
    purple_plugins_add_search_path("");

    if (!purple_core_init(ZCHAT_UI_NAME)) {
        z_log_error("ZChatClient: libpurple initialization failed.");
        abort();
    }

/*  Create and load the buddylist. */
    purple_set_blist(purple_blist_new());
    purple_blist_load();
    purple_prefs_load();
    purple_plugins_load_saved("/purple/user/plugins/saved");
    purple_pounces_load();
}

void ZChatClient::connectSignals(){
    purple_signal_connect(purple_connections_get_handle(),  "signed-on",
                          this, PURPLE_CALLBACK(&ZChatClient::_signedOn), NULL);

    purple_signal_connect(purple_connections_get_handle(),  "received-im-msg",
                          this, PURPLE_CALLBACK(&ZChatClient::_imMessageReceived), NULL);
}


void ZChatClient::_signedOn(PurpleConnection *c){
    PurpleAccount *acct = purple_connection_get_account(c);
    z_log("ZChatClient: Account signed-on: "+STR(purple_account_get_username(acct)));
    emit signedOn();
}

void ZChatClient::_imMessageReceived(PurpleAccount *acct, char *from,
                                     char *message, PurpleConversation *conv,
                                     PurpleMessageFlags f)
{
    if(!conv)
        conv = purple_conversation_new(PURPLE_CONV_TYPE_IM, acct, from);

    //emit messageReceived();
}
