#ifndef ZLOCALSYSTEM_H
#define ZLOCALSYSTEM_H

#include <QObject>
#include <QDateTime>

class ZLocalSystem
{
// variables / structures
public:
    struct SystemLoad{
        double Average1;
        double Average5;
        double Average15;
    };

public:
    ZLocalSystem();
    virtual QDateTime systemTime();
    virtual qint64 systemTimeEpoch();
    virtual qint64 uptime();
    virtual ZLocalSystem::SystemLoad systemLoad();

// static members
public:
    static ZLocalSystem *instance();

private:
    static ZLocalSystem *_instance;
};

#endif // ZLOCALSYSTEM_H
