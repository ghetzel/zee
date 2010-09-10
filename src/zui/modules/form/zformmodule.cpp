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

#include "zformmodule.h"

ZFormModule::ZFormModule()
    : ZuiPlugin(){
}

ZuiResult ZFormModule::prepareWidget(const QDomElement &el, QWidget *parent){
    ZuiResult zRes;
    zRes.parent = parent;
    zRes.widget = NULL;

    if(0){
#ifdef ZUI_FRAME
    }else if(el.tagName() == ZUI_FRAME){
	zRes.widget = new ZFrame(el,zRes.parent);
#endif
#ifdef ZUI_BUTTON // button: add a button to do things (and stuff!)
    }else if(el.tagName() == ZUI_BUTTON){
	zRes.widget = new ZButton(el, zRes.parent);
#endif
#ifdef ZUI_TOGGLEBUTTON // togglebutton: a dual-state persistent button-thing
    }else if(el.tagName() == ZUI_TOGGLEBUTTON){
	zRes.widget = new ZToggleButton(el, zRes.parent);
#endif
#ifdef ZUI_LIST // list: generic list box
    }else if(el.tagName() == ZUI_LIST){
	zRes.widget = new ZListWidget(el, zRes.parent);
#endif
#ifdef ZUI_TABLE
    }else if(el.tagName() == ZUI_TABLE){
	zRes.widget = new ZTableView(el,zRes.parent);
#endif
#ifdef ZUI_RADIO
    }else if(el.tagName() == ZUI_RADIO){
	zRes.widget = new ZRadioButton(el,zRes.parent);
#endif
#ifdef ZUI_CHECKBOX
    }else if(el.tagName() == ZUI_CHECKBOX){
	if(el.text().isEmpty())
	    zRes.widget = new QCheckBox(zRes.parent);
	else
	    zRes.widget = new QCheckBox(el.text(), zRes.parent);
#endif
#ifdef ZUI_INPUT
    }else if(el.tagName() == ZUI_INPUT){
	zRes.widget = new ZTextInput(el,zRes.parent);
#endif
#ifdef ZUI_SLIDER
    }else if(el.tagName() == ZUI_SLIDER){
	zRes.widget = new ZSlider(el,zRes.parent);
#endif
#ifdef ZUI_PROGRESS
    }else if(el.tagName() == ZUI_PROGRESS){
	zRes.widget = new ZProgressBar(el,zRes.parent);
#endif
    }

    return zRes;
}

Q_EXPORT_PLUGIN2(zui_form, ZFormModule)
