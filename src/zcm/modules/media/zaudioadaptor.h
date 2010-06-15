#ifndef ZAUDIOADAPTOR_H
#define ZAUDIOADAPTOR_H

#define ZAUDIO_DBUS_SVCNM   "net.gammazeta.zee"
#define ZAUDIO_DBUS_OPATH   "/net/gammazeta/zee/"
#define ZAUDIO_DBUS_NAME    "AudioManager"

#include <QDBusAbstractAdaptor>
#include <QDBusConnection>
#include <zaudiomanager.h>

class ZAudioAdaptor : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "net.gammazeta.zee.AudioManager")

public:
    ZAudioAdaptor(ZAudioManager *parent);
    ZAudioAdaptor(QString name, ZAudioManager *parent);

public slots:
    void play();
    void pause();
    void togglePlay();
    void stop();
    void next();
    void previous();

signals:
    void playing();
    void paused();
    void stopped();
    void loading();
    void buffering();
    void error();

private:
    void init();
    void _stateHandler(ZAudioManager::ZAudioState state);

private:
    ZAudioManager *_instance;
    QString _name;
};

#endif // ZAUDIOADAPTOR_H
