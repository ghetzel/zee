#include "zdebug.h"

//QVariant _round(QVariant in, int places=0){
//    double rv = in.toDouble();
//    int multiplier = qPow(10,places);
//    rv *= multiplier;
//    z_log_debug("RV: "+in.toString()+", M="+STR(multiplier)+", CV="+STR(rv));
//    rv = qRound(rv);
//    return QVariant(rv/multiplier);
//}


QVariant _base(QVariant in, int toBase, int fromBase=10){
    QString val = in.toString();
    char tokens[16] = {'0','1','2','3','4','5','6','7',    // base 8
                       '8','9','A','B','C','D','E','F'};   // base 16
    QString rv;
    int remain = 0;
    long input = in.toInt();

    do{
        remain = input % toBase;
        input /= toBase;
        rv.prepend(tokens[remain]);
        remain -= toBase;
    }while(input > 0);

    return QVariant(rv);
}

ZDebug::ZDebug(int argc, char **argv)
    : QCoreApplication(argc, argv)
{
    z_log_debug("ZDebug: Debug Application Started");

//    z_log_debug("libzee: ZDateTime: Tests");
//    z_log_debug("\tnow:\t"+STR(ZDateTime::now().toTime_t()));
//    z_log_debug("\tnow:\t"+STR(ZDateTime::now_t()));
//    z_log_debug("\tnowms:\t"+STR(ZDateTime::nowMsec().time().msec()));
//    z_log_debug("\tnowms:\t"+STR(ZDateTime::nowMsec_t()));
//    z_log_debug("\tnowus:\t"+STR(ZDateTime::nowUsec_t()));
//    z_log_debug("libzee: ZDateTime: Format Tests");
//    z_log_debug("\tformat:\t"+STR(ZDateTime::strtotime("tomorrow 17:23:29")));
//    z_log_debug("\tformat:\t"+STR(ZDateTime::strtotime_t("tomorrow 17:23:29")));
//    z_log_debug("libzee: ZDateTime: Diffs");
//    z_log_debug("\tsecTo:\t"+STR(ZDateTime::secondsTo("today 17:50:00")));
//    z_log_debug("\tmsecTo:\t"+STR(ZDateTime::msecsTo("tomorrow teatime")));
//
//    z_log_debug("\tfromUx:\t"+STR(ZDateTime::fromUnix(1285273660)));
//    z_log_debug("\tfromUxMs:\t"+STR(ZDateTime::fromUnixMsec(1285273660500)));

    //QIcon::setThemeName("Faenza");
    //z_log("ZDebug: "+QIcon::themeName());
    //QIcon i = QIcon::fromTheme("media-playback-start");
    //z_log("ZDebug: "+i.themeName());

//    z_log("Round (0 places)"+_round(QVariant(10.845347)).toString());
//    z_log("Round (1 places)"+_round(QVariant(10.845347),1).toString());
//    z_log("Round (2 places)"+_round(QVariant(10.845347),2).toString());
//    z_log("Round (3 places)"+_round(QVariant(10.845347),3).toString());
//    z_log("Round (4 places)"+_round(QVariant(10.845347),4).toString());

    //z_log("Base: "+_base(QVariant(172),16).toString());
}
