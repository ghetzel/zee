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

#ifndef ZTOGGLEBUTTON_H
#define ZTOGGLEBUTTON_H

#define ZUI_TOGGLEBUTTON          "zui:togglebutton"

#include <QObject>
#include <zbutton.h>
#include <zeventmanager.h>

class ZToggleButton : public ZButton
{
    Q_OBJECT

public:
    ZToggleButton(const ZConfig &el, QWidget *parent);
    ZToggleButton(const QString &text, const ZConfig &el, QWidget *parent);
    ZToggleButton(const QString &icon, const QString &text, const ZConfig &el, QWidget *parent);

public slots:
    void check();
    void uncheck();
    void toggle();

signals:
    void checked();
    void unchecked();

private slots:
    void _toggled(bool);

private:
    void init();
    void toggleLabel();
    virtual void parse(const ZConfig &el);

private:
    QString _otherLabel;
    QIcon _otherIcon;
};

#endif // ZTOGGLEBUTTON_H
