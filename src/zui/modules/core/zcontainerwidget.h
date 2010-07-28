#ifndef ZCONTAINERWIDGET_H
#define ZCONTAINERWIDGET_H

#define ZUI_CONTAINER       "zui:container"

#include <QtGui>
#include <zui/zwidget.h>
#include <zeventmanager.h>

class ZContainerWidget : public ZWidget<QFrame>
{
    Q_OBJECT
    Q_PROPERTY(Qt::Alignment align READ alignment WRITE setAlignment)
public:
    ZContainerWidget(const ZConfig &el, QWidget *parent=0);
    Qt::Alignment alignment();
    void setAlignment(Qt::Alignment alignment);


public slots:
    void toggle();

private:
    void parse(const ZConfig &el);
};

#endif // ZCONTAINERWIDGET_H
