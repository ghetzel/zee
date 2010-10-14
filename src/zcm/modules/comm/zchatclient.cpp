#include "zchatclient.h"

ZChatClient::ZChatClient(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZComponent(el,this)
{
    parse(_config);
    ZChatClient::init();
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
    //purple_eventloop_set_ui_ops(&glib_eventloops);
    //purple_plugins_add_search_path(CUSTOM_PLUGIN_PATH);

    if (!purple_core_init(ZCHAT_UI_NAME)) {
    /*  Initializing the core failed. Terminate. */
        fprintf(stderr,
                "libpurple initialization failed. Dumping core.\n"
                "Please report this!\n");
        abort();
    }

/*  Create and load the buddylist. */
    purple_set_blist(purple_blist_new());
    purple_blist_load();
    purple_prefs_load();
    //purple_plugins_load_saved(PLUGIN_SAVE_PREF);
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

void purple_glib_io_destroy(gpointer data)
{
        g_free(data);
}

gboolean purple_glib_io_invoke(GIOChannel *source, GIOCondition condition,
                               gpointer data)
{
        PurpleGLibIOClosure *closure = (PurpleGLibIOClosure *)data;
        PurpleInputCondition purple_cond = (PurpleInputCondition)0;

        if (condition & PURPLE_GLIB_READ_COND)
                purple_cond |= PURPLE_INPUT_READ;
        if (condition & PURPLE_GLIB_WRITE_COND)
                purple_cond |= PURPLE_INPUT_WRITE;

        closure->function(closure->data, g_io_channel_unix_get_fd(source),
                          purple_cond);

        return TRUE;
}

guint glib_input_add(gint fd, PurpleInputCondition condition, PurpleInputFunction function,
                                                           gpointer data)
{
        PurpleGLibIOClosure *closure = g_new0(PurpleGLibIOClosure, 1);
        GIOChannel *channel;
        GIOCondition cond;

        closure->function = function;
        closure->data = data;

        if (condition & PURPLE_INPUT_READ)
                cond |= PURPLE_GLIB_READ_COND;
        if (condition & PURPLE_INPUT_WRITE)
                cond |= PURPLE_GLIB_WRITE_COND;

        channel = g_io_channel_unix_new(fd);
        closure->result = g_io_add_watch_full(channel, G_PRIORITY_DEFAULT, cond,
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
