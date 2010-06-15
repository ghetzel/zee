#include "zformmodule.h"

ZFormModule::ZFormModule()
    : ZuiPlugin(){
}

ZuiResult ZFormModule::prepareWidget(const QDomElement &el, QWidget *parent){
    ZuiResult zRes;
    zRes.parent = parent;
    zRes.widget = NULL;

    if(0){
#ifdef ZUI_BUTTON // button: add a button to do things (and stuff!)
    }else if(el.tagName() == ZUI_BUTTON){
        zRes.widget = new ZButton(el, zRes.parent);

#endif // ZUI_BUTTON
#ifdef ZUI_TOGGLEBUTTON // togglebutton: a dual-state persistent button-thing
    }else if(el.tagName() == ZUI_TOGGLEBUTTON){
        zRes.widget = new ZToggleButton(el, zRes.parent);

#endif // ZUI_TOGGLEBUTTON
#ifdef ZUI_LIST // list: generic list box
    }else if(el.tagName() == ZUI_LIST){
	zRes.widget = new ZListWidget(el, zRes.parent);

#endif // ZUI_LIST
#ifdef ZUI_RADIO
    }else if(el.tagName() == ZUI_RADIO){
	if(el.text().isEmpty())
	    zRes.widget = new QRadioButton(zRes.parent);
	else
	    zRes.widget = new QRadioButton(el.text(), zRes.parent);

#endif // ZUI_RADIO
#ifdef ZUI_CHECKBOX
    }else if(el.tagName() == ZUI_CHECKBOX){
	if(el.text().isEmpty())
	    zRes.widget = new QCheckBox(zRes.parent);
	else
	    zRes.widget = new QCheckBox(el.text(), zRes.parent);

#endif // ZUI_CHECKBOX
#ifdef ZUI_INPUT
    }else if(el.tagName() == ZUI_INPUT){
	zRes.widget = new ZTextInput(el,zRes.parent);
#endif // ZUI_INPUT
#ifdef ZUI_SLIDER
    }else if(el.tagName() == ZUI_SLIDER){
	zRes.widget = new ZSlider(el,zRes.parent);
#endif // ZUI_SLIDER
#ifdef ZUI_PROGRESS
    }else if(el.tagName() == ZUI_PROGRESS){
	zRes.widget = new ZProgressBar(el,zRes.parent);
#endif // ZUI_PROGRESS
    }

    return zRes;
}

Q_EXPORT_PLUGIN2(zui_form, ZFormModule)
