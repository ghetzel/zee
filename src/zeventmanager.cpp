#include <zeventmanager.h>

ZEventManager *ZEventManager::_instance = 0;

void ZEventManager::init()
{
    QObject::setParent(qApp);
}

void ZEventManager::initialize(ZEventManager *instance){
    _instance = instance;
    _instance->init();
}

ZEventManager *ZEventManager::instance()
{
    if(!_instance)
	ZEventManager::initialize(new ZEventManager());
    return _instance;
}

void ZEventManager::insertMethod(QObject *object, const char *method,
				 QHash<QObject *, ZEventObject> &store)
{
    ZEventObject zeo;
    if(store.contains(object)){
	zeo = store.take(object);
	zeo.addMethod(method);
    }else{
	zeo = ZEventObject(object,method);
    }

    store.insert(object,zeo);
    //z_log_debug("ZEventManager: Register method "+QString(method)+", store="+QVariant(store.count()).toString());
}

void ZEventManager::registerMethod(QMetaMethod::MethodType type,
				   QObject *object, const char *method)
{
    //  some sanity checks
    if(!object){
	z_log_error("ZEventManager: Object not specified, skip register");
	return; }
    if(!method){
	z_log_error("ZEventManager: Method not specified, skip register");
	return; }
    if(object->objectName().isEmpty()){
	z_log_error("ZEventManager: Object name not specified, skip register");
	return; }
/*  ------------------------------------------------------------------------- */
    bool isSignal = false;

    switch(type){
    case QMetaMethod::Signal:
	isSignal = true;
	break;
    case QMetaMethod::Slot:
	isSignal = false;
	break;
    default:
	z_log_error("ZEventManager: Only signals and slots can be registered");
	return;
    }

//  insert the data into the registration object
/*! \bug    this doesnt work...the registration needs to be keyed by both the
	    object pointer AND the method name.  this gives a unique entry
	    for all objects and their signals/slots (multiples for different
	    argument signatures)

	    (ZLabel,setText) -->  <data>

	    when accessing, pass a QPair composed of object pointer and the
	    method name, this will return the first [value()] or all [values()]
            of the signals/slots.  pass those to the relationship class

2010-07-28 (GWH): is this still true?
  */
    if(isSignal)
	insertMethod(object, method, _signals);
    else
	insertMethod(object, method, _slots);

}

void ZEventManager::registerSignal(QObject *source, const char *signal){
    registerMethod(QMetaMethod::Signal,source,signal);
}

void ZEventManager::registerSlot(QObject *receiver, const char *slot){
    registerMethod(QMetaMethod::Slot,receiver,slot);
}

void ZEventManager::map(QString from, QString to, QString via, bool direct)
{
    ZEventObject sender;
    ZEventObject receiver;
    QList<QPair<QObject*,QString> > viaProperties;
    QStringList vias = via.split(",");

    sender = _signals.value(findObject(from));
    receiver = _slots.value(findObject(to));


    if(!via.isEmpty()){
	foreach(QString v, vias){
	    QObject *propobj = findObject(v);
	    if(propobj)
		viaProperties << qMakePair(propobj, CALLALIAS(v));
	    else
		viaProperties.append(QPair<QObject*,QString>(NULL,QString()));
	}
    }

    z_log_debug("ZEventManager: via STR: "+via);
    z_log_debug("ZEventManager: via IN: "+STR(vias.count()));
    z_log_debug("ZEventManager: via OUT: "+STR(viaProperties.count()));

    if(sender.isValid()){
       if(receiver.isValid()){
	   ZMethodObject signal, slot;
	   if(direct && viaProperties.isEmpty()){
	       ZEventObject::ZMethodPair methodMatch = sender.match(
		       CALLALIAS(from), CALLALIAS(to),
		       receiver);

	       signal = methodMatch.first;
	       slot = methodMatch.second;
	   }else{
	    // by arbitratily choosing the first method from each, it may lead to
	    // trying to adapt an unadaptable type when an adaptable alternative
	    // exists
		QList<ZMethodObject> m;
		m = sender.methods(CALLALIAS(from));
		if(!m.isEmpty()){
		    signal = m.first();
		}else{
		    z_log_error("ZEventManager: No signals found for '"+
				CALLALIAS(from)+"'");
		    return; }

		m = receiver.methods(CALLALIAS(to));
		if(!m.isEmpty()){
		    slot = m.first();
		}else{
		    z_log_error("ZEventManager: No slots found for '"+
				CALLALIAS(to)+"'");
		    return; }
	   }

	   if(!signal.isValid()){
	       z_log_error("ZEventManager: No direct match for signal found.");
	       return; }
	   if(!slot.isValid()){
	       z_log_error("ZEventManager: No direct match for slot found.");
	       return; }

//	    by this point, we have verfied the presence of all necessary arguments,
//	    found the objects in the hierarchy, retreived the methods for those
//	    objects...let's map the damned connection already
	    _mappings.append(new ZEventRelationship(signal, slot, viaProperties,
						direct));
	}else{
	    z_log_error("ZEventManager: Cannot map, receiving object not found ("+to+")");
	    return;
	}
    }else{
	z_log_error("ZEventManager: Cannot map, sending object not found ("+from+")");
	return;
    }
}



QObject *ZEventManager::findObject(QString methodString, bool objectOnly){
    QObject *obj = NULL;
    QObject *rv = NULL;
    QString oname;
    QStringList proc;
    bool foundIt = false; // WHOOP! Found the Tank!

//  split the method specifier on the configured separator
//	zee.container.object.method -->  [zee, container, object, method]
    proc = methodString.split(ZEV_SEPARATOR,QString::SkipEmptyParts);

//  if that string was not splittable, return empty
    if(proc.isEmpty()){
	z_log_error("ZEventManager: Cannot map, no object specified");
	return NULL;
    }else{
	if(!objectOnly){
    //	omit the last argument (the method name itself)
	    proc.removeLast();
	}

//	and the last element here now is the object we're ultimately looking for
	oname = proc.last();

//	if the first element is 'zee', the remove it (if this code is running,
//	then 'zee' is assumed...what a mind-job)
//      then set the current object to the application
	if(proc.first() == ZEE_OBJNAME){
	    proc.removeFirst();
	    rv = qApp;
	}

	if(!proc.isEmpty()){
//          search the app and each top-level window for a match
	    QList<QObject*> objs;
	    objs << qApp;
	    foreach(QObject *o, qApp->topLevelWidgets())
		objs << o;

	    foreach(QObject *top, objs){
		rv = top;
//	    for each element to be searched (in succession)...
		foreach(QString o, proc){
//		if we or one of our children is the object being searched for,
//		we have found the object at this level, move on to the next one,
//		wherein only this found object will be searched for the next tier
		    if(((obj = (rv->objectName() == o ? rv : NULL)) ||
			(obj = rv->findChild<QObject*>(o)))
		     ){
			z_log_debug("ZEventManager: Found '"+o+"', moving on...");
			foundIt = true;
			rv = obj;

		    }else{
//		the next tier was not found within the given parent, exit and
//		try the next window
			z_log_debug("ZEventManager: No '"+o+"', staying "+rv->objectName());
			foundIt = false;
			break;
		    }
		}

//	    if we have found what we are looking for, stop searching
		if(foundIt)
		    break;
	    }
	}

	if(rv->objectName() == oname)
	    z_log_debug("ZEventManager: Found '"+methodString+"', "
			"it's a "+QString(rv->metaObject()->className()));
	else
	    return NULL;
    }

    return rv;
}
