#ifndef ZTIMEDSOURCE_H
#define ZTIMEDSOURCE_H

#include <glib.h>
#include <QTimer>
#include <QtDebug>

class ZTimedSource : public QObject
{
    Q_OBJECT
public:
    ZTimedSource(QObject *parent=0);
    ~ZTimedSource();
    void setSourceFunc(GSourceFunc func, gpointer data);
    void setInterval(int msec);
    void setIntervalSec(int sec);

public slots:
    void start();
    void stop();

private slots:
    void timeout();

private:
    QTimer *_timer;
    GSourceFunc _func;
    gpointer _data;

};

#endif // ZTIMEDSOURCE_H
