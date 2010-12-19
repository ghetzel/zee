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

#ifndef ZSHORTCUT_H
#define ZSHORTCUT_H

#define ZCM_SHORTCUT        "zee:key"

#include <QObject>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZShortcut : public QObject, public ZConfigurable
{
    Q_OBJECT

public:
    ZShortcut(const ZConfig &el, QObject *parent=0);
    void lateInit();

public slots:
    void trigger();

signals:
    void triggered();

private:
    void parse(const ZConfig &el);

private slots:
    void _shortcutActivated();

private:
    QWidget *_source;
    QShortcut *_shortcut;
};

#endif // ZSHORTCUT_H
