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
