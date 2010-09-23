#ifndef ZDATETIME_H
#define ZDATETIME_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <QtGlobal>
#include <QDebug>
#include <QString>
#include <QDateTime>

#define ZLDT_PARSE_DATE_FMT         "yyyy-MM-dd"
#define ZLDT_PARSE_TIME_MIDNGHT_FMT "00:00:00"
#define ZLDT_PARSE_TIME_MIDDAY_FMT  "12:00:00"
#define ZLDT_PARSE_TIME_TEATIME_FMT "16:00:00"

#define ZLDT_PARSE_CONV_FMT         "yyyy-MM-ddThh:mm:ss"
#define ZLDT_PARSE_CONV_MS_FMT      "yyyy-MM-ddThh:mm:ss.zzz000"

#define ZLDT_DATE_REL_TODAY         "today"
#define ZLDT_DATE_REL_TOMORROW      "tomorrow"
#define ZLDT_DATE_REL_YESTERDAY     "yesterday"

#define EPOCH_DATE()                date(1970,1,1)
#define EPOCH_DIFF(x)               time_duration(ptime(x)-ptime(EPOCH_DATE()))

#define UNIXTIME(x)                 EPOCH_DIFF(x).total_seconds()
#define UNIXTIME_NS(x)              EPOCH_DIFF(x).total_nanoseconds()
#define UNIXTIME_US(x)              EPOCH_DIFF(x).total_microseconds()
#define UNIXTIME_MS(x)              EPOCH_DIFF(x).total_milliseconds()

#define NOW()                       second_clock::universal_time()
#define NOW_US()                    microsec_clock::universal_time()
#define NOW_MS()                    NOW_US()



#define PTIME_TO_QDATETIME_FMT(x,f) QDateTime::fromString(QString::fromStdString(to_iso_extended_string(x)),f)
#define PTIME_TO_QDATETIME(x)       PTIME_TO_QDATETIME_FMT(x,ZLDT_PARSE_CONV_FMT)
#define PTIME_TO_QDATETIME_MS(x)    PTIME_TO_QDATETIME_FMT(x,ZLDT_PARSE_CONV_MS_FMT)

using namespace boost::posix_time;
using namespace boost::gregorian;

class ZDateTime
{
public:
    ZDateTime();
    static QDateTime fromUnix(qint64);
    static QDateTime fromUnixMsec(qint64);
    static QDateTime strtotime(QString);
    static qint64 strtotime_t(QString);
    static QDateTime now();
    static QDateTime nowMsec();
    static qint64 now_t();
    static qint64 nowMsec_t();
    static qint64 nowUsec_t();
    static qint64 secondsTo(QString target);
    static qint64 secondsTo(QDateTime target);
    static qint64 msecsTo(QString target);
    static qint64 msecsTo(QDateTime target);

private:
    static void _parseFormatString(QString &in);
};

#endif // ZDATETIME_H
