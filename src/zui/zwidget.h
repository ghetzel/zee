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

#ifndef ZWIDGET_H
#define ZWIDGET_H

#define ZWIDGET_DEFAULT_STATE       "default"

#include <QtCore>
#include <QtGui>
#include <QStateMachine>
#include <QState>
#include <zconfigurable.h>
#include <zeventmanager.h>
#include <zui/zuiutils.h>

template<class Z>
class ZWidget: public Z, public ZConfigurable
{

public:
    ZWidget(const ZConfig &el, QWidget *self, QWidget *parent=0)
	: Z(parent),
	  ZConfigurable(el,self)
    {
	parse(_config);

        QWidget *t_Widget = NULL;
        if( (t_Widget = QCAST(QWidget*,this)) ){
            zEvent->registerSlot(t_Widget, SIGNAL(setDisabled(bool)));
        }
    }

private:
    void parse(const ZConfig &el){
    //	tell the object what element spawned it (for style ~*MAGIC*~)
	_self->setProperty("element", QVariant(el.tagName()));

    //	set style classes
	if(el.hasAttribute("class"))
	    _self->setProperty("cls", QVariant(el.attribute("class").split(" ")));

    //  build any additional states specified, populating each state with its
    //  target properties and values
    //  ...
	foreach(QDomElement cel, childElements("zui:state")){
	    //if(cel.hasAttribute("name"))
	}
    }

    void initDefaultState(){
    //  build the default state, populating it with the post-initialize values
    //  of any properties being watched from any other state.
    //
    //  Example:
    //      on parse:
    //          add state 'warning'
    //              this.color = 'yellow'       --> properties << "color"
    //          add state 'critical'
    //              this.color = 'red'
    //              this.sound = 'critical.wav' --> properties << "sound"
    //
    //      on initDefaultState:
    //          add state 'default'
    //              foreach properties:
    //                  defaultState.assignProperty ( name , currentValue )
    //
    //      We know to store the 'color' property because other specified
    //      states explicitly change it.
    //
	if(!_monitoredProperties.isEmpty()){
	    QState *state = new QState();

	    foreach(QString p, _monitoredProperties){
		if(_self)
		    state->assignProperty(_self,
					  p.toLatin1().data(),
					  _self->property(p.toLatin1().data()));
	    }

	    _states.insert(ZWIDGET_DEFAULT_STATE, state);
	    _stateMachine.addState(state);
	    _stateMachine.setInitialState(state);
	}
    }

private:
    QStringList _monitoredProperties;
    QStateMachine _stateMachine;
    QHash<QString,QState*> _states;
};

#endif // ZWIDGET_H
