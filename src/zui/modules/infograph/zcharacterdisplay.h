#ifndef ZCHARACTERDISPLAY_H
#define ZCHARACTERDISPLAY_H

#define ZUI_CHARACTER_DISPLAY           "zui:marquee"

#include <QLabel>
#include <zeventmanager.h>
#include <zui/zwidget.h>

class ZCharacterDisplay : public ZWidget<QFrame>
{
    Q_OBJECT

public:
    ZCharacterDisplay(const ZConfig &el, QWidget *parent=0);

public slots:
    void setText(QString text);
    void updateDisplay();

private:
    void init();
    void parse(const ZConfig &el);

    void addCharacter();

private:
    QString _text;
    QList<QLabel*> _characters;
    QString _charImagePath;
};

#endif // ZCHARACTERDISPLAY_H
