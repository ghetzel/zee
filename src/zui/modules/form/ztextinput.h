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
