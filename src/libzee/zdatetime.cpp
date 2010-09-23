#include "zdatetime.h"

ZDateTime::ZDateTime()
{
}

QDateTime ZDateTime::fromUnix(qint64 sec){
    ptime tm(EPOCH_DATE(),seconds(sec));
    return PTIME_TO_QDATETIME(tm);
}

QDateTime ZDateTime::fromUnixMsec(qint64 msec){
    ptime tm(EPOCH_DATE(),milliseconds(msec));
    QDateTime rv(PTIME_TO_QDATETIME_MS(tm));
    return rv.addMSecs(msec%1000);
}

QDateTime ZDateTime::strtotime(QString in){
    ZDateTime::_parseFormatString(in);

    try{
        return PTIME_TO_QDATETIME(time_from_string(in.toStdString()));
    }catch(...){
        return QDateTime();
    }
}

qint64 ZDateTime::strtotime_t(QString in){    
    QDateTime rv = ZDateTime::strtotime(in);
    if(rv.isValid())
        return rv.toTime_t();
    return -1;
}

QDateTime ZDateTime::now(){
    return QDateTime::fromTime_t(UNIXTIME(NOW()));
}

qint64 ZDateTime::now_t(){
    return UNIXTIME(NOW());
}

QDateTime ZDateTime::nowMsec(){
    qint64 nw = UNIXTIME_MS(NOW_MS());
    return QDateTime::fromTime_t(nw/1000).addMSecs(nw%1000);
}

qint64 ZDateTime::nowMsec_t(){
    return UNIXTIME_MS(NOW_MS());
}

qint64 ZDateTime::nowUsec_t(){
    return UNIXTIME_US(NOW_US());
}

qint64 ZDateTime::secondsTo(QString target){
    ptime then(EPOCH_DATE(),seconds(ZDateTime::strtotime_t(target)));
    time_duration rv = (then - NOW());
    return rv.total_seconds();
}

qint64 ZDateTime::secondsTo(QDateTime target){
    ptime then(EPOCH_DATE(),seconds(target.toTime_t()));
    time_duration rv = (then - NOW());
    return rv.total_seconds();
}


void ZDateTime::_parseFormatString(QString &in){
    in = in.replace("yesterday", ZDateTime::nowMsec().addDays(-1).toString(ZLDT_PARSE_DATE_FMT));
    in = in.replace("today", ZDateTime::nowMsec().toString(ZLDT_PARSE_DATE_FMT));
    in = in.replace("tomorrow", ZDateTime::nowMsec().addDays(1).toString(ZLDT_PARSE_DATE_FMT));
    in = in.replace("midnight", ZLDT_PARSE_TIME_MIDNGHT_FMT);
    in = in.replace("midday", ZLDT_PARSE_TIME_MIDDAY_FMT);
    in = in.replace("noon", ZLDT_PARSE_TIME_MIDDAY_FMT);
    in = in.replace("teatime", ZLDT_PARSE_TIME_TEATIME_FMT);
}

qint64 ZDateTime::msecsTo(QString target){
    QDateTime tgVal = ZDateTime::strtotime(target);
    ptime then(EPOCH_DATE(),seconds(tgVal.toTime_t())+milliseconds(tgVal.time().msec()));
    time_duration rv = (then-NOW_MS());
    return rv.total_milliseconds();
}

qint64 ZDateTime::msecsTo(QDateTime target){
    ptime then(EPOCH_DATE(),seconds(target.toTime_t())+milliseconds(target.time().msec()));
    time_duration rv = (then-NOW_MS());
    return rv.total_milliseconds();
}
