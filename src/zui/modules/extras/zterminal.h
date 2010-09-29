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

class ZTerminal : public QFrame, public ZWidget
{
    Q_OBJECT
public:
    ZTerminal(const ZConfig &el, QWidget *parent=0);

signals:
    void finished();

private:
    void init();
    void parse(const ZConfig&);

private:
    QTermWidget *_terminal;
};

#endif // ZTERMINAL_H
