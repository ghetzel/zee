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

#include "zgenericdial.h"

ZGenericDial::ZGenericDial(const ZConfig &el, QWidget *parent)
    : QFrame(parent),
      ZContainerWidget(el,this){
    init(0);
}

ZGenericDial::ZGenericDial(double startValue, const ZConfig &el,
                           QWidget *parent)
    : QFrame(parent),
      ZContainerWidget(el,this)
{
    init(startValue);
}

void ZGenericDial::init(double startValue)
{
    _offset = 0;
    _range = 360.0;
    _minValue = 0.0;
    _value = startValue;
    _maxValue = 100.0;
    _padX = ZGENERIC_DIAL_X_PAD+(layout() ? layout()->spacing() : 0);
    _padY = ZGENERIC_DIAL_Y_PAD+(layout() ? layout()->spacing() : 0);

    parse(_config);

    zEvent->registerSlot(this, SLOT(setValue(int)));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, SIGNAL(valueChanged(qreal)), SLOT(redraw()));
    connect(this, SIGNAL(minimumValueChanged(qreal)), SLOT(redraw()));
    connect(this, SIGNAL(maximumValueChanged(qreal)), SLOT(redraw()));

    zEvent->registerSignal(this, SIGNAL(minimumValueChanged(qreal)));
    zEvent->registerSignal(this, SIGNAL(maximumValueChanged(qreal)));
    zEvent->registerSignal(this, SIGNAL(valueChanged(qreal)));
    zEvent->registerSignal(this, SIGNAL(rangeChanged(qreal,qreal)));
    zEvent->registerSlot(this, SLOT(reset()));
    zEvent->registerSlot(this, SLOT(hide()));
    zEvent->registerSlot(this, SLOT(refreshAllTicks()));
    zEvent->registerSlot(this, SLOT(setEnabled(bool)));
    zEvent->registerSlot(this, SLOT(show()));
    zEvent->registerSlot(this, SLOT(setMaximum(qreal)));
    zEvent->registerSlot(this, SLOT(setMinimum(qreal)));
    zEvent->registerSlot(this, SLOT(setValue(qreal)));
    zEvent->registerSlot(this, SLOT(setVisible(bool)));
}

void ZGenericDial::parse(const ZConfig &el){
    _value = qRound(property("value").toFloat());
    _startValue = _value;

    if(property("min").isValid())
        setMinimum(property("min").toDouble());

    if(property("max").isValid())
        setMaximum(property("max").toDouble());

    if(el.hasAttribute("start"))
        setStartOffset(qRound(el.attribute("start").toFloat()));

    if(el.hasAttribute("range"))
        setRange(qRound(el.attribute("range").toFloat()));

    if(ZuiUtils::attribute(el.attribute("direction"), ZuiUtils::RadialDirectionCounterClockwise)){
        _direction = Reverse;
    }else{
        _direction = Forward;
    }


    QDomNodeList l = el.childNodes();
    QDomNode e;
    QDomElement ell;
    for(uint i = 0; i < l.length(); i++){
        e = l.item(i);
        if(e.isElement()){
            ell = e.toElement();
            if(ell.tagName() == ZUI_GAUGE_SERIES)
                addTickRule(ell.attribute("name"),
                        ell.attribute("interval","1").toInt(),
                        ell.attribute("labelEvery","0").toInt(),
                        ell.attribute("length","5").toInt(),
                        ell.attribute("skipEvery","0").toInt());
        }
    }
}

void ZGenericDial::drawIndicator(QPolygonF &i){
    qreal rX = (width()-(_padX*2))/2;
    qreal rY = (height()-(_padY*2))/2;
    qreal s = qSin(RADIANS(_value));
    qreal c = qCos(RADIANS(_value));

    i << QPointF(rX,rY);
    i << QPointF(c*rX,s*(rY-100));
}

void ZGenericDial::paintEvent(QPaintEvent *event)
{
    QPainter *p = new QPainter(this);
    QStyleOption style;
    QPen pen(QColor(0,0,0,255));

    qreal cX = (width()/2.0)-(_padX);
    qreal cY = (height()/2.0)-(_padY);

    style.initFrom(this);

    p->setRenderHint(QPainter::Antialiasing);
    //pen.setWidth(1);
    //p->setPen(pen);

    p->save();
    pen.setColor(QColor(255,0,0,255));
    p->setPen(pen);

    foreach(QPainterPath t, _ticks)
        p->drawPath(t);
    p->restore();

    //p->drawText(cX-(75/2),cY-(25/2),75,32,Qt::AlignCenter,QVariant(_value).toString());

    p->setBrush(style.palette.background());
    p->drawEllipse(_padX,
                   _padY,
                   width()-(2*_padX),
                   height()-(2*_padY));

    QColor c;
    if(property("zgauge_background_color").isValid()){
        c = property("zgauge_background_color").value<QColor>();
        z_log_debug("ZGenericDial: background-color: "+STR(c.red())+","+STR(c.green())+","+STR(c.blue()));
    }

    //p->drawConvexPolygon(indicator);
    p->end();
}


void ZGenericDial::resizeEvent(QResizeEvent *e){
    QWidget::resizeEvent(e);
    refreshAllTicks();
}

void ZGenericDial::refreshTicks(ZDialTickRule r){
    int val = 0;
    qreal step = (_range/(_maxValue-_minValue))*r.every;
    qreal c,s;
    qreal xRadius = (width()-(_padX*2.0))/2.0;
    qreal yRadius = (height()-(_padY*2.0))/2.0;
    qreal innerXRadius = xRadius-r.length;
    qreal innerYRadius = yRadius-r.length;

    //  update stored rule
    _rules[r.series] = r;

    //  clear existing data
    _ticks[r.series] = QPainterPath();

    for(qreal a = 0.0; a <= _range; a+=step)
    {
        //  allow skipping of values
        if(r.skipEvery > 0 && (val++)%r.skipEvery == 0)
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
        s = qSin(RADIANS(a+ZGENERIC_DIAL_ANNULAR_OFFSET+_offset));
        c = qCos(RADIANS(a+ZGENERIC_DIAL_ANNULAR_OFFSET+_offset));
        _ticks[r.series].moveTo(QPointF( innerXRadius*c+xRadius+_padX,
                                         innerYRadius*s+yRadius+_padY));
        _ticks[r.series].lineTo(QPointF(xRadius*c+xRadius+_padX,
                                        yRadius*s+yRadius+_padY));
    }
}

void ZGenericDial::addTickRule(QString series, int everyNvalues, int labelEvery, int length, int skipEvery)
{
    ZDialTickRule r;
    r.series = series;
    r.every = everyNvalues;
    r.labelEvery = labelEvery;
    r.length = length;
    r.skipEvery = skipEvery;
    refreshTicks(r);
}

void ZGenericDial::refreshAllTicks(){
    foreach(ZDialTickRule r, _rules)
        refreshTicks(r);
}

void ZGenericDial::setValue(qreal value)
{
    if(value < _minValue)
        _value = _minValue;
    else if(value > _maxValue)
        _value = _maxValue;
    else
        _value = value;

    emit valueChanged(_value);
}
void ZGenericDial::setMinimum(qreal value)
{
    _minValue = value;
    //	calcRanges();
    emit minimumValueChanged(_minValue);
}

void ZGenericDial::setMaximum(qreal value)
{
    _maxValue = value;
    //	calcRanges();
    emit maximumValueChanged(_maxValue);
}


void ZGenericDial::setStartOffset(int sOffset)
{
    if(sOffset < 0)
        _offset = 0;
    else if(sOffset > 360)
        _offset = 360;
    else
        _offset = sOffset;
}

void ZGenericDial::setRange(int sRange)
{
    if(sRange < 0)
        _range = 0;
    else if(sRange > 360)
        _range = 360;
    else
        _range = sRange;

    //	calcRanges();
}

void ZGenericDial::reset(){
    setValue(_startValue);
}

QSize ZGenericDial::sizeHint()
{
    return QSize(ZGENERIC_DIAL_DEFAULT_WIDTH, ZGENERIC_DIAL_DEFAULT_HEIGHT);
}


void ZGenericDial::redraw()
{
    update(contentsRect());
}
