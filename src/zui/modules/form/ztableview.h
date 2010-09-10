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

#ifndef ZTABLEVIEW_H
#define ZTABLEVIEW_H

#define ZUI_TABLE      "zui:table"

#include <QTableView>
#include <zutil.h>
#include <zui/zuiutils.h>
#include <zui/zwidget.h>
#include <zeventmanager.h>

class ZTableView : public ZWidget<QTableView>
{
public:
    ZTableView(const ZConfig &el, QWidget *parent);

private:
    void parse(const ZConfig &el);
};

#endif // ZTABLEVIEW_H
