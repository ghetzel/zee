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

#include "zcmcoremodule.h"

ZCMCoreModule::ZCMCoreModule(){}

ZcmResult ZCMCoreModule::prepare(const QDomElement &el){
    ZcmResult rv;

    if(0){
#ifdef ZEE_SETTING
    }else if(el.tagName() == ZEE_SETTING){
        rv.component = new ZSetting(el,qApp);
#endif // ZEE_SETTING
#ifdef ZCM_SHORTCUT
    }else if(el.tagName() == ZCM_SHORTCUT){
        rv.component = new ZShortcut(el,qApp);
#endif // ZCM_SHORTCUT
#ifdef ZEE_TIMER
    }else if(el.tagName() == ZEE_TIMER){
        rv.component = new ZTimer(el,qApp);
#endif // ZEE_TIMER
#ifdef ZCM_COUNTDOWN
    }else if(el.tagName() == ZCM_COUNTDOWN){
        rv.component = new ZCountdown(el,qApp);
#endif
#ifdef ZCM_EXECUTOR
    }else if(el.tagName() == ZCM_EXECUTOR){
        rv.component = new ZExecutor(el,qApp);
#endif // ZCM_EXECUTOR

#ifdef ZCM_SQLQUERY
    }else if(el.tagName() == ZCM_SQLQUERY){
        rv.component = new ZSQLQuery(el,qApp);
#endif // ZCM_SQLQUERY

#ifdef ZEE_SYSTEM_INFO
    }else if(el.tagName() == ZEE_SYSTEM_INFO){
        rv.component = new ZSystemInfo(el,qApp);
#endif // ZEE_SYSTEM_INFO
#ifdef ZCM_DBUS_INTERFACE
    }else if(el.tagName() == ZCM_DBUS_INTERFACE){
        ZDBusInterface *dbi = new ZDBusInterface(el,qApp);
        rv.component = dbi->interface();
#endif
#ifdef ZCM_LINUX_AUTH
    }else if(el.tagName() == ZCM_LINUX_AUTH){
        rv.component = new ZLinuxAuthenticator(el,qApp);
#endif
#ifdef ZCM_TRAYICON
    }else if(el.tagName() == ZCM_TRAYICON){
        rv.component = new ZTrayIcon(el,qApp);
#endif
    }

    return rv;
}

Q_EXPORT_PLUGIN2(zcm_core, ZCMCoreModule)
