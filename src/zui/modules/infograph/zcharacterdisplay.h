#ifndef ZCHARACTERDISPLAY_H
#define ZCHARACTERDISPLAY_H

#define ZUI_CHARACTER_DISPLAY           "zui:marquee"

#include <QLabel>
#include <zeventmanager.h>
#include <zui/zwidget.h>

class ZCharacterDisplay : public ZWidget<QFrame>
{
public:
    ZCharacterDisplay(const ZConfig &el, QWidget *parent=0);

private:
    void init();
    void parse(const ZConfig &el);
    void updateDisplay();

private:
    QString _text;
    QList<QLabel*> _characters;
};

#endif // ZCHARACTERDISPLAY_H
