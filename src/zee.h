#ifndef ZEE_H_
#define ZEE_H_

#define ZEE_CFG_DIR             ".config/zee"
#define ZEE_CFG_KEY             "zconfig"
#define ZUI_DEFAULT_FILE_NAME   "ui.xml"
#define ZUI_DEFAULT_QSS_NAME    "ui.qss"

#define ZEE_EXIT_OK                                 0
#define ZEE_EXIT_NO_ZUI_DEF                         1
#define ZEE_EXIT_INVALID_ZUI_DEF                    2
#define ZEE_EXIT_ZUI_DEF_INACCESSIBLE               3

#include <iostream>
#include <typeinfo>

#include <QtCore>
#include <QtGui>
#include <QtXml>
#include <QString>
#include <QHash>
#include <QMultiHash>
#include <QList>

#ifdef Q_WS_X11
#include <X11/Xlib.h>
#endif // Q_WS_X11

#include <zutil.h>
#include <zeventmanager.h>
#include <zui/zuiparser.h>

/*!
  \class Zee
  \ingroup zeeapp
  \brief A configurable, cross-platform, extendable dynamic UI builder written
  in C++ using the Qt framework.

  Zee is an application designed to make creating modular cross-platform
  applications simple.  This is accomplished by the use of plain-text
  \link ZuiParser XML configurations for UI structure\endlink and via Qt's
  StyleSheets functionality.
*/

class Zee : public QApplication
{
  Q_OBJECT
  private:
    QHash<QString,QVariant> _arguments;
    const static int ZWIDTH = 500;
    const static int ZHEIGHT = 500;
    int sW, sH , sX, sY;
    static Zee *_app;
    QDesktopWidget *dtMain;

  public:
/*!
  Zee is the main instance for the application. It, like its parent
  QApplication, is responsible for initializing and starting the Qt event loop.
  It takes arguments \a argc and \a argv from the command line or any valid
  source.
*/
    Zee(int argc, char* argv[]);


/*!
  \internal

  Initializes the application by performing startup tasks such as UI definition
  parsing and applying stylesheets.
*/
    void	init();

/*!
  Returns the named argument or an invalid QVariant
*/
    QVariant arg(QString key);

/*!
  Returns whether the argument exists or not.
*/
    bool hasArg(QString key);

/*!
  Parses command-line arguments into an internal structure.

  \todo Clean this up a bit more, standardize and document switches.
*/
    void  parseArguments();


/*!
  Singular instance of this application
*/
    static Zee *instance();


/*!
  Loads and processes the UI definition file, either specified on the command
  line or from default locations.

  \todo add default system locations as places to search (home folders,
  system config folders, etc.)
*/
    void parseUI();


#ifdef Q_WS_X11
/*!
  Hooks into Qt event loop and receives XEvents sent to this window.
  Emits signal x11EventReceived, passing \a e as an argument to all interested
  parties.
*/
    bool x11EventFilter(XEvent *e);
#endif
  public slots:
    void reloadStyleSheet();
    void log(QString);
    void logWarning(QString);
    void logError(QString);
    void logCritical(QString);
    void logDebug(QString);

signals:
    void styleReloaded();
#ifdef Q_WS_X11
    void x11EventReceived(XEvent*);
#endif
};

#endif // ZEE_H_
