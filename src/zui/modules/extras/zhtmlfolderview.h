#ifndef ZHTMLFOLDERVIEW_H
#define ZHTMLFOLDERVIEW_H

#define ZUI_HTMLFOLDER      "zui:htmlfolder"

#include <QtCore>
#include <QtGui>
#include <zutil.h>
#include <libzee/zhtmllistmodel.h>
#include <zui/zwidget.h>
#include <zui/zuiutils.h>
#include <zui/modules/form/zlistwidget.h>
#include <zui/zlistwidgetitem.h>

class ZHTMLFolderView : public ZListWidget
{
    Q_OBJECT

public:
    ZHTMLFolderView(const ZConfig &el, QWidget *parent=0);
    void parse(const ZConfig &el);

public slots:
    void setUrl(QString location);

private:
    void init();

private:
    ZHTMLListModel *_model;
};

#endif // ZHTMLFOLDERVIEW_H
