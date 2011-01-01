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

#include "zpolystateindicator.h"

ZPolystateIndicator::ZPolystateIndicator(const ZConfig &el, QWidget *parent)
    : QLabel(parent),
      ZWidget(el,this)
{
    parse(_config);
    init();
}

void ZPolystateIndicator::init(){
    zEvent->registerSignal(this, SIGNAL(stateChanged(QString)));
    zEvent->registerSlot(this, SLOT(setImage(QString,QString)));
    zEvent->registerSlot(this, SLOT(switchTo(QString)));
    zEvent->registerSlot(this, SLOT(setValue(double)));
    zEvent->registerSlot(this, SLOT(clear()));
    zEvent->registerSlot(this, SLOT(reset()));
}

void ZPolystateIndicator::parse(const ZConfig &el){
    if(el.hasAttribute("align"))
        setAlignment(ZuiUtils::getAlignment(el.attribute("align")));

    _defaultState = el.attribute("default");

    foreach(const ZConfig state, el.firstChild("zui:states").children("zui:state")){
        QPair<double,double> range;
        setImage(state.attribute("name"), state.value());

        range.first = state.attribute("min", "-1.0").toDouble();
        range.second = state.attribute("max", "-1.0").toDouble();
        _ranges.insert(state.attribute("name"), range);
    }

    if(!_defaultState.isEmpty())
        switchTo(_defaultState);
}

QString ZPolystateIndicator::state(){
    return _currentState;
}

QPixmap ZPolystateIndicator::currentImage(){
    return _images.value(_currentState).pixmap(width()-ZPOLYIC_PAD_X,
                                               height()-ZPOLYIC_PAD_Y);
}

void ZPolystateIndicator::resizeEvent(QResizeEvent*){
    setPixmap(currentImage());
}

void ZPolystateIndicator::setImage(QString name, QString icon){
    _images.insert(name, ZuiUtils::getIcon(icon));
}

void ZPolystateIndicator::switchTo(QString name){
    if(_images.contains(name)){
        _currentState = name;
        setPixmap(currentImage());
        emit stateChanged(_currentState);
    }else{
        z_log_error("ZPolystateIndicator: State '"+name+"' does not exist.");
    }
}

void ZPolystateIndicator::setValue(double value){
    _value = value;

    foreach(QString state, _ranges.keys()){
        QPair<double,double> range = _ranges.value(state);
        if(value >= range.first && value <= range.second){
            switchTo(state);
            return;
        }
    }
}

void ZPolystateIndicator::reset(){
    if(!_defaultState.isEmpty())
        switchTo(_defaultState);
    else
        clear();
}

void ZPolystateIndicator::clear(){
    _value = 0;
    _currentState = QString();
    setPixmap(QPixmap());
    emit stateChanged(_currentState);
}
