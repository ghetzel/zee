#ifndef ZLABEL_H
#define ZLABEL_H

#define ZUI_TEXT            "zui:text"

#include <QtCore>
#include <zui/zwidget.h>

class ZLabel : public ZWidget<QLabel>
{
    Q_OBJECT
public:
    ZLabel(const ZConfig &el, QWidget *parent=0);
    ZLabel(QString value, const ZConfig &el, QWidget *parent=0);

public slots:
    void reset();
private:
    void init();
    void parse(const ZConfig &el);

private:
    QString _initValue;
};

#endif // ZLABEL_H
