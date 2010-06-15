#include <iostream>
#include <string>
#include <QtCore>
#include <QtGui>

#define	ANNULAR_OFFSET			-90
#define PADDING                         2

using namespace std;

static const double Q_PI   = 3.14159265358979323846;

class Canvas : public QFrame{
	Q_OBJECT
public:
	Canvas(QWidget *parent=0);
	void paintEvent(QPaintEvent *e);

public slots:
	void setAngle(int a){
		repaint(rect());
	};

private:
        void prepareTicks(QString series, int everyNvalues, int labelEvery, int length, int skipEvery=0);

        QHash<QString,QPainterPath> _ticks;
        qreal _radiusX, _radiusY;
        qreal _startAngle;
        qreal _extentAngle;
        int _minValue;
        int _maxValue;
};
