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

#ifndef ZCMDATAMODULE_H
#define ZCMDATAMODULE_H

#include <QtCore>
#include <zcm/zcmplugin.h>
#include <zdatabase.h>
#include <zdatamodel.h>

class ZCMDataModule : public ZcmPlugin
{
    Q_OBJECT
    Q_INTERFACES(ZcmPluginInterface)

public:
    ZCMDataModule();
    ZcmResult prepare(const QDomElement &el);
};

#endif // ZCMDATAMODULE_H
