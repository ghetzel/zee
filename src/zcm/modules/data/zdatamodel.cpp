#include "zdatamodel.h"

ZDataModel::ZDataModel(const ZConfig &el, QObject *parent, QSqlDatabase db)
    : QSqlRelationalTableModel(parent, db),
      ZConfigurable(el,this)
{
    parse(_config);
}

void ZDataModel::parse(const ZConfig &el){
    if(el.hasAttribute("table")){
        setTable(el.attribute("table"));

        for(int i = 0; i < columnCount(); i++){
            _columns.insert(headerData(i,Qt::Horizontal).toString(), i);
        }

        foreach(const ZConfig &field, el.children("zee:field")){
            if(_columns.contains(field.attribute("name"))){
            //  set header title
                if(field.hasAttribute("title")){
                    setHeaderData(_columns.value(field.attribute("name")), Qt::Horizontal,
                                  QVariant(field.attribute("title")));
                }

                if(field.hasAttribute("belongsTo")){
                    QString relation = field.attribute("belongsTo");
                    QString rTable = relation.section(":",0,0);
                    QString rKey = relation.section(":",1,1);
                    QString rDisplay = relation.section(":",2,2);

                    if(!(rTable.isEmpty() && rKey.isEmpty() && rDisplay.isEmpty())){
                        setRelation(_columns.value(field.attribute("name")),
                                    QSqlRelation(rTable,rKey,rDisplay));
                    }
                }
            }
        }
    }

    select();
}
