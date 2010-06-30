#include "zexecutor.h"

ZExecutor::ZExecutor(const ZConfig &el, QObject *parent)
    : QObject(parent),
      ZConfigurable(el,this)
{
    parse(_config);
    zEvent->registerSignal(this, SIGNAL(executed(QString)));
    zEvent->registerSignal(this, SIGNAL(commandChanged(QString)));
    zEvent->registerSignal(this, SIGNAL(commandChanged(QString,QString)));
    zEvent->registerSlot(this, SLOT(exec()));
    zEvent->registerSlot(this, SLOT(setCommand(QString)));
}

ZExecutor::~ZExecutor(){
    _command = "";
}

void ZExecutor::parse(const ZConfig &el){
    if(el.text().isEmpty()){
        if(el.hasAttribute("value")){
            _command = el.attribute("value");
        }
    }else{
        _command = el.text();
    }

    if(el.hasAttribute("oneline"))
        if(!el.attribute("oneline").isEmpty())
            _oneLine = el.attribute("oneline");
}

void ZExecutor::exec(){
    if(_command.isEmpty())
        z_log_error("ZExecutor: No command specified.");
    else
        if(_oneLine.isEmpty())
            emit executed(ZUtil::exec(_command));
        else
            emit executed(ZUtil::execln(_command,_oneLine));
}

void ZExecutor::setCommand(QString command){
    QString oldCmd = _command;
    _command = command;
    emit commandChanged(command, oldCmd);
}
