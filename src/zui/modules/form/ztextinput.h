#ifndef ZTEXTINPUT_H
#define ZTEXTINPUT_H

#define ZUI_INPUT      "zui:input"

#include <zutil.h>
#include <zui/zwidget.h>

class ZTextInput : public QLineEdit, public ZWidget
{
    Q_OBJECT
    Q_PROPERTY(int lastCursorPosition READ lastCursorPosition)

public:
    ZTextInput(const ZConfig &el, QWidget *parent=0);
    int lastCursorPosition();

private:
    int _lastCursorPosition;

    void init();
    void parse(const ZConfig &el);

private slots:
    void _cursorPosition(int o, int);
};

#endif // ZTEXTINPUT_H
