#ifndef ZLINUXFILENOTIFIER_H
#define ZLINUXFILENOTIFIER_H

#include <cstdio>
#include <sys/inotify.h>
#include <QtCore>
#include <zfilenotifier.h>

class ZLinuxFileNotifier : public ZFileNotifier
{
public:
    ZLinuxFileNotifier();
    bool watch(QString path, uchar events, bool once=false);

private:
    int _descriptor;
    bool _ok;
};

#endif // ZLINUXFILENOTIFIER_H
