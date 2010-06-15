#include "ztogglebutton.h"

ZToggleButton::ZToggleButton(const ZConfig &el, QWidget *parent)
    : ZButton(el, parent)
{
    init();
}

ZToggleButton::ZToggleButton(const QString &text, const ZConfig &el, QWidget *parent)
    : ZButton(text, el, parent)
{
    init();
}

ZToggleButton::ZToggleButton(const QIcon &icon, const QString &text, const ZConfig &el, QWidget *parent)
    : ZButton(icon, text, el, parent)
{
    init();
}

void ZToggleButton::init(){
    setCheckable(true);
    parse(_config);

    connect(this, SIGNAL(toggled(bool)), this, SLOT(_toggled(bool)));

    zEvent->registerSignal(this, SIGNAL(checked()));
    zEvent->registerSignal(this, SIGNAL(unchecked()));
    zEvent->registerSignal(this, SIGNAL(toggled(bool)));
    zEvent->registerSlot(this, SLOT(check()));
    zEvent->registerSlot(this, SLOT(uncheck()));
    zEvent->registerSlot(this, SLOT(toggle()));
}


void ZToggleButton::parse(const ZConfig &el){
    if(el.hasAttribute("value2"))
        _otherLabel = el.attribute("value2");
}

void ZToggleButton::check(){
    emit toggled(true);
}

void ZToggleButton::uncheck(){
    emit toggled(false);
}

void ZToggleButton::toggle(){
    if(isChecked())
        uncheck();
    else
        check();
}

void ZToggleButton::toggleLabel(){
    QString t = text();
    setText(_otherLabel);
    _otherLabel = t;
}

void ZToggleButton::_toggled(bool on){
    if(on){
        emit checked();
    }else{
        emit unchecked();
    }
    toggleLabel();
}
