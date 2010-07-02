#include "ztextinput.h"

ZTextInput::ZTextInput(const ZConfig &el, QWidget *parent)
    : QLineEdit(parent),
      ZWidget(el,this)
{
    _lastCursorPosition = 0;
    init();
}

void ZTextInput::init(){
    parse(_config);

    zEvent->registerSignal(this,SIGNAL(returnPressed()));
    zEvent->registerSignal(this,SIGNAL(textChanged(QString)));
    zEvent->registerSignal(this,SIGNAL(textEdited(QString)));
    zEvent->registerSignal(this,SIGNAL(selectionChanged()));
    zEvent->registerSignal(this,SIGNAL(cursorPositionChanged(int,int)));

    connect(this, SIGNAL(cursorPositionChanged(int,int)),
	    this, SLOT(_cursorPosition(int,int)));

    zEvent->registerSlot(this,SLOT(setText(QString)));
    zEvent->registerSlot(this,SLOT(setDisabled(bool)));
    zEvent->registerSlot(this,SLOT(clear()));
    zEvent->registerSlot(this,SLOT(cut()));
    zEvent->registerSlot(this,SLOT(copy()));
    zEvent->registerSlot(this,SLOT(paste()));
    zEvent->registerSlot(this,SLOT(update()));
}

void ZTextInput::parse(const ZConfig &el){
    QString fieldtype = el.attribute("type");

    if(fieldtype == "password"){
	setEchoMode(QLineEdit::Password);
    }

    if(!el.text().isEmpty()) //! default text
	setText(el.text());

    if(el.hasAttribute("disabled") && el.attribute("disabled") == "true") //! disabled
	setDisabled(true);

    if(el.hasAttribute("maxlength")) //! max character length
	setMaxLength(el.attribute("maxlength").toInt());

    if(el.hasAttribute("mask")) //! See QLineEdit#inputMask for mask examples
	setInputMask(el.attribute("mask"));
}


void ZTextInput::_cursorPosition(int o, int){
    _lastCursorPosition = o;
}

int ZTextInput::lastCursorPosition(){
   return _lastCursorPosition;
}
