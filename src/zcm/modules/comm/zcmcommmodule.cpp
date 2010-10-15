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

#include "zcmcommmodule.h"

ZcmResult ZCMCommModule::prepare(const QDomElement &el){
    ZcmResult rv;

    if(0){
#ifdef ZCM_CHAT
    }else if(el.tagName() == ZCM_CHAT){
        rv.component = new ZChatClient(el,qApp);
#endif
    }

    return rv;
}

Q_EXPORT_PLUGIN2(zcm_comm, ZCMCommModule)
