#include "zcharacterdisplay.h"

ZCharacterDisplay::ZCharacterDisplay(const ZConfig &el, QWidget *parent)
    : ZWidget<QFrame>(el,this,parent)
{
    init();
}

void ZCharacterDisplay::init(){
    setLayout(new QHBoxLayout);
    parse(_config);

    updateDisplay();
}

void ZCharacterDisplay::parse(const ZConfig &el){
    if(el.hasAttribute("value"))
        _text = el.attribute("value");
}

void ZCharacterDisplay::updateDisplay(){
    if(!_text.isEmpty()){
        _characters.clear();

        for(int i = 0; i < _text.length(); i++){
            QLabel *l = new QLabel(_text.at(i),this);
            l->setFixedWidth(32);
            l->setFixedHeight(72);
            _characters << l;
        }        
    }
}
