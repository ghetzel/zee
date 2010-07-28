#ifndef ZSHORTCUT_H
#define ZSHORTCUT_H

#define ZCM_SHORTCUT        "zee:key"

#include <QObject>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZShortcut : public QObject, public ZConfigurable
{
    Q_OBJECT

public:
    ZShortcut(const ZConfig &el, QObject *parent=0);

signals:
    void triggered();

private:
    void parse(const ZConfig &el);

private slots:
    void _shortcutActivated();

private:
    QWidget *_source;
    QShortcut *_shortcut;
};

#endif // ZSHORTCUT_H
