#include "canvas.h"

Canvas::Canvas(QWidget *parent)
 : QFrame(parent){
    _radiusX = 200.0;
    _radiusY = 200.0;
    _startAngle = 235.0;
    _extentAngle = 233.0;
    _minValue = 0;
    _maxValue = 150;
}

void Canvas::addValue(int a){
	addValue((qreal)a);
}

void Canvas::addValue(qreal a)
{
	_values << a;
//	qSort(_values);

        _valueSum = 0.0;
	foreach(qreal v, _values)
		_valueSum += v;
	repaint(rect());
}

void Canvas::clear(){
	_values.clear();
	_valueSum = 0.0;
	repaint(rect());	
}

void Canvas::paintEvent(QPaintEvent *e)
{
    QPainter *p = new QPainter(this);
    QPen pen(QColor(0,0,0,255));
    qreal curangle = 0.0;

    if(p->isActive()){
        p->setRenderHint(QPainter::Antialiasing);
        pen.setWidth(1);
        p->setPen(pen);

        p->save();
        pen.setColor(QColor(255,0,0,255));
        p->setPen(pen);

        foreach(qreal v, _values){
		qreal span = (5760.0 / _valueSum) * v;

		cout << "Value: " << v << " (sum="<<_valueSum<<") , span = " << span << "/5760, curangle = " << curangle;

		p->drawPie(rect(), curangle, span);
		curangle += span;

		cout << ", newangle = " << curangle << endl;
	}

        p->restore();

//        p->drawEllipse(PADDING,PADDING,_radiusX*2,_radiusY*2);
        p->end();
    }

    QFrame::paintEvent(e);
}
