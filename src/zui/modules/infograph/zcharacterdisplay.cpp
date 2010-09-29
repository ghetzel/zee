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

#include "zcharacterdisplay.h"

ZCharacterDisplay::ZCharacterDisplay(const ZConfig &el, QWidget *parent)
    : QFrame(parent),
      ZWidget(el,this)
{
    init();
    parse(_config);
}

void ZCharacterDisplay::init(){
    _currentLine = 0;
    _charSize.setWidth(48);
    _charSize.setHeight(72);

    setLayout(new ZFlowLayout);
    //layout()->setSpacing(0);

    zEvent->registerSlot(this, SLOT(updateDisplay()));
    zEvent->registerSlot(this, SLOT(appendLine(QString)));
    zEvent->registerSlot(this, SLOT(setText(QString)));
    zEvent->registerSlot(this, SLOT(setText(QString,int)));
    zEvent->registerSlot(this, SLOT(setLine(int)));
}

void ZCharacterDisplay::parse(const ZConfig &el){
    if(el.hasAttribute("images"))
	_charImagePath = el.attribute("images");

    if(el.hasAttribute("width") && el.hasAttribute("height"))
	_charSize = QSize(el.attribute("width").toInt(),
			  el.attribute("height").toInt());

    if(el.hasChildNodes()){
	QDomNodeList ch = el.childNodes();
	for(int i = 0; i < ch.length(); i++){
	    if(ch.at(i).toElement().tagName() == "zui:lines"){
		QDomNodeList lines = ch.at(i).childNodes();
		for(int j = 0; j < lines.length(); j++){
		    if(lines.at(j).toElement().tagName() == "zui:line"){
			QDomElement lnel = lines.at(j).toElement();
			if(!lnel.text().isEmpty()){
			    if(lnel.hasAttribute("id")){
				setText(lnel.text(),
					lnel.attribute("id").toInt());
			    }else{
				appendLine(lnel.text());
			    }
			}
		    }
		}
	    }
	}
    }

    if(_text.isEmpty())
	if(el.hasAttribute("value"))
	    setText(el.attribute("value"));
}

void ZCharacterDisplay::updateDisplay(){
    QString charFile;

    if(!_text[_currentLine].isEmpty()){
	if(_text[_currentLine].length() > _characters.length()){
	    for(int i = _characters.length(); i < _text[_currentLine].length(); i++){
		addCharacter();
	    }
	}

	for(int i = 0; i < _text[_currentLine].length(); i++){
	    if(_characters[i]){
		if(_charImagePath.isEmpty()){
		    _characters[i]->setText(_text[_currentLine].at(i));
		}else{
		    _characters[i]->setPixmap(
			    _characterImage(_text[_currentLine].at(i)));
		}
	    }
	}
    }
}

void ZCharacterDisplay::addCharacter(){
    QLabel *l = new QLabel("",this);
    l->setAlignment(Qt::AlignCenter);
    l->setFixedSize(_charSize);

    _characters << l;
    layout()->addWidget(l);
}

void ZCharacterDisplay::appendLine(QString text){
    setText(text, _text.count());
}

void ZCharacterDisplay::setText(QString text){
    setText(text, _currentLine);
}

void ZCharacterDisplay::setText(QString text, int line){
    _text[line] = text;
    updateDisplay();
}

void ZCharacterDisplay::setLine(int line){
    _currentLine = line;
    updateDisplay();
}

bool ZCharacterDisplay::_characterImageIsSvg(){
    return (_charImagePath.section(".",-1,-1).toLower() == "svg");
}

QPixmap ZCharacterDisplay::_characterImage(QChar token){
    QPixmap retval;

//  substute the current token name for the argument in the image path
//  using trsym, which provides filesystem-friendly names for otherwise
//  irritating (if not impossible) filenames
    QString fn = _charImagePath.arg(ZUtil::trsym(token));
    bool loadImage = false;

    if(!QPixmapCache::find(token, retval)){
    //  check for the existence of the file
	if(!fn.isEmpty()){
	    if(QFile::exists(fn)){
		loadImage = true;
	    }

    //  check for the existence of the fallback
	}else if(!_charFallbackPath.isEmpty()){
	    if(QFile::exists(_charFallbackPath)){
		fn = _charFallbackPath;
		loadImage = true;
	    }
	}

   //   a valid filename was found, load it
	if(loadImage){
	    retval.load(fn);
	}

   //   insert the new pixmap into the cache
	QPixmapCache::insert(token, retval);
    }

    return retval;
}

int ZCharacterDisplay::lineCount() const{
    return _text.count();
}

int ZCharacterDisplay::currentLine() const{
    return _currentLine;
}

int ZCharacterDisplay::currentLineLength() const{
    return _text[_currentLine].length();
}
