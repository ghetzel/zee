#ifndef ZTRAYICON_H
#define ZTRAYICON_H

#define	ZCM_TRAYICON		"zee:trayicon"

#define ZTRAY_MESSAGE_TIMEOUT	10000

#include <QSystemTrayIcon>
#include <zutil.h>
#include <zui/zuiutils.h>
#include <zeventmanager.h>
#include <zconfigurable.h>


class ZTrayIcon : public QSystemTrayIcon, public ZConfigurable
{
    Q_OBJECT
public:
    ZTrayIcon(const ZConfig &el, QObject *parent=0);

public slots:
    void show();
    void hide();
    void message(QString title, QString body="", QString icon="", int timeout=ZTRAY_MESSAGE_TIMEOUT);
    void setTitle(QString);
    void setIcon(QString);

signals:
    void clicked();
    void doubleClicked();
    void middleClicked();
    void rightClicked();

private slots:
    void _activated(QSystemTrayIcon::ActivationReason);

private:
    void parse(const ZConfig &el);
};

#endif // ZTRAYICON_H
