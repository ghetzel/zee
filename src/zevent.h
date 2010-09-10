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

#ifndef ZEVENT_
#define ZEVENT_

#include <QObject>
#include <QString>
#include <QVariant>

/*!
  \class ZEvent
  \ingroup zeeapp
  \brief An interface for objects the utilize the Zee event system.

*/

class ZEvent
{
  public:
    virtual bool invoke(QString action,
			QString arg1="",QString arg2="",QString arg3="",
			QString arg4="",QString arg5="",QString arg6="") =0;
};

#endif
