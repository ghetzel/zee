#include "canvas.h"

Canvas::Canvas(QWidget *parent)
 : QFrame(parent){
    _radiusX = 200.0;
    _radiusY = 200.0;
    _startAngle = 235.0;
    _extentAngle = 233.0;
    _minValue = 0;
    _maxValue = 150;

    prepareTicks("velocity_1",1,0,3,5);
    prepareTicks("velocity_5",5,0,7,2);
    prepareTicks("velocity_10",10,0,10,2);
    prepareTicks("velocity_20",20,0,15);
}

void Canvas::prepareTicks(QString series, int everyNvalues, int labelEvery, int length, int skipEvery){
    int val = 0;
    qreal step = (_extentAngle/(_maxValue-_minValue))*everyNvalues;
    qreal s,c;
    qreal innerRadiusX = _radiusX-length;
    qreal innerRadiusY = _radiusY-length;

    for(qreal a = 0.0; a <= _extentAngle; a+=step)
    {
    //  allow skipping of values
        if(skipEvery > 0 && (val++)%skipEvery == 0)
            continue;

    /*!  Lines are drawn as two points connecting the same angle projected onto two
         concentric circles; the outer circle (visible border ellipse) and an inner
         circle whose radius is \a length shorter than the border

         Points are calculated as follows:

            x --> r cos θ
            y --> r sin θ

         Where θ is the current angle that we wish to draw the line, expressed in
         radians, and r is the radius of the circle we're working with.
     */
        s = qSin((a+ANNULAR_OFFSET+_startAngle)*(Q_PI/180.0) );
        c = qCos((a+ANNULAR_OFFSET+_startAngle)*(Q_PI/180.0) );
        _ticks[series].moveTo(QPointF( innerRadiusX*c+_radiusX+PADDING, innerRadiusY*s+_radiusY+PADDING));
        _ticks[series].lineTo(QPointF(_radiusX*c+_radiusX+PADDING, _radiusY*s+_radiusY+PADDING));
    }
}

void Canvas::paintEvent(QPaintEvent *e)
{
    QPainter *p = new QPainter(this);
    QPen pen(QColor(0,0,0,255));

    if(p->isActive()){
        p->setRenderHint(QPainter::Antialiasing);
        pen.setWidth(1);
        p->setPen(pen);

        p->save();
        pen.setColor(QColor(255,0,0,255));
        p->setPen(pen);

        foreach(QPainterPath t, _ticks)
            p->drawPath(t);

        p->restore();

        p->drawEllipse(PADDING,PADDING,_radiusX*2,_radiusY*2);
        p->end();
    }

    QFrame::paintEvent(e);
}
