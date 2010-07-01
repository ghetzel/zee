#ifndef ZTABLEVIEW_H
#define ZTABLEVIEW_H

#define ZUI_TABLE      "zui:table"

#include <QTableView>
#include <zutil.h>
#include <zui/zuiutils.h>
#include <zui/zwidget.h>
#include <zeventmanager.h>

class ZTableView : public QTableView, public ZWidget
{
public:
    ZTableView(const ZConfig &el, QWidget *parent);

private:
    void parse(const ZConfig &el);
};

#endif // ZTABLEVIEW_H
