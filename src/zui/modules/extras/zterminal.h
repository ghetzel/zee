#ifndef ZTERMINAL_H
#define ZTERMINAL_H

#define ZUI_TERMINAL            "zui:terminal"

#define ZTERM_DEFAULT_SHELL         "$SHELL"
#define ZTERM_FALLBACK_SHELL        "/bin/sh"
#define ZTERM_DEFAULT_CODEC         "UTF-8"
#define ZTERM_DEFAULT_SCROLLBACK    1000
#define ZTERM_DEFAULT_FONT_FAMILY   "Monospace"

#include <QObject>
#include <qtermwidget/qtermwidget.h>
#include <zwidget.h>
#include <zeventmanager.h>

class ZTerminal : public ZWidget<QFrame>
{
    Q_OBJECT
public:
    ZTerminal(const ZConfig &el, QWidget *parent=0);

signals:
    void finished();

private:
    void init();
    void parse(const ZConfig &el);

private:
    QTermWidget *_terminal;
};

#endif // ZTERMINAL_H
