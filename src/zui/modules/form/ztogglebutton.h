#ifndef ZTOGGLEBUTTON_H
#define ZTOGGLEBUTTON_H

#define ZUI_TOGGLEBUTTON          "zui:togglebutton"

#include <QObject>
#include <zbutton.h>
#include <zeventmanager.h>

class ZToggleButton : public ZButton
{
    Q_OBJECT

public:
    ZToggleButton(const ZConfig &el, QWidget *parent);
    ZToggleButton(const QString &text, const ZConfig &el, QWidget *parent);
    ZToggleButton(const QString &icon, const QString &text, const ZConfig &el, QWidget *parent);

public slots:
    void check();
    void uncheck();
    void toggle();

signals:
    void checked();
    void unchecked();

private slots:
    void _toggled(bool);

private:
    void init();
    void toggleLabel();
    virtual void parse(const ZConfig &el);

private:
    QString _otherLabel;
    QIcon _otherIcon;
};

#endif // ZTOGGLEBUTTON_H
