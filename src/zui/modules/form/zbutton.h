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

#ifndef ZBUTTON_
#define ZBUTTON_

#define ZUI_BUTTON          "zui:button"

#include <iostream>
#include <QPushButton>
#include <zeventmanager.h>
#include <zui/zwidget.h>

/*!
  \class ZButton
  \ingroup zui_plugins_form
  \brief A button with superpowers

*/
class ZButton : public QPushButton, public ZWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue)
    Q_PROPERTY(QString zicon READ zicon WRITE zSetIcon)

public:
    ZButton(const ZConfig &el, QWidget *parent);
    ZButton(const QString &text, const ZConfig &el, QWidget *parent);
    ZButton(const QString &icon, const QString &text, const ZConfig &el, QWidget *parent);
    QString zicon(){ return icon().themeName(); }
    QVariant value(){ return _value; }
    void setValue(QVariant v);
    void zSetIcon(QString name);

signals:
    void clicked(QVariant);

private slots:
    void _clicked();

private:
    void init();
    virtual void parse(const ZConfig &el);

private:
    QVariant _value;
};

#endif
