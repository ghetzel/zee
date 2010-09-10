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

#include "zinfographmodule.h"

ZuiResult ZInfographModule::prepareWidget(const QDomElement &el,
					  QWidget *parent){

  ZuiResult zRes;
  zRes.parent = parent;
  zRes.widget = NULL;

  if(0){
#ifdef ZUI_GAUGE
  }else if(el.tagName() == ZUI_GAUGE){
    zRes.widget = new ZGauge(el,zRes.parent);
#endif // ZUI_GAUGE
#ifdef ZUI_PIEGAUGE
  }else if(el.tagName() == ZUI_PIEGAUGE){
    zRes.widget = new ZPieGauge(el,zRes.parent);
#endif // ZUI_PIEGAUGE
#ifdef ZUI_CHARACTER_DISPLAY
  }else if(el.tagName() == ZUI_CHARACTER_DISPLAY){
    zRes.widget = new ZCharacterDisplay(el,zRes.parent);
#endif // ZUI_CHARACTER_DISPLAY
  }

  return zRes;
}



Q_EXPORT_PLUGIN2(zui_infograph, ZInfographModule)
