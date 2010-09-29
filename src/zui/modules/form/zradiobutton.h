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

#ifndef ZRADIOBUTTON_H
#define ZRADIOBUTTON_H

#define ZUI_RADIO           "zui:radio"

#include <QtGui>
#include <zeventmanager.h>
#include <zwidget.h>

class ZRadioButton : public QRadioButton, public ZWidget
{
    Q_OBJECT

public:
    ZRadioButton(const ZConfig &el, QWidget *parent=0);

signals:
    void selected(QVariant);
    void deselected();

public slots:
    void select();
    void deselect();

private:
    void parse(const ZConfig &el);

private:
    QVariant _value;
};

#endif // ZRADIOBUTTON_H
