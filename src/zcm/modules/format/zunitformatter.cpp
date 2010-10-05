#include "zunitformatter.h"

ZUnitFormatter::ZUnitFormatter(QObject *parent)
    : ZAbstractFormatter(parent)
{
    _utInitCode = utInit(ZUNIT_UT_DBPATH);
}

void ZUnitFormatter::transform(QVariant in){
    if(_utInitCode == UT_SUCCESS){
	utUnit res;
        utInit();
	utScan("5 feet in inches", &res);

//	z_log_debug("ZUnitFormatter: "+STR(res.unit2));
    }else{
	z_log_error("ZUnitFormatter: Unable to initialize udunits with error "
		    "code "+STR(_utInitCode));
    }
}
