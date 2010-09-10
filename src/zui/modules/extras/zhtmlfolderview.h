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

#ifndef ZHTMLFOLDERVIEW_H
#define ZHTMLFOLDERVIEW_H

#define ZUI_HTMLFOLDER      "zui:htmlfolder"

#include <QtCore>
#include <QtGui>
#include <zutil.h>
#include <libzee/zhtmllistmodel.h>
#include <zui/zwidget.h>
#include <zui/zuiutils.h>
#include <zui/modules/form/zlistwidget.h>
#include <zui/zlistwidgetitem.h>

class ZHTMLFolderView : public ZListWidget
{
    Q_OBJECT

public:
    ZHTMLFolderView(const ZConfig &el, QWidget *parent=0);
    void parse(const ZConfig &el);

public slots:
    void setUrl(QString location);

private:
    void init();

private:
    ZHTMLListModel *_model;
};

#endif // ZHTMLFOLDERVIEW_H
