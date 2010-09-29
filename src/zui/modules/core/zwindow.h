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

#ifndef ZWINDOW_H
#define ZWINDOW_H

#define ZUI_APPLICATION         "zui:application"
#define ZUI_APP_DEFAULT_NAME    "ROOT"


#include <QtCore>
#include <QApplication>
#include <zui/zwidget.h>
#include <zui/zroot.h>

class ZWindow : public QFrame, public ZWidget
{
    Q_OBJECT

public:
    ZWindow(const ZConfig &el, QWidget *parent=0);
    QWidget *rootSurface();

signals:
    void clicked(int,int);
    void doubleClicked(int,int);
    void released(int,int);
    void hover(int,int);

private:
    QWidget *_rootSurface;

    void init();
    void parse(const ZConfig &el);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

};

#endif // ZWINDOW_H
