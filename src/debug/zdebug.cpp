#include "zdebug.h"

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
}
