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

#ifndef ZSPLITTER_H
#define ZSPLITTER_H

#define ZUI_SPLITTER        "zui:splitter"
#define ZUI_PANE            "zui:pane"

#include <QSplitter>
#include <zeventmanager.h>
#include <zui/zcontainerwidget.h>

class ZSplitter : public QSplitter, public ZWidget
{
    Q_OBJECT

public:
    ZSplitter(const ZConfig &el, QWidget *parent=0);

private:
    void parse(const ZConfig &el);
};

#endif // ZSPLITTER_H
