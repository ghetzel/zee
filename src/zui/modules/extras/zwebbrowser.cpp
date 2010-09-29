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

#include "zwebbrowser.h"

ZWebBrowser::ZWebBrowser(const ZConfig &el, QWidget *parent)
  : QWebView(parent),
    ZWidget(el,this){
  init();
}

ZWebBrowser::ZWebBrowser(QString uri, const ZConfig &el, QWidget *parent)
  : QWebView(parent),
  ZWidget(el,this){
  init();
  load(uri);
}

ZWebBrowser::ZWebBrowser(QUrl uri, const ZConfig &el, QWidget *parent)
  : QWebView(parent),
    ZWidget(el,this){
  init();
  load(uri.toString());
}

void ZWebBrowser::init(){
    zEvent->registerSignal(this,SIGNAL(titleChanged(QString)));
    zEvent->registerSignal(this,SIGNAL(urlChanged(QUrl)));
    zEvent->registerSignal(this,SIGNAL(statusBarMessage(QString)));
    zEvent->registerSignal(this,SIGNAL(selectionChanged()));
    zEvent->registerSignal(this,SIGNAL(loadStarted()));
    zEvent->registerSignal(this,SIGNAL(loadProgress(int)));
    zEvent->registerSignal(this,SIGNAL(loadFinished(bool)));
    zEvent->registerSignal(this,SIGNAL(iconChanged()));
    zEvent->registerSlot(this,SLOT(load(QString)));
    zEvent->registerSlot(this,SLOT(back()));
    zEvent->registerSlot(this,SLOT(forward()));
    zEvent->registerSlot(this,SLOT(reload()));
    zEvent->registerSlot(this,SLOT(stop()));

//  transparent webpages
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Base, Qt::transparent);
    page()->setPalette(palette);
    setAttribute(Qt::WA_OpaquePaintEvent, false);
    setAttribute(Qt::WA_TranslucentBackground, true);

//  enable features
    QWebSettings::globalSettings()->setAttribute(
	QWebSettings::JavascriptEnabled, true);
    QWebSettings::globalSettings()->setAttribute(
	QWebSettings::PluginsEnabled, true);

    parse(_config);
    show();
    load();
}

void ZWebBrowser::parse(const ZConfig &el){
    if(el.hasAttribute("uri"))
	setHome(el.attribute("uri"));
}

void ZWebBrowser::load(QString url){
    if(url.isEmpty())
	QWebView::load(_home);
    else
	QWebView::load(QUrl::fromUserInput(url));
}

void ZWebBrowser::setHome(QString url){
    _home = QUrl::fromUserInput(url);
}
