#ifndef ZSTYLESECTION_H
#define ZSTYLESECTION_H

// section identifier property name
#define ZSTYLE_SECTION_PROP_NAME            "zstyle-section-id"

// custom sub-control -> qproperty mappings
#define ZSTYLE_PROPSUB_SC_GAUGE             "gauge"

// aggregates and alternate forms
#define ZSTYLE_PROPSUB_AG_FIXED_HEIGHT      "fixed-height"
#define ZSTYLE_PROPSUB_AG_FIXED_WIDTH       "fixed-width"

#include <QWidget>
#include <QHash>
#include <QRegExp>
#include <QRectF>
#include <QColor>
#include <libzee/libzee.h>
#include <zutil.h>
#include <zstyleproperty.h>

class ZStyle;

class ZStyleSection : public QObject
{
    Q_OBJECT
public:
    ZStyleSection(ZStyle *parent=0);
    ZStyleSection(QString rule, QString data, ZStyle *parent=0);
    ZStyle *style();
    QString toString();
    void setId(int id);
    void pushProperty(const ZStyleProperty *property);
    ZStyleSection &merge(const ZStyleSection &other);

public:
    static ZStyleSection &merge(const ZStyleSection &first, const ZStyleSection &second);

signals:
    void sectionChanged(QString);

private:
    void init();
    void parse(QString data);

private:
    int _id;
    ZStyle *_parent;
    QHash<QString,ZStyleProperty*> _properties;
    ZString _rule;
    QString _data;
};

#endif // ZSTYLESECTION_H
