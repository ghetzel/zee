#ifndef ZSETTING_H
#define ZSETTING_H

#define ZEE_SETTING	"zee:setting"

#include <QObject>
#include <zutil.h>
#include <zconfigurable.h>
#include <zeventmanager.h>

class ZSetting : public QObject, public ZConfigurable
{
public:
    ZSetting(const ZConfig &el, QObject *parent=0);
    void parse(const ZConfig &el);
};

#endif // ZSETTING_H
