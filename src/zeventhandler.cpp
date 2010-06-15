#include "zeventhandler.h"

bool ZEventHandler::hasReceiver(QString title)
{
  if(_receivers.contains(title))
    return true;
  return false;
}

QObject *ZEventHandler::receiver(QString title)
{
  if(_receivers.contains(title)){
    //DEBUG
    //cout << "Receive Retreive: " << title.toStdString() << " -> " << _receivers.value(title)->property("element").toString().toStdString() << endl; flush(cout);
    return _receivers.value(title);
  }
  return NULL;
}

QHash<QString,QString> ZEventHandler::handlers(QString receiverTitle){
  return _handlers.value(receiverTitle);
}

QString ZEventHandler::handler(QString receiverTitle, QString event)
{
  if(_handlers.contains(receiverTitle))
    if(_handlers.value(receiverTitle).contains(event))
      return _handlers.value(receiverTitle).value(event);
  return NULL;
}

void ZEventHandler::registerReceiver(QObject *receiver, QString title)
{
  //DEBUG
  //cout << "Receive REGISTER: " << receiver->property("element").toString().toStdString() << " -> " << title.toStdString() << endl; flush(cout);
  _receivers.insert(title, receiver);
}

void ZEventHandler::addHandler(QString receiverTitle, QString event, QString arg)
{
  QHash<QString,QString> hnd;
  //DEBUG
  //cout << "Add Handler: " << receiverTitle.toStdString() << " -> " << event.toStdString() << endl; flush(cout);
  hnd.insert(event, arg);
  _handlers.insert(receiverTitle, hnd);
}


ActionDescriptor ZEventHandler::parseActionDescriptor(QString evstring){
  QStringList evCode = evstring.split("@");
  QString recv = evCode.first();            // RECEIVER
  QString cAction = evCode.last();
  QStringList lAction = cAction.split(":");
  QString action = lAction.first();         // ACTION
  QString cArguments = lAction.last();
  QStringList arguments = cArguments.split("|");
  ActionDescriptor retval;

  retval.receiver = recv;
  retval.action = action;
  retval.arguments = arguments;

  return retval;
}

void ZEventHandler::invokeEventAction(QObject *watched, QString event)
{
  QVariant adstring = watched->property(event.toUtf8().data());
  QHash<QString,QString> hnd;
  ActionDescriptor actdesc = ZEventHandler::parseActionDescriptor(adstring.toString());

  //DEBUG
  //cout << "Attempt: " << event.toStdString() << " -> " << actdesc.receiver.toStdString()
  //     << "@" << actdesc.action.toStdString() << endl; flush(cout);

  if(adstring.isValid()){
//  if receiver found...
    if(receiver(actdesc.receiver))
    {
    //	DEBUG
      cout << "\tReciever FOUND: " << actdesc.receiver.toStdString() << endl; flush(cout);

//    if a handler is registered to this receiver...
      if(_handlers.contains(actdesc.receiver)){
        hnd = _handlers.value(actdesc.receiver);

        if(hnd.contains(event))
            invokeAction(actdesc);
      }
    }
  }
}


void ZEventHandler::invokeAction(QString evstring){
  invokeAction(ZEventHandler::parseActionDescriptor(evstring));
}


void ZEventHandler::invokeAction(ActionDescriptor actdesc){
  try{
    QObject *recv;
    bool invokeRetVal = false;
//  if the receiver exists/was found...
    if((recv = receiver(actdesc.receiver)))
    {

      cout << "INVOKE: " << recv->metaObject()->className() << "@"
           << actdesc.action.toStdString()
           << " ('" << actdesc.arguments.join(", '").toStdString() << "')"
           << endl; flush(cout);

//    call the invoke() slot from across the shared library boundary
      if(QMetaObject::invokeMethod(recv,
           "invoke",
           Qt::DirectConnection,
           Q_RETURN_ARG(bool, invokeRetVal),
           Q_ARG(QString, actdesc.action),
           Q_ARG(QString, actdesc.arguments.value(0)),
           Q_ARG(QString, actdesc.arguments.value(1)),
           Q_ARG(QString, actdesc.arguments.value(2)),
           Q_ARG(QString, actdesc.arguments.value(3)),
           Q_ARG(QString, actdesc.arguments.value(4)),
           Q_ARG(QString, actdesc.arguments.value(5)))){

        if(!invokeRetVal)
          cout << "Invocation failure at receiver" << endl; flush(cout);

      }else{
        cout << "Invocation failure: "
             << actdesc.receiver.toStdString() << "@"
             << actdesc.action.toStdString()
             << " (" << recv->metaObject()->className() << ")"
             << endl; flush(cout);
      }
    }else{
      cout << "Receiver " << recv->metaObject()->className()
           << " is not a ZEvent" << endl; flush(cout);
    }
  }catch(exception& e){
    cout << "Error Fail" << endl; flush(cout);
  }
}

ConditionString ZEventHandler::parseConditionString(QString cond){
  ConditionString ret;

  QRegExp compMatch = QRegExp("==|!=|<|>|<=|>=|>\\||\\|<|~");
  QStringList conds = cond.split("?");
  ret.handler = conds.first();                        // handler
  conds.last().indexOf(compMatch);
  ret.comparator = compMatch.capturedTexts().first(); // comparator
  conds = conds.last().split(compMatch);
  ret.property = conds.first();                       // property
  ret.value = conds.last();                           // value

  return ret;
}

bool ZEventHandler::eventFilter(QObject *watched, QEvent *event)
{
  switch(event->type())
  {
    case QEvent::MouseButtonPress:
      invokeEventAction(watched, "onclick");
      break;
    default:
      QVariant a;
      if(QMetaObject::invokeMethod(watched,
                                "query",
                                Qt::DirectConnection,
                                Q_RETURN_ARG(QVariant, a),
                                Q_ARG(QString, "test")))
        break;
  }

  return false;
}
