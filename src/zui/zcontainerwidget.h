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

#ifndef ZCONTAINERWIDGET_H
#define ZCONTAINERWIDGET_H

#include <QWidget>
#include <zui/zwidget.h>

class ZContainerWidget : public ZWidget
{
public:
    ZContainerWidget(const ZConfig &el, QWidget *self);
    Qt::Alignment alignment();
    void setAlignment(QString alignment);
    void setAlignment(Qt::Alignment alignment);

protected:
    virtual void parse(const ZConfig &el);
};

#endif // ZCONTAINERWIDGET_H
