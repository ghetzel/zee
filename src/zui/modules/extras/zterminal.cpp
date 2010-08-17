#include "zterminal.h"

ZTerminal::ZTerminal(const ZConfig &el, QWidget *parent)
    : ZWidget<QFrame>(el,this,parent)
{
    init();
}

void ZTerminal::init(){
    zEvent->registerSignal(this, SIGNAL(finished()));

    setLayout(new QHBoxLayout);
    _terminal = new QTermWidget(1, this);

    QFont f = font();
    f.setFamily(ZTERM_DEFAULT_FONT_FAMILY);
    f.setFixedPitch(true);
    if(f.fixedPitch())
        _terminal->setTerminalFont(f);

    connect(_terminal, SIGNAL(finished()),
            this, SIGNAL(finished()));

    parse(_config);

    layout()->setContentsMargins(0,0,0,0);
    layout()->addWidget(_terminal);
}

void ZTerminal::parse(const ZConfig &el){
}
