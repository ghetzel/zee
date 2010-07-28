#ifndef ZCMCOREMODULE_H
#define ZCMCOREMODULE_H

#include <QtCore>
#include <zcm/zcmplugin.h>
#include <zsetting.h>
#include <ztimer.h>
#include <zsysteminfo.h>
#include <zexecutor.h>
#include <zshortcut.h>
#include <zsqlquery.h>

#ifdef Q_OS_LINUX
#include "zdbusinterface.h"
#endif

class ZCMCoreModule : public ZcmPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZcmPluginInterface)

public:
    ZCMCoreModule();
    ZcmResult prepare(const QDomElement &el);
};

#endif // ZCMCOREMODULE_H
