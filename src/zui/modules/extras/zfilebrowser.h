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

#ifndef ZFILEBROWSER_H
#define ZFILEBROWSER_H

#define ZUI_FILEBROWSER "zui:filebrowser"

#include <iostream>
#include <QtCore>
#include <QtGui>
#include <zutil.h>
#include <zui/zwidget.h>
#include <zui/zuiutils.h>
#include <zui/modules/form/zlistwidget.h>
#include <zui/zlistwidgetitem.h>

#define ZUI_FLIST_DEFAULT_DIR    "~"


class ZFileBrowser : public ZListWidget
{
  Q_OBJECT

public:
  ZFileBrowser(const ZConfig &el, QWidget *parent = 0);
  ZFileBrowser(QDir initDirectory, const ZConfig &el, QWidget *parent = 0);
  ZFileBrowser(QString initDirectory, const ZConfig &el, QWidget *parent = 0);
  void parse(const ZConfig &el);

public slots:
  bool cd(QModelIndex itemIndex);
  bool cd(QDir directory);
  bool cd(QString directory);
  bool cdUp();

signals:
  void directoryChanged(QString);
  void activated(QString);
  void activated(QStringList);

protected:
  virtual void init();
  virtual void keyPressEvent(QKeyEvent *event);
  QFileSystemModel *pwd;

private slots:
  void _activated(const QModelIndex&);
};

#endif // ZFILEBROWSER_H
