#ifndef ZTERMINAL_H
#define ZTERMINAL_H

#define ZUI_TERMINAL            "zui:terminal"

#define ZTERM_DEFAULT_SHELL         "$SHELL"
#define ZTERM_FALLBACK_SHELL        "/bin/sh"
#define ZTERM_DEFAULT_CODEC         "UTF-8"
#define ZTERM_DEFAULT_SCROLLBACK    1000

#include <QObject>
#include <zwidget.h>
#include <zeventmanager.h>
#include <konsole/Session.h>
#include <konsole/TerminalDisplay.h>

using namespace Konsole;

class ZTerminal : public ZWidget<QFrame>
{
public:
    ZTerminal(const ZConfig &el, QWidget *parent=0);

private:
    void init();
    void parse(const ZConfig &el);

private:
    TerminalDisplay *_display;
    Session *_session;
};

#endif // ZTERMINAL_H
