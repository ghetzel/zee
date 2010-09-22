#ifndef ZDATETIME_H
#define ZDATETIME_H

#include <boost/date_time/posix_time/posix_time.hpp>
#include <QtGlobal>
#include <QDebug>
#include <QString>
#include <QDateTime>

#define EPOCH_DIFF(x)       time_duration(ptime(x)-ptime(date(1970,1,1)))

#define UNIXTIME(x)         EPOCH_DIFF(x).total_seconds()
#define UNIXTIME_MS(x)      EPOCH_DIFF(x).total_milliseconds()
#define UNIXTIME_US(x)      EPOCH_DIFF(x).total_microseconds()
#define UNIXTIME_NS(x)      EPOCH_DIFF(x).total_nanoseconds()

#define NOW()               ptime(second_clock::universal_time())

#define PARSE_DATE_FMT      "yyyy-MM-dd"
#define PARSE_TIME_FMT      "hh:mm:ss"

#define DATE_REL_TODAY      "today"
#define DATE_REL_TOMORROW   "tomorrow"
#define DATE_REL_YESTERDAY  "yesterday"



using namespace boost::posix_time;
using namespace boost::gregorian;

class ZDateTime
{
public:
    ZDateTime();
    static QDateTime strtotime(QString);
    static QDateTime now();
    static QDateTime nowMsec();

    static qint64 strtotime_t(QString);
    static qint64 now_t();
    static qint64 nowMsec_t();


};

#endif // ZDATETIME_H
