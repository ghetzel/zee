#include "zshortcut.h"

ZShortcut::ZShortcut(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    parse(_config);
}

void ZShortcut::parse(const ZConfig &el){
    if(el.hasAttribute("src")){
        _source = QCAST(QWidget*, zEvent->findObject(el.attribute("src"),true));
        if(_source){
            if(param("value").isValid()){
                _shortcut = new QShortcut(_source);
                _shortcut->setKey(el.attribute("value"));

                connect(_shortcut, SIGNAL(activated()),
                        this, SLOT(_shortcutActivated()));
            }
        }else{
            z_log_error("ZShortcut: Cannot find object '"+
                        el.attribute("src")+"'");
        }
    }
}

void ZShortcut::_shortcutActivated(){
    z_log_debug("ZShortcut: Trigger "+_shortcut->key().toString() + " on " +
                _source->objectName());
    emit triggered();
}
