#ifndef ZSCREEN_MANAGER_
#define ZSCREEN_MANAGER_

#define ZUI_SCREENMGR       "zui:screens"

#include <iostream>
#include <QWidget>
#include <QStackedWidget>
#include <QHash>
#include <QVariant>
#include <zutil.h>
#include <zui/zwidget.h>
#include <zeventmanager.h>

using namespace std;

/*!
  \class ZScreenManager
  \ingroup zui_plugins_core
  \brief A screen stacking manager with named elements
*/
class ZScreenManager : public QStackedWidget, public ZWidget
{
  Q_OBJECT
  Q_PROPERTY(QString screen READ screen RESET jump)

  private:
    QHash<QString,int> _screens;
    QString _defaultScreen;
    QString _currentScreen;

    void parse(const ZConfig &el);

  public:
//! Constructs a new manager
    ZScreenManager(const ZConfig &el, QWidget *parent);

//! adds a new screen \a widget named \a id
    int addScreen(QWidget *widget, QString id);

//! sets \a screen to be the default screen one isnt specified to be shown
    void setDefaultScreen(QString screen);

//! screen property
    QString screen();

public slots:
    void jump(QString screen="");
};

#endif
