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

#include "zlocalsystem.h"

ZLocalSystem *ZLocalSystem::_instance = NULL;

ZLocalSystem::ZLocalSystem(){
}

ZLocalSystem::SystemLoad ZLocalSystem::systemLoad(){
    ZLocalSystem::SystemLoad load = {0,0,0};
    return load;
}

qint64 ZLocalSystem::uptime(){
    return 0;
}



ZLocalSystem *ZLocalSystem::instance(){
    if(!_instance)
	_instance = new ZLocalSystem();
    return _instance;
}
