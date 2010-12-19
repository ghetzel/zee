#include "zregexformatter.h"

ZRegexFormatter::ZRegexFormatter(QObject *parent)
    : ZAbstractFormatter(parent){}

QVariant ZRegexFormatter::transform(QVariant val){
    if(method() == ZFMT_METHOD_REGEX_MATCH_FIRST){ //!            match-first
        return _matchFirst(val, arg("pattern", ZML_DEFAULT_PARAM_NAME).toString());

    }else if(method() == ZFMT_METHOD_REGEX_MATCH_LAST){ //!       match-last
        return _matchLast(val, arg("pattern", ZML_DEFAULT_PARAM_NAME).toString());

    }else if(method() == ZFMT_METHOD_REGEX_MATCH){ //!            match
        return _match(val, arg("pattern", ZML_DEFAULT_PARAM_NAME).toString(), arg("occurrence").toInt());

    }else if(method() == ZFMT_METHOD_REGEX_MATCH_ALL){ //!        match-all
        return _matchAll(val, arg("pattern", ZML_DEFAULT_PARAM_NAME).toString(), arg("separator").toString());

    }else if(method() == ZFMT_METHOD_REGEX_REPLACE){ //!          replace
        return _replace(val, arg("pattern").toString(), arg("with", ZML_DEFAULT_PARAM_NAME).toString());
    }

    return val;
}


// Methods

QVariant ZRegexFormatter::_match(QVariant in, QString pattern, int occurrence){
    if(pattern.isEmpty())
        return in;

    QRegExp rx(pattern);
    ZString instr = in.toString();
    QString rv;
    int count = 0;
    int position = 0;
    int forward = ((occurrence >= 0) ? 1 : -1);

    if(occurrence != 0){
        while( (position = ZRegexFormatter::_regexIndexInDirection(rx,instr,forward*position,(forward==1))) != -1){
            ++count;
            rv = instr.substring(position,position+rx.matchedLength());

            z_log("ZRegexFormatter: #"+STR(count)+" @"+STR(position)+","+STR(position+rx.matchedLength()));

            if(count == qAbs(occurrence))
                return QVariant(rv);
        }
    }

    return QVariant();
}

QVariant ZRegexFormatter::_matchFirst(QVariant in, QString pattern){
    return _match(in, pattern, 1);
}

QVariant ZRegexFormatter::_matchLast(QVariant in, QString pattern){
    return _match(in, pattern, -1);
}

QVariant ZRegexFormatter::_matchAll(QVariant in, QString pattern, QString separator){
    if(pattern.isEmpty())
        return in;

    QVariant rv;
    QRegExp rx(pattern);

    z_log_debug("ZRegexFormatter: separator = '"+separator+"'");

    if(in.toString().contains(rx)){
        if(separator.isEmpty()){
            rv = QVariant(rx.capturedTexts());
        }else{
            QString out;
            z_log_debug("ZRegexFormatter: Cap Count="+STR(rx.captureCount()));
            z_log_debug("ZRegexFormatter: Caps = "+rx.capturedTexts().join(" | "));

            for(int i = 1; i < rx.captureCount(); i++){
                out += rx.cap(i);
            //  dont append 'separator' to the last element
                if(i != rx.captureCount())
                    out += separator;
            }

            rv = QVariant(out);
        }
    }

    return rv;
}

QVariant ZRegexFormatter::_replace(QVariant in, QString pattern, QString with){
    return in;
}


int ZRegexFormatter::_regexIndexInDirection(QRegExp &rx, QString string, int offset, bool forward){
    if(forward)
        return rx.indexIn(string,offset);
    else
        return rx.lastIndexIn(string,offset);
}
