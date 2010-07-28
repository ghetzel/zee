#include "zgenericdial.h"

ZGenericDial::ZGenericDial(const ZConfig &el, QWidget *parent)
    : ZWidget<QFrame>(el,this,parent){
    init(0);
}

ZGenericDial::ZGenericDial(double startValue, const ZConfig &el,
			   QWidget *parent)
    : ZWidget<QFrame>(el,this,parent)
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

    parse(_config);

    zEvent->registerSlot(this, SLOT(setValue(int)));

    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    connect(this, SIGNAL(valueChanged(double)), SLOT(redraw()));
    connect(this, SIGNAL(minimumValueChanged(double)), SLOT(redraw()));
    connect(this, SIGNAL(maximumValueChanged(double)), SLOT(redraw()));

    zEvent->registerSignal(this, SIGNAL(minimumValueChanged(double)));
    zEvent->registerSignal(this, SIGNAL(maximumValueChanged(double)));
    zEvent->registerSignal(this, SIGNAL(valueChanged(double)));
    zEvent->registerSignal(this, SIGNAL(rangeChanged(int,int)));
    zEvent->registerSlot(this, SLOT(hide()));
    zEvent->registerSlot(this, SLOT(refreshAllTicks()));
    zEvent->registerSlot(this, SLOT(setEnabled(bool)));
    zEvent->registerSlot(this, SLOT(show()));
    zEvent->registerSlot(this, SLOT(setMaximum(double)));
    zEvent->registerSlot(this, SLOT(setMinimum(double)));
    zEvent->registerSlot(this, SLOT(setValue(double)));
    zEvent->registerSlot(this, SLOT(setVisible(bool)));
}

void ZGenericDial::parse(const ZConfig &el){
    if(el.hasAttribute("max"))
	setMaximum(el.attribute("max").toDouble());

    if(el.hasAttribute("min"))
	setMinimum(el.attribute("min").toDouble());

    if(el.hasAttribute("start"))
	setStartOffset(el.attribute("start").toInt());

    if(el.hasAttribute("range"))
	setRange(el.attribute("range").toInt());

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
    qreal rX = (width()-(ZGENERIC_DIAL_X_PAD*2))/2;
    qreal rY = (height()-(ZGENERIC_DIAL_Y_PAD*2))/2;
    qreal s = qSin(RADIANS(_value));
    qreal c = qCos(RADIANS(_value));

    i << QPointF(rX,rY);
    i << QPointF(c*rX,s*(rY-100));
}

void ZGenericDial::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter *p = new QPainter(this);
    QPen pen(QColor(0,0,0,255));
    qreal cX = (width()/2.0)-(ZGENERIC_DIAL_X_PAD);
    qreal cY = (height()/2.0)-(ZGENERIC_DIAL_Y_PAD);

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

        p->drawText(cX-(75/2),cY-(25/2),75,32,Qt::AlignCenter,QVariant(_value).toString());

	p->drawEllipse(ZGENERIC_DIAL_X_PAD,
		       ZGENERIC_DIAL_Y_PAD,
		       width()-(2*ZGENERIC_DIAL_X_PAD),
		       height()-(2*ZGENERIC_DIAL_Y_PAD));

        //p->drawConvexPolygon(indicator);
	p->end();
    }

    p = NULL;
}


void ZGenericDial::resizeEvent(QResizeEvent *e){
    QFrame::resizeEvent(e);
    refreshAllTicks();
}

void ZGenericDial::refreshTicks(ZDialTickRule r){
    int val = 0;
    qreal step = (_range/(_maxValue-_minValue))*r.every;
    qreal c,s;
    qreal xRadius = (width()-(ZGENERIC_DIAL_X_PAD*2))/2;
    qreal yRadius = (height()-(ZGENERIC_DIAL_Y_PAD*2))/2;
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
	_ticks[r.series].moveTo(QPointF( innerXRadius*c+xRadius+ZGENERIC_DIAL_X_PAD,
					 innerYRadius*s+yRadius+ZGENERIC_DIAL_Y_PAD));
	_ticks[r.series].lineTo(QPointF(xRadius*c+xRadius+ZGENERIC_DIAL_X_PAD,
					yRadius*s+yRadius+ZGENERIC_DIAL_Y_PAD));
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

void ZGenericDial::setValue(double value)
{
    if(value < _minValue)
	_value = _minValue;
    else if(value > _maxValue)
	_value = _maxValue;
    else
	_value = value;

    emit valueChanged(_value);
}
void ZGenericDial::setMinimum(double value)
{
    _minValue = value;
    //	calcRanges();
    emit minimumValueChanged(_minValue);
}

void ZGenericDial::setMaximum(double value)
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

QSize ZGenericDial::sizeHint()
{
    if(layout())
	return QSize(ZGENERIC_DIAL_DEFAULT_WIDTH, ZGENERIC_DIAL_DEFAULT_HEIGHT);
    return QSize(0,0);
}


void ZGenericDial::redraw()
{
    update(contentsRect());
}
