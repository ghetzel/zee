#ifndef ZCHATCLIENT_H
#define ZCHATCLIENT_H


#include <QObject>
#include <zcomponent.h>
#include <zeventmanager.h>

extern "C"{
    #include <purple.h>
    #include <glib.h>
    #include <signal.h>
    #include <string.h>
    #include <unistd.h>
    #include <stdio.h>
}

#define PURPLE_GLIB_READ_COND  (G_IO_IN | G_IO_HUP | G_IO_ERR)
#define PURPLE_GLIB_WRITE_COND (G_IO_OUT | G_IO_HUP | G_IO_ERR | G_IO_NVAL)

extern "C"
typedef struct _PurpleGLibIOClosure {
        PurpleInputFunction function;
        guint result;
        gpointer data;
} PurpleGLibIOClosure;

extern "C"
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

extern "C"
void purple_glib_io_destroy(gpointer data)
{
        g_free(data);
}

extern "C"
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

extern "C"
guint glib_input_add(gint fd, PurpleInputCondition condition, PurpleInputFunction function,
                                                           gpointer data)
{
        PurpleGLibIOClosure *closure = g_new0(PurpleGLibIOClosure, 1);
        GIOChannel *channel;
        GIOCondition cond;

        closure->function = function;
        closure->data = data;

        if (condition & PURPLE_INPUT_READ)
                cond |= CAST(PurpleInputCondition,PURPLE_GLIB_READ_COND);
        if (condition & PURPLE_INPUT_WRITE)
                cond |= CAST(PurpleInputCondition,PURPLE_GLIB_WRITE_COND);

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

class ZChatClient : public QObject, public ZComponent
{
public:
    ZChatClient(const ZConfig &el, QObject *parent=0);

private:
    void parse(const ZConfig &el);
};

#endif // ZCHATCLIENT_H
