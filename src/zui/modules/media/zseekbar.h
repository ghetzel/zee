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

#ifndef ZSEEKBAR_H
#define ZSEEKBAR_H

#define ZUI_SEEKBAR	"zui:seekbar"

#include <QtCore>
#include <zeventmanager.h>
#include <zui/zwidget.h>
#include <zui/modules/form/zprogressbar.h>

class ZSeekbar : public ZProgressBar
{
    Q_OBJECT
public:
    ZSeekbar(const ZConfig &el, QWidget *parent=0);
    void parse(const ZConfig&);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public slots:
    void reset();
    void addBookmark(qint64 msec);
    void addBookmarks(QString marks);

signals:
    void positionChanged(qint64);

private:
    void init();

private:
    QList<qint64> _bookmarks;
};

#endif // ZSEEKBAR_H
