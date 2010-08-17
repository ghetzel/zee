#include "zterminal.h"

ZTerminal::ZTerminal(const ZConfig &el, QWidget *parent)
    : ZWidget<QFrame>(el,this,parent)
{
    init();
}

void ZTerminal::init(){
    _display = new TerminalDisplay(this);
    _session = new Session();
    parse(_config);
    setLayout(new QHBoxLayout);
    layout()->addWidget(_display);
    _session->run();

    setFocus(Qt::OtherFocusReason);
    setFocusProxy(_display);
}

void ZTerminal::parse(const ZConfig &el){
    QString defshell(ZTERM_DEFAULT_SHELL);

    if(defshell.at(0) == '$')
        defshell = QVariant(getenv(ZTERM_DEFAULT_SHELL)).toString();

    z_log_debug("ZTerminal: Shell = "+defshell);

    if(el.hasAttribute("shell")){
        _session->setProgram(el.attribute("shell"));
    }else if(!defshell.isEmpty()){
        _session->setProgram(defshell);
    }else{
        _session->setProgram(ZTERM_FALLBACK_SHELL);
    }

    _session->setAutoClose(true);
    _session->setCodec(QTextCodec::codecForName(ZTERM_DEFAULT_CODEC));
    _session->setFlowControlEnabled(true);
    _session->setHistoryType(HistoryTypeBuffer(ZTERM_DEFAULT_SCROLLBACK));
    _session->setKeyBindings("");
    _session->setDarkBackground(true);
    _session->setArguments(QStringList(""));

    _display->setScrollBarPosition(TerminalDisplay::NoScrollBar);
    _display->setBellMode(TerminalDisplay::NotifyBell);
    _display->setTerminalSizeHint(true);
    _display->setTripleClickMode(TerminalDisplay::SelectWholeLine);
    _display->setTerminalSizeStartup(true);
    _display->setRandomSeed(_session->sessionId()*31);
    _display->setFont(font());
}
