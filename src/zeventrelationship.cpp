#include <zeventrelationship.h>


ZEventRelationship::ZEventRelationship(ZMethodObject from,
				       ZMethodObject to,
				       QList<QPair<QObject *, QString> > via,
				       bool direct)
{
    //z_log_debug("ZEventRelationship: vias: "+STR(via.count()));
    _signal = from;
    _slot = to;
    _via = via;
    _direct = direct;
    init();
}

void ZEventRelationship::init(){
//  Direct Connection
//      if specified explictly direct and there are no surrogate properties,
//      attempt to connect the named signal directly to the named slot
    if(_direct && _via.isEmpty()){
	if(_signal.isValid()){        //              signal valid
	    if(_slot.isValid()){      //              slot valid
		if(connect(_signal.object(), _signal.method(),
			   _slot.object(), _slot.method())){
		    z_log("ZEventRelationship: Connected "+
			  _signal.object()->objectName()+" to "+
			  _slot.object()->objectName());
		    return;
		}else{
		    z_log_error("ZEventRelationship: Direct Connection failure,"
				" attempting adaptive connection");
		}
	    }else{
		z_log_error("ZEventRelationship: Cannot direct connect,"
			    " invalid slot method");    return;}
	}else{
	    z_log_error("ZEventRelationship: Cannot direct connect,"
			" invalid signal method");      return;}
    }

//  Adaptive Connection
//      If surrogate properties are used, if it is explicitly requested, or if
//      a direct connection fails, attempt to connect the signal to the slot
//      through this object, which will act as an intermediary, converting data
//      types as necessary to facilitate the transfer of data from otherwise
//      incompatible signals and slots.
    QString sigsig(QMetaObject::normalizedSignature(_signal.method()));
    sigsig = sigsig.section("(",1,1);
    sigsig = "1adapter("+sigsig; //! \hack uses knowledge of Qt internals
    QString slotsig(QMetaObject::normalizedSignature(_slot.method()));
    slotsig = slotsig.section("(",1,1);
    slotsig = "2adapted("+slotsig; //! \hack uses knowledge of Qt internals
    const char *adaptSlot = qstrdup(sigsig.toAscii().data());
    const char *adaptSig = qstrdup(slotsig.toAscii().data());

//      attempt to connect signal to an internal adapter slot
//      these slots are provided for the majority of signal-type use cases
    if(connect(_signal.object(), _signal.method(), this, adaptSlot)){
//	attempt to connect a local adapter signal to slot
//      these signals are provided for the majority of slot-type use cases
	if(connect(this,adaptSig, _slot.object(),_slot.method())){
	    z_log("ZEventRelationship: Adapted "+_signal.signature()+
			" to "+_slot.signature());
	}else{
	    z_log_error("ZEventRelationship: Failed adapting local signal "+
			STR(adaptSig)+"to "+_slot.name());
	}
    }else{
	z_log_error("ZEventRelationship: "
		    "Failed adapting "+_signal.name()+" to "+_slot.name());
    }
}


void ZEventRelationship::adapter(QVariant p1, QVariant p2, QVariant p3,
				 QVariant p4, QVariant p5, QVariant p6)
{
//    z_log_debug("ZEventRelationship: adapter("+
//                p1.toString()+","+
//                p2.toString()+","+
//                p3.toString()+","+
//                p4.toString()+","+
//                p5.toString()+","+
//                p6.toString()+")");
//  1.  create arguments list populated with all valid variant args
    QList<QVariant> args;
    if(p1.isValid()){ args << p1; }
    if(p2.isValid()){ args << p2; }
    if(p3.isValid()){ args << p3; }
    if(p4.isValid()){ args << p4; }
    if(p5.isValid()){ args << p5; }
    if(p6.isValid()){ args << p6; }

//  2.  for each _via, replace elements in the arguments list
//          args:  [ a | b | c | d ]
//          vias:  [   | x |   | z ]
//          ----- -------------------
//           res:  [ a | x | c | z ]
    for(int i = 0; i < _via.count(); i++){
	QObject *o = _via.at(i).first;
    //  if the object exists...
	if(o){
	//  get the data at the given property
	    QVariant v = o->property(_via.at(i).second.toAscii().data());
	//  replace existing or append the data
	    (i < args.size()) ? args.replace(i,v) : args.append(v);
	}else{
	    z_log("ZEventRelationship: Skipping via #"+STR(i)+
		  ", object not specified.");
	}
    }

//  invoke the slot
    invokeSlot(args);
}

void ZEventRelationship::invokeSlot(QList<QVariant> args){
//  1: Get the types for the slot method
    QList<QVariant::Type> slotArgs = _slot.argTypes();

//    z_log_debug("ZEventRelationship: invokeSlot");
//    foreach(QVariant v, args)
//        z_log_debug("\t"+v.toString());

    if(_slot.object()){
	if(!_slot.name().isEmpty()){
//	    insufficient arguments
	    if(args.length() < slotArgs.length()){
		z_log_error("ZEventRelationship: Cannot invoke "+_slot.name()+" "+
			    "not enough arguments (have "+STR(args.length())+
			    ", need "+STR(slotArgs.length())+")");     return; }

//	    0 arguments
	    if(slotArgs.length() == 0){
		emit adapted();

//	    1 argument
	    }if(slotArgs.length() == 1){
		if(slotArgs.at(0) == QVariant::Int){ //		    (int)
		    emit adapted(args.at(0).toInt());
		}else if(slotArgs.at(0) == QVariant::UInt){ //	    (uint)
		    emit adapted(args.at(0).toUInt());
		}else if(slotArgs.at(0) == QVariant::LongLong){ //  (qlonglong)
		    emit adapted(args.at(0).toLongLong());
		}else if(slotArgs.at(0) == QVariant::ULongLong){ // (qulonglong)
		    emit adapted(args.at(0).toULongLong());
		}else if(slotArgs.at(0) == QVariant::Double){ //    (double)
		    emit adapted(args.at(0).toDouble());
		}else if(slotArgs.at(0) == QVariant::Bool){ //	    (bool)
		    emit adapted(args.at(0).toBool());
		}else if(slotArgs.at(0) == QVariant::Char){ //	    (QChar)
		    emit adapted(args.at(0).toChar());
		}else if(slotArgs.at(0) == QVariant::Date){ //	    (QDate)
		    emit adapted(args.at(0).toDate());
		}else if(slotArgs.at(0) == QVariant::DateTime){ //  (QDateTime)
		    emit adapted(args.at(0).toDateTime());
		}else if(slotArgs.at(0) == QVariant::String){ //    (QString)
		    emit adapted(args.at(0).toString());
		}else if(slotArgs.at(0) == QVariant::StringList){// (QStringList)
		    emit adapted(args.at(0).toStringList());
		}else if(slotArgs.at(0) == QVariant::Url){ //	    (QUrl)
		    emit adapted(args.at(0).toUrl());
		}else{
		    return;
		}

//	    2 arguments
	    }else if(slotArgs.length() == 2){
		if(slotArgs.at(0) == QVariant::Int){
		    if(slotArgs.at(1) == QVariant::Int){ //	    (int,int)
			emit adapted(args.at(0).toInt(),args.at(1).toInt());
		    }
                }else if(slotArgs.at(0) == QVariant::String){
                    if(slotArgs.at(1) == QVariant::String){ //	    (QString,QString)
                        emit adapted(args.at(0).toString(),
                                     args.at(1).toString());
                    }
                }
    //	    3 arguments
            }else if(slotArgs.length() == 3){
                if(slotArgs.at(0) == QVariant::String){
                    if(slotArgs.at(1) == QVariant::String){
                        if(slotArgs.at(2) == QVariant::String){ //  (QString,QString,QString)
                            emit adapted(args.at(0).toString(),
                                         args.at(1).toString(),
                                         args.at(2).toString());
                        }
                    }
                }
    //	    4 arguments
            }else if(slotArgs.length() == 4){
                if(slotArgs.at(0) == QVariant::String){
                    if(slotArgs.at(1) == QVariant::String){
                        if(slotArgs.at(2) == QVariant::String){
                            if(slotArgs.at(3) == QVariant::UInt){ //  (QString,QString,QString,uint)
                                emit adapted(args.at(0).toString(),
                                             args.at(1).toString(),
                                             args.at(2).toString(),
                                             args.at(3).toUInt());
                            }
                        }
                    }
                }
            }
	}else{
	    z_log_error("ZEventRelationship: Cannot invoke unnamed method of "+
			_slot.object()->objectName());
	}
    }else{
	z_log_error("ZEventRelationship: Cannot invoke unset object");
    }
}

void ZEventRelationship::adapter(bool p1){ //		(bool)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(int p1){ //		(int)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(uint p1){ //		(uint)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(qint64 p1){ //		(qint64)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(qulonglong p1){ //	(qulonglong)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(double p1){ //		(double)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(QString p1){ //	(QString)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(QStringList p1){ //	(QStringList)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(QDate p1){ //		(QDate)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(QDateTime p1){ //	(QDateTime)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(QUrl p1){ //		(QUrl)
    adapter(QVariant(p1)); }
void ZEventRelationship::adapter(int p1, int p2){ //	(int,int)
    adapter(QVariant(p1),QVariant(p2)); }

