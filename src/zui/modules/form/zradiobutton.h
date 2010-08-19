#ifndef ZRADIOBUTTON_H
#define ZRADIOBUTTON_H

#define ZUI_RADIO           "zui:radio"

#include <QtGui>
#include <zeventmanager.h>
#include <zwidget.h>

class ZRadioButton : public ZWidget<QRadioButton>
{
    Q_OBJECT

public:
    ZRadioButton(const ZConfig &el, QWidget *parent=0);

signals:
    void selected(QVariant);
    void deselected();

public slots:
    void select();
    void deselect();

private:
    void parse(const ZConfig &el);

private:
    QVariant _value;
};

#endif // ZRADIOBUTTON_H
