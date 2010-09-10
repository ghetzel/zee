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
