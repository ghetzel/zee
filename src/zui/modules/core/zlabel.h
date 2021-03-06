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

#ifndef ZLABEL_H
#define ZLABEL_H

#define ZUI_TEXT            "zui:text"

#include <QtCore>
#include <zui/zwidget.h>

class ZLabel : public QLabel, public ZWidget
{
    Q_OBJECT
public:
    ZLabel(const ZConfig &el, QWidget *parent=0);
    ZLabel(QString value, const ZConfig &el, QWidget *parent=0);

public slots:
    void reset();
private:
    void init();
    void parse(const ZConfig &el);

private:
    QString _initValue;
};

#endif // ZLABEL_H
