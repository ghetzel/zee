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

#ifndef ZCMSCRIPTMODULE_H
#define ZCMSCRIPTMODULE_H

#include <QtCore>
#include <zcm/zcmplugin.h>
#include <zrubyscript.h>

class ZCMScriptModule : public ZcmPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZcmPluginInterface)

public:
    ZcmResult prepare(const QDomElement &el);
};

#endif // ZCMSCRIPTMODULE_H
