#include "ztrayicon.h"

ZTrayIcon::ZTrayIcon(const ZConfig &el, QObject *parent)
    : QSystemTrayIcon(parent),
      ZConfigurable(el,this)
{
    parse(_config);

    connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
	    this, SLOT(_activated(ActivationReason)));

    zEvent->registerSignal(this, SIGNAL(clicked()));
    zEvent->registerSignal(this, SIGNAL(doubleClicked()));
    zEvent->registerSignal(this, SIGNAL(middleClicked()));
    zEvent->registerSignal(this, SIGNAL(messageClicked()));
    zEvent->registerSignal(this, SIGNAL(rightClicked()));
    zEvent->registerSlot(this, SLOT(hide()));
    zEvent->registerSlot(this, SLOT(message(QString,QString,QString,int)));
    zEvent->registerSlot(this, SLOT(message(QString,QString,QString)));
    zEvent->registerSlot(this, SLOT(message(QString,QString)));
    zEvent->registerSlot(this, SLOT(message(QString)));
    zEvent->registerSlot(this, SLOT(setIcon(QString)));
    zEvent->registerSlot(this, SLOT(setToolTip(QString)));
    zEvent->registerSlot(this, SLOT(show()));

    QSystemTrayIcon::show();
}

void ZTrayIcon::parse(const ZConfig &el){
    if(el.hasAttribute("icon"))
	QSystemTrayIcon::setIcon(ZuiUtils::getIcon(el.attribute("icon")));

    if(el.hasAttribute("tip"))
	setToolTip(el.attribute("tip"));
}

void ZTrayIcon::message(QString title, QString body, QString icon, int timeout){
    QSystemTrayIcon::MessageIcon ico = QSystemTrayIcon::NoIcon;
    icon = icon.toLower();

    if(ZuiUtils::attribute(icon, ZuiUtils::SeverityInfo))
	ico = QSystemTrayIcon::Information;
    else if(ZuiUtils::attribute(icon, ZuiUtils::SeverityWarning))
	ico = QSystemTrayIcon::Warning;
    else if(ZuiUtils::attribute(icon, ZuiUtils::SeverityCritical))
	ico = QSystemTrayIcon::Critical;

    showMessage(title, body, ico, timeout);
}

void ZTrayIcon::setToolTip(QString tip){
    QSystemTrayIcon::setToolTip(tip);
}

void ZTrayIcon::setIcon(QString icon){
    QSystemTrayIcon::setIcon(ZuiUtils::getIcon(icon));
}

void ZTrayIcon::_activated(ActivationReason reason){
    switch(reason){
    case Trigger:
	emit clicked();
	break;
    case DoubleClick:
	emit doubleClicked();
	break;
    case MiddleClick:
	emit middleClicked();
	break;
    case Context:
	emit rightClicked();
	break;
    case Unknown:
	break;
    }
}
