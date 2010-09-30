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

#include "zwindow.h"

ZWindow::ZWindow(const ZConfig &el, QWidget *parent)
    : QFrame(parent),
      ZContainerWidget(el,this)
{
    init();
}

QWidget *ZWindow::rootSurface(){
    return _rootSurface;
}

void ZWindow::init(){
    parse(_config);
    zEvent->registerSignal(this,SIGNAL(clicked(int,int)));
    zEvent->registerSignal(this,SIGNAL(released(int,int)));
    zEvent->registerSignal(this,SIGNAL(doubleClicked(int,int)));
    zEvent->registerSignal(this,SIGNAL(hover(int,int)));
    zEvent->registerSlot(this,SLOT(setWindowTitle(QString)));
    zEvent->registerSlot(this,SLOT(close()));
    zEvent->registerSlot(this,SLOT(show())); //! \bug segfaults when called, possibly only on 64-bit
}

void ZWindow::parse(const ZConfig &el){
    QString wWidth, wHeight;

    setWindowTitle(el.attribute("title", qApp->applicationName()));
    setMouseTracking(true);

//  set object name if not set
    if(objectName().isEmpty())
	setObjectName(ZUI_APP_DEFAULT_NAME);

//  only allow translucent backgrounds for apps... 8-{ ...with style...
//  YYEEEEEEEEEEEEEAAAAAAAAAAAHHHHHHHHHHHHH!!!!!
    if(!qApp->styleSheet().isEmpty()){
	setAttribute(Qt::WA_TranslucentBackground);
    }

    if(param("iconTheme").isValid())
	QIcon::setThemeName(param("iconTheme").toString());

    if(el.hasAttribute("icon") && QFile::exists(el.attribute("icon")))
	setWindowIcon(QPixmap(el.attribute("icon")));
    else
	setWindowIcon(QIcon(":/icons/zee.svg"));

//  set frameless window preference
    if(el.hasAttribute("frame") && el.attribute("frame") == "false")
	setWindowFlags(Qt::FramelessWindowHint);

    if(el.hasAttribute("hidden") && el.attribute("hidden") == "true")
	setVisible(false);
    else
	setVisible(true);

//  set desktop drawing
#ifdef Q_WS_X11
    if(el.hasAttribute("type") && el.attribute("type") != "normal"){
	if(el.attribute("type") == "desktop"){
	    setAttribute(Qt::WA_X11NetWmWindowTypeDesktop);
	}else if(el.attribute("type") == "dock"){
	    setAttribute(Qt::WA_X11NetWmWindowTypeDock);
	}else if(el.attribute("type") == "overlay"){
	    setAttribute(Qt::WA_TransparentForMouseEvents);
	}
    }
#endif

//  set window size and position on the screen
    if(el.hasAttribute("width") && el.hasAttribute("height")){
	QDesktopWidget *desktop = QApplication::desktop();
	int dW = desktop->width(), dH = desktop->height();  // Desktop WxH
	int zW = width(), zH = height();                    // width, height
	int dX = -1, dY = -1;                               // x,y
	float pX = 0.0, pY = 0.0;                           // offset x,y

//      fixed size or percentages?
	//!   \todo make the application x/y/width/height calculations a utility func.
//      x: +/-
	if(el.attribute("x","").contains("%"))
	    pX = dW * (el.attribute("x").remove("%").toFloat()/100.0);
	else
	    pX = el.attribute("x","0").toInt();

//      y: +/-
	if(el.attribute("y","").contains("%"))
	    pY = dH * (el.attribute("y").remove("%").toFloat()/100.0);
	else
	    pY = el.attribute("y","0").toInt();

//      width
	if(el.attribute("width").contains("%"))
	    zW = desktop->width() * (el.attribute("width").remove("%").toFloat()/100.0);
	else
	    zW = el.attribute("width").toUInt();

//      height
	if(el.attribute("height").contains("%"))
	    zH = desktop->height() * (el.attribute("height").remove("%").toFloat()/100.0);
	else
	    zH = el.attribute("height").toUInt();

//      set window position
	QString pos = el.attribute("position", "");
	if(!pos.isEmpty()){
	    if(pos == "nw"){
		dX = 0+pX; dY = 0+pY;
	    }else if(pos == "ne"){
		dX = (dW-zW)+pX; dY = 0+pY;
	    }else if(pos == "se"){
		dX = (dW-zW)+pX; dY = (dH-zH)+pY;
	    }else if(pos == "sw"){
		dX = 0+pX; dY = (dH-zH)+pY;
	    }else if(pos == "n"){
		dX = ((dW-zW)/2)+pX; dY = 0+pY;
	    }else if(pos == "s"){
		dX = ((dW-zW)/2)+pX; dY = (dH-zH)+pY;
	    }else if(pos == "e"){
		dX = (dW-zW)+pX; dY = ((dH-zH)/2)+pY;
	    }else if(pos == "w"){
		dX = 0+pX; dY = ((dH-zH)/2)+pY;
	    }else if(pos == "center"){
		dX = ((dW-zW)/2)+pX; dY = ((dH-zH)/2)+pY;
	    }
	}else{
	    dX = 0+pX;
	    dY = 0+pY;
	}

	//!   default: window is resizable
	if(el.hasAttribute("resizable") && el.attribute("resizable") == "false"){
	    setFixedWidth(zW);
	    setFixedHeight(zH);
	}else{
	    resize(zW, zH);
	}

	//  only move the window if we specified where to
	if(el.hasAttribute("x") || el.hasAttribute("y") || el.hasAttribute("position"))
	    move(dX, dY);
    }

    _rootSurface = new ZRoot(_config,this);
    _rootSurface->setObjectName("root");
    _rootSurface->setAutoFillBackground(true);
    //setLayout(new QHBoxLayout);
    layout()->setSpacing(0);
    layout()->setMargin(0);
    layout()->addWidget(_rootSurface);
}

void ZWindow::mousePressEvent(QMouseEvent *e){
    emit clicked(e->pos().x(), e->pos().y());
}

void ZWindow::mouseMoveEvent(QMouseEvent *e){
    emit hover(e->pos().x(), e->pos().y());
}

void ZWindow::mouseReleaseEvent(QMouseEvent *e){
    emit released(e->pos().x(), e->pos().y());
}

void ZWindow::mouseDoubleClickEvent(QMouseEvent *e){
    emit doubleClicked(e->pos().x(), e->pos().y());
}
