#include <iostream>
#include <string>
#include <QtCore>
#include <QtGui>

#define	ANNULAR_OFFSET			-1440
#define PADDING                         2

using namespace std;

static const double Q_PI   = 3.14159265358979323846;

class Canvas : public QFrame{
	Q_OBJECT
public:
	Canvas(QWidget *parent=0);
	void paintEvent(QPaintEvent *e);

public slots:
	void clear();
	void addValue(int a);
	void addValue(qreal a);

private:
	QList<qreal> _values;
	qreal _valueSum;
        qreal _radiusX, _radiusY;
        qreal _startAngle;
        qreal _extentAngle;
        int _minValue;
        int _maxValue;
};
