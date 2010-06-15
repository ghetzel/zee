#ifndef ZBUTTON_
#define ZBUTTON_

#define ZUI_BUTTON          "zui:button"

#include <iostream>
#include <QPushButton>
#include <zeventmanager.h>
#include <zui/zwidget.h>

/*!
  \class ZButton
  \ingroup zui_plugins_form
  \brief A button with superpowers

*/
class ZButton : public QPushButton, public ZWidget
{
    Q_OBJECT

public:
    ZButton(const ZConfig &el, QWidget *parent);
    ZButton(const QString &text, const ZConfig &el, QWidget *parent);
    ZButton(const QIcon &icon, const QString &text, const ZConfig &el, QWidget *parent);

private:
    virtual void parse(const ZConfig &el);
};

#endif
