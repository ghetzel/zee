/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef ZCMCOREMODULE_H
#define ZCMCOREMODULE_H

#include <QtCore>
#include <zcm/zcmplugin.h>
#include <zsetting.h>
#include <ztimer.h>
#include <zcountdown.h>
//#include <zsysteminfo.h>
#include <zexecutor.h>
#include <zshortcut.h>
#include <zsqlquery.h>
#include <zlinuxauthenticator.h>
#include <ztrayicon.h>
#include <znotificationdaemon.h>
#include <znotificationdaemonadaptor.h>

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
