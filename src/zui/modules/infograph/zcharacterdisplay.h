/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

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
