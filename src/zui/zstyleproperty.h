#ifndef ZSTYLEPROPERTY_H
#define ZSTYLEPROPERTY_H

// property value validation
#define ZSTYLE_PROP_BOOL_TRUE       "1|true|yes|on"
#define ZSTYLE_PROP_BOOL_FALSE      "0|false|no|off"
#define ZSTYLE_PROP_LENGTH          "px|pt|em|ex"

// value parsing expressions
#define ZSTYLE_PROP_MATCH_LENGTH    "[0-9]+("ZSTYLE_PROP_LENGTH")?"
#define ZSTYLE_PROP_MATCH_BOX       "^("ZSTYLE_PROP_MATCH_LENGTH"(?:(\\s+|\\s*$))){1,4}"
#define ZSTYLE_PROP_COLOR_HEX       "#([0-9A-Fa-f]{3}|[0-9A-Fa-f]{4}|[0-9A-Fa-f]{6}|[0-9A-Fa-f]{8})"

#define ZSTYLE_PROP_COLOR_DEC       "[0-9]{1,3}%?"
#define ZSTYLE_PROP_COLOR_RGB       "rgb\\s*\\(\\s*("ZSTYLE_PROP_COLOR_DEC")\\s*,\\s*("ZSTYLE_PROP_COLOR_DEC")\\s*,\\s*("ZSTYLE_PROP_COLOR_DEC")\\s*\\)"
#define ZSTYLE_PROP_COLOR_RGBA      "rgba\\s*\\(\\s*("ZSTYLE_PROP_COLOR_DEC")\\s*,\\s*("ZSTYLE_PROP_COLOR_DEC")\\s*,\\s*("ZSTYLE_PROP_COLOR_DEC")\\s*,\\s*("ZSTYLE_PROP_COLOR_DEC")\\s*\\)"


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

public:
//  the idea behind this static function is as follows:
//
//      a zee-specific ::subcontrol's properties will be converted into
//      qproperties, which will propogate to all matching objects.  once
//      in those objects, those properties will be set to the raw value of the
//      QSS property value.  This function is designed to take that raw value
//      and return a new ZStyleProperty initialized to that value.  The init
//      will, in turn, automatically parse that raw value into the interpreted
//      result (e.g.: '1px 2px' as an argument will result in a quad() whose
//      top()/bottom() = 1, and a right()/left() = 2).  This resultant object
//      can then be used to easily pull out expected values and used in the
//      display of the widget.  So:
//
//          background-color: red;
//
//      Will result in a ZStyleProperty with a color() method that returns
//      a QColor(Qt::red) value, which can then be used to draw the widget.
//
    static ZStyleProperty &valueFrom(QString rawValue);

// Value Accessor Properties
//   the value of this property will be parsed for certain data
//   if that data is contained in the value, these methods can be used to
//   access it.  Otherwise, they will return their default-constructed values, or
//   in the case of primitive numeric types, -1.
public:
    enum ZBorderStyle{
        None,
        Dashed,
        DotDash,
        DotDotDash,
        Dotted,
        Double,
        Groove,
        Inset,
        Outset,
        Ridge,
        Solid
    };

    enum ZStyleAlign{
        Top,
        Bottom,
        Left,
        Right,
        Center
    };

    qreal width(){          return _width;  }

    qreal height(){         return _height; }
    QRectF quad(){          return _quad;   }
    ZBorderStyle style();
    QColor color(){         return _color;  }
    QPen pen(){             return _pen;    }
    QBrush brush(){         return _brush;  }
    bool toBool(){          return _toBool; }

private:
    void init();
    void parse();

private:
    ZStyleSection *_parent;
    QString _name;
    ZString _value;

private:
    qreal _width;
    qreal _height;
    QRectF _quad;
    ZBorderStyle _style;
    QColor _color;
    QPen _pen;
    QBrush _brush;
    bool _toBool;
};

Q_DECLARE_METATYPE(ZStyleProperty);
//qRegisterMetaType<ZStyleProperty>("ZStyleProperty");

#endif // ZSTYLEPROPERTY_H
