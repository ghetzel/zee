#ifndef ZGENERIC_DIAL_
#define ZGENERIC_DIAL_

#define ZUI_GAUGE_SERIES		"zui:series"

#define ZGENERIC_DIAL_ANNULAR_OFFSET    -90

#define ZGENERIC_DIAL_DEFAULT_WIDTH     300
#define ZGENERIC_DIAL_DEFAULT_HEIGHT    300

#define ZGENERIC_DIAL_X_PAD             2
#define ZGENERIC_DIAL_Y_PAD             2

#include <iostream>
#include <QtCore>
#include <QtGui>
#include <QtSvg>
#include <zutil.h>
#include <zui/zwidget.h>
#include <zeventmanager.h>

using namespace std;

class ZGenericDial : public QFrame, public ZWidget
{
    Q_OBJECT
//    Q_PROPERTY(int value READ value)

public:
    ZGenericDial(const ZConfig &el, QWidget *parent=0);
    ZGenericDial(double startValue, const ZConfig &el, QWidget *parent=0);
    void addTickRule(QString series, int everyNvalues=1, int labelEvery=0, int length=5, int skipEvery=0);
    double maximum(){return _maxValue;};
    double minimum(){return _minValue;};
    int offset(){return _offset;};
    int range(){return _range;};
    void setStartOffset(int sOffset=0);
    void setRange(int sRange=360);
    double value(){return _value;};

    struct ZDialTickRule{
	QString series;
	int every;
	int labelEvery;
	int length;
	int skipEvery;
    };

public slots:
    void setValue(int xvalue){setValue(static_cast<double>(xvalue));};
    void setValue(double xvalue);
    void setMinimum(double value);
    void setMaximum(double value);
    void redraw();
    QSize sizeHint();

private:
    void init(double startValue);
    void parse(const ZConfig &el);
    void refreshTicks(ZDialTickRule r);
    void resizeEvent(QResizeEvent *e);
    void drawIndicator(QPolygonF &i);

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    QHash<QString,QPainterPath> _ticks;
    QHash<QString,ZDialTickRule> _rules;
    qreal _value;
    qreal _radius;
    qreal _offset;
    qreal _range;
    int _minValue;
    int _maxValue;

private slots:
    void refreshAllTicks();

signals:
    void valueChanged(double);
    void minimumValueChanged(double);
    void maximumValueChanged(double);
    void rangeChanged(int,int);
};

#endif
