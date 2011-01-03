/******************************************************************************
*    This file is part of Zee.
*
*    Zee is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    Zee is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with Zee.  If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/

#ifndef ZGENERIC_DIAL_
#define ZGENERIC_DIAL_

#define ZUI_GAUGE_SERIES		"zui:series"

#define ZGENERIC_DIAL_ANNULAR_OFFSET    -90

#define ZGENERIC_DIAL_DEFAULT_WIDTH     50
#define ZGENERIC_DIAL_DEFAULT_HEIGHT    50

#define ZGENERIC_DIAL_X_PAD             2
#define ZGENERIC_DIAL_Y_PAD             2

#include <iostream>
#include <QString>
#include <QWidget>
#include <QtSvg>
#include <libzee/zstring.h>
#include <zutil.h>
#include <zui/zcontainerwidget.h>
#include <zeventmanager.h>

using namespace std;

class ZGenericDial : public QFrame, public ZContainerWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal value READ value WRITE setValue RESET reset)

public:
    ZGenericDial(const ZConfig &el, QWidget *parent=0);
    ZGenericDial(double startValue, const ZConfig &el, QWidget *parent=0);
    void addTickRule(QString series, int everyNvalues=1, int labelEvery=0, int length=5, int skipEvery=0);
    double maximum(){return _maxValue;}
    double minimum(){return _minValue;}
    int offset(){return _offset;}
    int range(){return _range;}
    void setStartOffset(int sOffset=0);
    void setRange(int sRange=360);
    qreal value(){return _value;}

    struct ZDialTickRule{
        QString series;
        int every;
        int labelEvery;
        int length;
        int skipEvery;
    };

public slots:
    void setValue(int value){
        setValue(CAST(qreal,value));
    }
    void setValue(qreal value);
    void setMinimum(double value);
    void setMaximum(double value);
    void reset();
    void redraw();
    QSize sizeHint();

private:
    void init(double startValue);
    void parse(const ZConfig &el);
    void refreshTicks(ZDialTickRule r);
    void drawIndicator(QPolygonF &i);

protected:
    virtual void resizeEvent(QResizeEvent *e);
    virtual void paintEvent(QPaintEvent *event);

protected:
    enum GaugeDirection{
        Forward,
        Reverse
    };
    GaugeDirection _direction;
    QHash<QString,QPainterPath> _ticks;
    QHash<QString,ZDialTickRule> _rules;
    qreal _startValue;
    qreal _value;
    qreal _radius;
    qreal _offset;
    qreal _range;
    int _minValue;
    int _maxValue;
    int _padX;
    int _padY;

private slots:
    void refreshAllTicks();

signals:
    void valueChanged(double);
    void minimumValueChanged(double);
    void maximumValueChanged(double);
    void rangeChanged(int,int);
};

#endif
