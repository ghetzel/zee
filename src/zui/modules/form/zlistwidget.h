#ifndef ZLIST_WIDGET_
#define ZLIST_WIDGET_

#define ZUI_LIST            "zui:list"
#define ZLIST_ITEM_NAME     "zui:item"

#include <iostream>
#include <QListView>
#include <QtCore>
#include <zutil.h>
#include <zui/zuiutils.h>
#include <zui/zwidget.h>
#include "ztuplelistmodel.h"

using namespace std;

/*!
  \class ZListWidget
  \ingroup zui_plugins_form
  \brief A list
*/
class ZListWidget : public ZWidget<QListView>
{
    Q_OBJECT

public:
    ZListWidget(const ZConfig &el, QWidget *parent);

signals:
    void activated(QVariant);
    void selected(QVariant);
    void clicked(QVariant);
    void doubleClicked(QVariant);

public slots:
    void setCurrentIndex(int row);

private slots:
    void _activated(QModelIndex i);
    void _clicked(QModelIndex i);
    void _doubleClicked(QModelIndex i);

private:
    void parse(const ZConfig &el);
    void currentChanged(const QModelIndex &current, const QModelIndex &previous);
};

#endif
