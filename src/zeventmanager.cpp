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
        z_log_debug("ZEventManager: Object not specified, skip register");
        return; }
    if(!method){
        z_log_error("ZEventManager: Method not specified, skip register");
        return; }
    if(object->objectName().isEmpty()){
        //z_log_debug("ZEventManager: Object name not specified, skip register");
        return; }
/*  ------------------------------------------------------------------------- */

    switch(type){
    case QMetaMethod::Signal:
        insertMethod(object, method, _signals);
        break;
    case QMetaMethod::Slot:
        insertMethod(object, method, _slots);
        break;
    default:
        z_log_error("ZEventManager: Only signals and slots can be registered");
        return;
    }
}

void ZEventManager::registerSignal(QObject *source, const char *signal){
    registerMethod(QMetaMethod::Signal,source,signal);
}

void ZEventManager::registerSlot(QObject *receiver, const char *slot){
    registerMethod(QMetaMethod::Slot,receiver,slot);
}

void ZEventManager::map(QString from, QString to, QString via,
                        QString formatters, bool direct)
{
    QObject *senderObj=0;
    ZEventObject sender;
    ZEventObject receiver;
    QList<QPair<QObject*,QString> > viaProperties;
    QList<ZFormatterInterface*> fmts;
    QStringList vias = via.split(ZEV_POSITIONAL_SEPARATOR);

    senderObj = findObject(from);
    sender = _signals.value(senderObj);
    receiver = _slots.value(findObject(to));


//  populate via (surrogate) properties
    if(!via.isEmpty()){
        foreach(QString v, vias){
            QObject *propobj = findObject(v,false,senderObj);
            if(propobj){
                viaProperties << qMakePair(propobj, CALLALIAS(v));
            }else{
                viaProperties.append(QPair<QObject*,QString>(NULL,QString()));
            }
        }
    }

//  populate formatters
    if(!formatters.isEmpty()){
        foreach(QString f, formatters.split(ZEV_POSITIONAL_SEPARATOR)){
            if(f.isEmpty()){
                fmts << NULL;
                continue;
            }

            QObject *fmt = findObject(f,true); // find the formatter object

            if(DCAST(ZFormatterInterface*,fmt)){ // if it is a formatter, add it
                fmts << DCAST(ZFormatterInterface*,fmt);
            }else{ // otherwise, fill its place
                z_log_error("ZEventManager: Illegal formatter specified ("+f+")");
                fmts << NULL;
            }
        }
    }

//    z_log_debug("ZEventManager: via STR: "+via);
//    z_log_debug("ZEventManager: via IN: "+STR(vias.count()));
//    z_log_debug("ZEventManager: via OUT: "+STR(viaProperties.count()));

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
                ZEventObject::ZMethodPair matchedPair;
                matchedPair = ZEventObject::matchMethodsBySignature(
                        sender.methods(CALLALIAS(from)),
                        receiver.methods(CALLALIAS(to)),
                        true,
                        via);
                if(! (matchedPair.first.isValid() &&
                      matchedPair.second.isValid())){
                    z_log_error("ZEventManager: Could not find compatible "
                                "signal-slot pair.");
                    return; }

                signal = matchedPair.first;
                slot = matchedPair.second;
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
                                                    fmts, direct));
        }else{
            z_log_error("ZEventManager: Cannot map, receiving object not found ("+to+")");
            return;
        }
    }else{
        z_log_error("ZEventManager: Cannot map, sending object not found ("+from+")");
        return;
    }
}


QObjectList ZEventManager::findChildObjects(QObject *parent, QString path, int depth){
    QObjectList rv;
    QString pathPart;
    QStringList parts = path.split(ZEV_SEPARATOR);

    //z_log_debug("ZEventManager: Finding child objects for path "+path+" at depth "+STR(depth)+" in parent "+parent->objectName());

    if(depth < parts.length()){
        pathPart = parts.at(depth);

        //z_log_debug("ZEventManager: PART "+STR(pathPart));

        foreach(QObject* child, parent->children()){
        //  simple ID check
            if(child->objectName() == pathPart){
                z_log_debug("ZEventManager: Object "+pathPart+" found at depth "+STR(depth));
                rv.append(child);
                rv.append(findChildObjects(child, path, depth+1));
            }else{
            //  nothing was found at this level, rebase at the next level and search there
                rv.append(findChildObjects(child, path, depth));
            }


        //  else if class name matches path part class specifier
        //  else if some other criteria...
        //  this was an accident, and possibly brilliant
        }
    }

    return rv;
}


QObject *ZEventManager::findObject(QString path, bool objectOnly, QObject *parent)
{
    QObjectList ol = findAllObjects(path, objectOnly, parent);

    if(!ol.isEmpty())
        return ol.last();

    return NULL;
}

QObjectList ZEventManager::findAllObjects(QString path, bool objectOnly, QObject *parent){
    QObjectList rv;
    QStringList parts = path.split(ZEV_SEPARATOR);
    QString prepPath;

//  all valid paths must be at least two parts, or one if no method is given
    if( (!objectOnly && parts.length() > 1) || (objectOnly && parts.length() > 0) ){
    //  if the first part is the app root, discard it (we already search qApp's
    //  children anyway)
        if(parts.at(0) == ZEE_OBJNAME){
            parts.removeFirst();
        }

        if(!objectOnly){
            parts.removeLast();
        }

    //  the first part is empty, therefore relative to parent
        if(parts.at(0).isEmpty()){
        //  parent was specified, continue...
            if(parent){
                z_log_debug("ZEventManager: Relative path specified, using parent '"+parent->objectName()+"'");

                parts.prepend(parent->objectName());
                prepPath = parts.join(ZEV_SEPARATOR);
                rv.append(findChildObjects(parent, prepPath));
            }else{
                z_log_error("ZEventManager: Cannot return relative path '"+path+"' without a parent object");
            }
        }else{
            z_log_debug("ZEventManager: Absolute path specified, using parent '"+STR(ZEE_OBJNAME)+"'");

            prepPath = parts.join(ZEV_SEPARATOR);

       //   search qApp itself for the path (zee:components)
            rv.append(findChildObjects(qApp, prepPath));

       //   search qApp's top-level widgets for the path (zee:widgets)
            foreach(QObject *o, qApp->topLevelWidgets()){
                rv.append(findChildObjects(o, prepPath));
            }
        }
    }

    return rv;
}

QVariant ZEventManager::getProperty(QString methodString){
    if(methodString.isEmpty())
        return QVariant();

    QObject *obj = ZEventManager::findObject(methodString);
    if(obj)
        return obj->property(CSTR(methodString.section(ZEV_SEPARATOR,-1,-1)));
    return QVariant();
}
