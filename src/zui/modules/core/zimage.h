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

#ifndef ZIMAGE_H
#define ZIMAGE_H

#define ZUI_IMAGE              "zui:image"

#include <QLabel>
#include <zeventmanager.h>
#include <zui/zwidget.h>


class ZImage : public ZWidget<QLabel>
{
    Q_OBJECT
    Q_PROPERTY(QString icon READ icon WRITE setIcon)
    Q_PROPERTY(QString image READ image WRITE setImage)

public:
    ZImage(const ZConfig &el, QWidget *parent=0);
    QString icon() const;
    QString image() const;
    void setIcon(QString);
    void setImage(QString);

private:
    void parse(const ZConfig &el);

private:
    QIcon _icon;
    QString _iconName;
    QString _imagePath;
};

#endif // ZIMAGE_H
