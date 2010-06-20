#ifndef ZAUDIOADAPTOR_H
#define ZAUDIOADAPTOR_H

#include <zdbusabstractadaptor.h>
#include <zaudiomanager.h>

class ZAudioAdaptor : public ZDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "net.gammazeta.zee.AudioManager")

public:
    ZAudioAdaptor(ZAudioManager *parent);
    ZAudioAdaptor(QString name, ZAudioManager *parent);

public slots:
    void play();
    void playSource(QString);
    void pause();
    void togglePlay();
    void stop();
    void next();
    void previous();
    void enqueue(QString);

signals:
    void playing();
    void paused();
    void stopped();
    void loading();
    void buffering();
    void error();

private:
    void init();
    ZAudioManager *instance();
    void _stateHandler(ZAudioManager::ZAudioState state);

private:
    ZAudioManager *_instance;
    QString _name;
};

#endif // ZAUDIOADAPTOR_H
