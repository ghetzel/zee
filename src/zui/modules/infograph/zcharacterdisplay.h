#ifndef ZCHARACTERDISPLAY_H
#define ZCHARACTERDISPLAY_H

#define ZUI_CHARACTER_DISPLAY           "zui:marquee"

#include <QLabel>
#include <QtSvg/QSvgRenderer>
#include <zutil.h>
#include <zeventmanager.h>
#include <zui/zwidget.h>

class ZCharacterDisplay : public ZWidget<QFrame>
{
    Q_OBJECT
    Q_PROPERTY(int lineCount READ lineCount)
    Q_PROPERTY(int currentLine READ currentLine)
    Q_PROPERTY(int currentLineLength READ currentLineLength)

public:
    ZCharacterDisplay(const ZConfig &el, QWidget *parent=0);
    int lineCount() const;
    int currentLine() const;
    int currentLineLength() const;

public slots:
    void setText(QString text);
    void setText(QString text, int line);
    void appendLine(QString text);
    void setLine(int line);
    void updateDisplay();

private:
    void init();
    void parse(const ZConfig &el);
    void addCharacter();
    bool _characterImageIsSvg();
    QPixmap _characterImage(QChar token);

private:
    QHash<int,QString> _text;
    int _currentLine;
    QSize _charSize;
    QList<QLabel*> _characters;
    QString _charImagePath;
    QString _charFallbackPath;
};

#endif // ZCHARACTERDISPLAY_H
