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
  void _activated(const QModelIndex &index);
};

#endif // ZFILEBROWSER_H
