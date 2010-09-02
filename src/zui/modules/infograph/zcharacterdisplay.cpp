#include "zcharacterdisplay.h"

ZCharacterDisplay::ZCharacterDisplay(const ZConfig &el, QWidget *parent)
    : ZWidget<QFrame>(el,this,parent)
{
    init();
}

void ZCharacterDisplay::init(){
    setLayout(new ZFlowLayout);
    layout()->setSpacing(0);
    parse(_config);
    zEvent->registerSlot(this, SLOT(updateDisplay()));
    zEvent->registerSlot(this, SLOT(setText(QString)));
}

void ZCharacterDisplay::parse(const ZConfig &el){
    if(el.hasAttribute("value"))
        setText(el.attribute("value"));
    if(el.hasAttribute("images"))
        _charImagePath = el.attribute("images");
}

void ZCharacterDisplay::updateDisplay(){
    if(!_text.isEmpty()){
        if(_text.length() > _characters.length()){
            for(int i = _characters.length(); i < _text.length(); i++){
                addCharacter();
            }
        }

        for(int i = 0; i < _text.length(); i++){
            if(_characters[i]){
                if(_charImagePath.isEmpty()){
                    _characters[i]->setText(_text.at(i));
                }else{
                    _characters[i]->setPixmap(
                            QPixmap(_charImagePath.arg(_text.at(i))));
                }
            }
        }        
    }
}

void ZCharacterDisplay::addCharacter(){
    QLabel *l = new QLabel("",this);
    l->setFixedWidth(54);
    l->setFixedHeight(72);
    l->setAlignment(Qt::AlignCenter);
    _characters << l;
    layout()->addWidget(l);
}

void ZCharacterDisplay::setText(QString text){
    _text = text;
    updateDisplay();
}
