#ifndef ZSHORTCUT_H
#define ZSHORTCUT_H

#include <QObject>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZShortcut : public QObject, public ZConfigurable
{
    Q_OBJECT

public:
    ZShortcut(const ZConfig &el, QObject *parent=0);

private:
    void parse(const ZConfig &el);

private:
    QShortcut *_shortcut;
};

#endif // ZSHORTCUT_H
