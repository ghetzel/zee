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

#include "zcmmediamodule.h"

ZCMMediaModule::ZCMMediaModule(){
    ZuiUtils::initialize();
}

ZcmResult ZCMMediaModule::prepare(const QDomElement &el){
    ZcmResult rv = {NULL};

    if(0){
#ifdef ZEE_AUDIO
    }else if(el.tagName() == ZEE_AUDIO){
	ZAudioManager *c = new ZAudioManager(el,qApp);
        if(ZuiUtils::attributeTrue(el.attribute("remote")))
	    c->setAdaptor(new ZAudioAdaptor(c));
	rv.component = c;
#endif // ZEE_AUDIO
#ifdef ZCM_METAREADER
    }else if(el.tagName() == ZCM_METAREADER){
	rv.component = new ZMetaReader(el,qApp);

#endif // ZCM_METAREADER
    }

    return rv;
}

Q_EXPORT_PLUGIN2(zcm_media, ZCMMediaModule)
