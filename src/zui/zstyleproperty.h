#ifndef ZSTYLEPROPERTY_H
#define ZSTYLEPROPERTY_H

#include <QString>
#include <QPen>
#include <QBrush>
#include <libzee/libzee.h>
#include <zutil.h>

class ZStyleSection;

class ZStyleProperty : public QObject
{
    Q_OBJECT
public:
    ZStyleProperty(ZStyleSection *parent=0);
    ZStyleProperty(const ZStyleProperty &other);
    ZStyleProperty(QString value);
    ZStyleProperty(QString name, QString value, ZStyleSection *parent=0);
    ~ZStyleProperty();
    QString toString();
    QString name();
    ZString rawValue();
    ZStyleSection *section();

private:
    void init();
    void parse();

private:
    ZStyleSection *_parent;
    QString _name;
    ZString _value;
};

Q_DECLARE_METATYPE(ZStyleProperty);
//qRegisterMetaType<ZStyleProperty>("ZStyleProperty");

#endif // ZSTYLEPROPERTY_H
