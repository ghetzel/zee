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

#include "zcmformatmodule.h"

ZCMFormatModule::ZCMFormatModule(){}

ZcmResult ZCMFormatModule::prepare(const QDomElement &el){
    ZcmResult rv;

    if(0){
#ifdef ZCM_FORMATTER
    }else if(el.tagName() == ZCM_FORMATTER){
        rv.component = new ZFormatter(el,qApp);
#endif
#ifdef ZCM_TRANSFORMATION
    }else if(el.tagName() == ZCM_TRANSFORMATION){
        rv.component = new ZTransformation(el,qApp);
#endif
    }

    return rv;
}

Q_EXPORT_PLUGIN2(zcm_format, ZCMFormatModule)
