#ifndef ZSOCKETSOURCE_H
#define ZSOCKETSOURCE_H

#include <QtDebug>
#include <QSocketNotifier>
#include <glib.h>
#include <purple.h>

class ZSocketSource : public QObject
{
    Q_OBJECT
public:
    ZSocketSource(QObject *parent=0);
    ~ZSocketSource();
    void setReadNotify(guint fd);
    void setWriteNotify(guint fd);
    void setSourceFunc(PurpleInputFunction func, gpointer data);
    int socket();

private slots:
    void socketRead(int fd);
    void socketWritten(int fd);

private:
    PurpleInputCondition purpleInputCondition();

private:
    QSocketNotifier *_readNotifier;
    QSocketNotifier *_writeNotifier;
    int _fileDescriptor;
    PurpleInputFunction _func;
    gpointer _data;
};

#endif // ZSOCKETSOURCE_H
