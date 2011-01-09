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

//    ZString ts1 = "zee:teststring/by/Value@yay";

//    z_log("ZString - basic tests");
//    z_log("value: "+ts1);
//    z_log("value: "+ts1.toQString());
//    z_log("value: "+QVariant(ts1).toString());
//    z_log("value: "+QVariant(ts1.toQString()).toString());

//    if(ts1.contains("/"))
//        z_log("YAY!");

//    z_log("leftOf '/': zee:teststring => "+ts1.leftOf("/"));
//    z_log("leftOf '/': zee:teststring/by => "+ts1.leftOfLast("/"));
//    z_log("rightOf '/': by/Value@yay => "+ts1.rightOf("/"));
//    z_log("rightOf '/': Value@yay => "+ts1.rightOfLast("/"));
//    z_log("upcase: zee:teststring => "+ts1.upcase());
//    z_log("downcase: zee:teststring => "+ts1.downcase());
//    z_log("lpad: zee:teststring => "+ts1.lpad(100));
//    z_log("rpad: zee:teststring => "+ts1.rpad(100));


//    z_log("ZString - substring() tests");

    //ZString str = "Pineapple";

//    z_log("");
//    z_log("   Pineapple ");
//    z_log("   0123456789111111111122222222223333333333");
//    z_log("             012345678901234567890123456789");

//      //z_log("Pineaple = "+str.squeeze("p"));

//    z_log("substring(0,9): Pineapple => "+str.substring(0,9));
//    z_log("substring(5,0):  => "+str.substring(5,0));
//    z_log("substring(2,3): nea => "+str.substring(2,3));
//    z_log("substring(0,4): Pine => "+str.substring(0,4));
//    z_log("substring(4,1000): apple => "+str.substring(4,1000));
//    z_log("substring(0,3): ??? => "+str.substring(0,3));
//    z_log("substring(0,3): eapp => "+str.substring(3,4));
//    z_log("substring(6,-3): app => "+str.substring(6,-3));
//    z_log("substring(7,-1000): Pineappl => "+str.substring(7,-1000));

    //z_log("find: solid => "+ZString::find("3px solid #FF00CC", "solid"));
//    QRegExp rxh("#([0-9A-Fa-f]{3}|[0-9A-Fa-f]{4}|[0-9A-Fa-f]{6}|[0-9A-Fa-f]{8})");
    //QRegExp rxf("rgba\\s*\\(\\s*([0-9]{1,3}%?)\\s*,\\s*([0-9]{1,3}%?)\\s*,\\s*([0-9]{1,3}%?)\\s*,\\s*([0-9]{1,3}%?)\\s*\\)");


//    QRegExp rxf("rgb\\s*\\((?:\\s*([0-9]{1,3}%?)(?:(\\s*,\\s*|\\s*\\)\\s*$))){3}");

//    ZString::match("3px solid #FF00CCD", rxh);
//    z_log("hexcolors: "+STR(rxh.cap(1)));

//    z_log("match: #F0C => "+ZString::match("3px solid #FF0F", rx)+" ("+STR(rx.captureCount())+")");
//    z_log("match: #F0C => "+ZString::match("3px solid #FF00CC", rx)+" ("+STR(rx.captureCount())+")");
//    z_log("match: #F0C => "+ZString::match("3px solid #FF00CCFF", rx)+" ("+STR(rx.captureCount())+")");

//    ZString::match("3px solid rgb(255,192  ,   64) ", rxf);
//    z_log("rgba: |"+STR(rxf.cap(1))+","+STR(rxf.cap(2))+","+STR(rxf.cap(3))+","+STR(rxf.cap(4))+"|");

//    z_log("match: #F0C => "+ZString::match("3px solid rgba(255,192  ,   64, 50%)", rx)+" ("+STR(rx.captureCount())+")");

    //z_log("match: 1px 2 3px 4 => "+str.match("1pt 2px 3px 4px 5px", QRegExp("([0-9]+(?:px|pt|em|ex)?(?:(\\s+|\\s*$))){1,4}")));

    ZStyle zp("../../examples/sysinfo/ui.qss");

    z_log_debug("ZDebug: style: \n"+zp.styleSheet());

    //QString v = "3px solid #F0C";
    //z_log_debug("ZStyleProperty:  valueFrom "+v+" color: "+ZStyleProperty::valueFrom(v).width());

//    ZString str = "50%";

//    z_log_debug("ZString: fromPercent =>"+STR(str.fromPercent()));
//    z_log_debug("ZString: fromPercent =>"+STR(str.fromPercent(200)));
//    z_log_debug("ZString: fromPercent =>"+STR(str.fromPercent(50)));
//    z_log_debug("ZString: fromPercent =>"+STR(str.fromPercent(256)));
//    z_log_debug("ZString: fromPercent =>"+STR(ZString::fromPercent("256",256)));

//    ZString qs = "this is a sentence. this is another one.";
//    z_log_debug("Title Case:    "+qs.titleCase());
//    z_log_debug("Capitalize:    "+qs.capitalize());
//    z_log_debug("Sentence case: "+qs.sentenceCase());

//    z_log_debug("camelize: "+ZString::camelize("gauge_background-image"));
//    z_log_debug("camelize: "+ZString::camelize(" non camel case"));
//    z_log_debug("camelize: "+ZString::camelize("pretty_darned neat"));
//    z_log_debug("camelize: "+ZString::camelize("  this ____ should----be camelzied"));
//    z_log_debug("camelize: "+ZString::camelize("NORMALIZE--____THIS___---sTrinG"));
}
