#ifndef ZCMMEDIAMODULE_H
#define ZCMMEDIAMODULE_H

#include <QObject>
#include <zutil.h>
#include <zui/zuiutils.h>
#include <zcm/zcmplugin.h>
#include <zaudiomanager.h>
#include <zaudioadaptor.h>
#include <zmetareader.h>

class ZCMMediaModule : public ZcmPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZcmPluginInterface)

public:
    ZCMMediaModule();
    ZcmResult prepare(const QDomElement &el);
};

#endif // ZCMMEDIAMODULE_H
