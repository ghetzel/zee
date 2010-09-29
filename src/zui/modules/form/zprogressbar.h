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

#ifndef ZPROGRESSBAR_H
#define ZPROGRESSBAR_H

#define ZUI_PROGRESS	    "zui:progress"

#include <QProgressBar>
#include <zutil.h>
#include <zui/zwidget.h>

class ZProgressBar : public QProgressBar, public ZWidget
{
    Q_OBJECT

public:
    ZProgressBar(const ZConfig &el, QWidget *parent);
    void parse(const ZConfig &el);

private:
    void init();
};

#endif // ZPROGRESSBAR_H
