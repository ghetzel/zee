#ifndef ZEVENTRELATIONSHIP_H
#define ZEVENTRELATIONSHIP_H

#include <iostream>
#include <string>
#include <QtCore>
#include <QtGui>
#include <QApplication>
#include <QMetaMethod>
#include <zutil.h>
#include <zmethodobject.h>


/*!
  \class ZEventRelationship
  \ingroup zeeapp
  \brief The event registration object represents a relationship between two or
  more components.

  When components need to interact with each other, they do so by mapping their
  signals and slots to each other, sometimes utilizing data from a third party
  to do so.  The relationship between sender, receiver, and other ancillary
  components is represented by the ZEventRelationship object.

  An event registration ties a sending object's signal to a receiving object's
  slot.  If the sending object does not provide the information a receiver needs
  for execution, the connection is facilitated with surrogate properties using
  the \a via and \a property constructor parameters.  If surrogate properties
  are specified, they will be used as the arguments for the calling the \a slot
  routine when the \a signal is emitted.  If no surrogate parameters are
  specified, the signal and slot are assumed to be type-compatible and a simple
  connect() is attempted.

  If surrogate properties are specified, they will be passed to the slot upon
  invocation.  The slot's signature determines the number and type of surrogate
  properties that will be passed.  If more properties are specified than the
  slot requires, they will be ignored.  Properties will be dynamically converted
  to whatever data types the slot is expecting as per its signature (within the
  limits of the conversion capability of QVariants).  If an insufficient number
  of properties are specified for a given slot signature, the property will be
  passed to the slot wholesale (no type conversion), and in all liklihood the
  call will fail.

*/
class ZEventRelationship : public QObject{
    Q_OBJECT

public:
    explicit ZEventRelationship(ZMethodObject from, ZMethodObject to,
				QList<QPair<QObject*,QString> > via,
				bool direct=false);
private slots:
    void adapter(QVariant p1=QVariant(),QVariant p2=QVariant(),
		 QVariant p3=QVariant(),QVariant p4=QVariant(),
		 QVariant p5=QVariant(),QVariant p6=QVariant());
    void adapter(bool);
    void adapter(int);
    void adapter(uint);
    void adapter(qint64);
    void adapter(qulonglong);
    void adapter(double);
    void adapter(QString);
    void adapter(QStringList);
    void adapter(QUrl);
    void adapter(QDate);
    void adapter(QDateTime);
    void adapter(int,int);
/*
    void adapter(QPoint);
    void adapter(QPointF);
    void adapter(QRect);
    void adapter(QRegion);
    void adapter(bool,bool);
    void adapter(bool,int);
    void adapter(bool,double);
    void adapter(bool,QString);
    void adapter(int,bool);

    void adapter(int,double);
    void adapter(int,QString);
    void adapter(double,bool);
    void adapter(double,int);
    void adapter(double,double);
    void adapter(double,QString);
    void adapter(QString,bool);
    void adapter(QString,int);
    void adapter(QString,double);
    void adapter(QString,QString); */

signals:
    void adapted();
    void adapted(bool);
    void adapted(int);
    void adapted(uint);
    void adapted(quint64);
    void adapted(qint64);
    void adapted(double);
    void adapted(QChar);
    void adapted(QString);
    void adapted(QStringList);
    void adapted(QVariant);
    void adapted(QDate);
    void adapted(QDateTime);
    void adapted(QUrl);
    void adapted(int,int);
    void adapted(QString,QString);
    void adapted(QString,QString,QString);
    void adapted(QString,QString,QString,uint);

private:
    ZMethodObject _signal;
    ZMethodObject _slot;
    QList<QPair<QObject*,QString> > _via;
    bool _direct;

private:
    void init();
    void invokeSlot(QList<QVariant> args);
};


#endif // ZEVENTRELATIONSHIP_H
