#include "zdatetime.h"

ZDateTime::ZDateTime()
{
}

QDateTime ZDateTime::strtotime(QString in){
    in = in.replace("yesterday", ZDateTime::now().addDays(-1).toString(PARSE_DATE_FMT));
    in = in.replace("today", ZDateTime::now().toString(PARSE_DATE_FMT));
    in = in.replace("tomorrow", ZDateTime::now().addDays(1).toString(PARSE_DATE_FMT));

    try{
        return QDateTime::fromTime_t(UNIXTIME(time_from_string(in.toStdString()))).toUTC();
    }catch(...){
        return QDateTime::fromTime_t(0).toUTC();
    }
}

qint64 ZDateTime::strtotime_t(QString in){
    return ZDateTime::strtotime(in).toTime_t();
}

QDateTime ZDateTime::now(){
    return QDateTime::fromTime_t(UNIXTIME(NOW()));
}

qint64 ZDateTime::now_t(){
    return UNIXTIME(NOW());
}

QDateTime ZDateTime::nowMsec(){
    qint64 nw = UNIXTIME_MS(NOW());
    return QDateTime::fromTime_t(nw/1000).addMSecs(nw%1000).toUTC();
}

qint64 ZDateTime::nowMsec_t(){
    return UNIXTIME_MS(NOW());
}


