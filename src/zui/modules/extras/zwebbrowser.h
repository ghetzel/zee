#ifndef ZWEBBROWSER_H
#define ZWEBBROWSER_H

#define ZUI_WEBBROWSER  "zui:webbrowser"

#include <QtCore>
#include <QPalette>
#include <QtWebKit>
#include <zutil.h>
#include <zeventmanager.h>
#include <zui/zwidget.h>

/*!
    \class ZWebBrowser
    \ingroup zui_plugins_extras
    \brief A web browser widget

*/
class ZWebBrowser : public ZWidget<QWebView>{
  Q_OBJECT

private:
    QUrl _home;
//! \internal
//! initialize the class
  void init();
  void parse(const ZConfig &el);

public:
//! Construct a default browser
  ZWebBrowser(const ZConfig &el, QWidget *parent);
//! Construct a browser and go to \a uri
  ZWebBrowser(QString uri, const ZConfig &el, QWidget *parent);
//! Construct a browser and go to \a uri (a QUrl)
  ZWebBrowser(QUrl uri, const ZConfig &el, QWidget *parent);

public slots:
  void load(QString url="");
  void setHome(QString url);
};

#endif // ZWEBBROWSER_H
