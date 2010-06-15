#ifndef ZFOLDERVIEW_H
#define ZFOLDERVIEW_H

#define ZUI_FOLDERVIEW  "zui:folder"

#include <QtCore>
#include <QtGui>

#include <zutil.h>
#include <zui/zuiutils.h>
#include <zui/zwidget.h>
#include "zfilebrowser.h"

class ZFolderView : public ZFileBrowser{
  Q_OBJECT

public:
  ZFolderView(const ZConfig &el, QWidget *parent = 0);
  ZFolderView(QDir initDirectory, const ZConfig &el, QWidget *parent = 0);
  ZFolderView(QString initDirectory, const ZConfig &el, QWidget *parent = 0);

private:
  void init();
};

#endif // ZFOLDERVIEW_H
