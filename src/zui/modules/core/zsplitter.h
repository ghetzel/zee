#ifndef ZSPLITTER_H
#define ZSPLITTER_H

#define ZUI_SPLITTER        "zui:splitter"
#define ZUI_PANE            "zui:pane"

#include <QSplitter>
#include <zeventmanager.h>
#include <zui/zwidget.h>

class ZSplitter : public ZWidget<QSplitter>
{
    Q_OBJECT

public:
    ZSplitter(const ZConfig &el, QWidget *parent=0);

private:
    void parse(const ZConfig &el);
};

#endif // ZSPLITTER_H
