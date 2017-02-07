#ifndef LIFT_H
#define LIFT_H

#include "gnetraw.h"

#include <QObject>
#include <QVector3D>

class Lift : public QObject
{
    Q_OBJECT
public:
    static const int  BASE_DEV_TYPE = 32;
    static const unsigned char  STATE_ACTUAL = (1<<0);
    static const unsigned char  STATE_UPDATE = (1<<1);

    explicit Lift(QObject *parent =0);
    explicit Lift(QHostAddress ip, unsigned int selfAddr=0,unsigned int  selfNet=0, unsigned int devType=0, QObject *parent = 0);
    virtual ~Lift();

    void headling(QVector<Gcpd> &cpd);

    unsigned int addr;
    unsigned char saState;

    unsigned int net;
    unsigned char snState;

    unsigned int devType;
    unsigned char dtState;

    unsigned int heightCurrent;
    unsigned char hcState;

    unsigned int heightLink;
    unsigned char hlState;

    QHostAddress ip;

    bool padked;
    unsigned char pkState;

    QVector3D basePos3d;
    int lenghtZero;
    int lenghtEnd;
signals:

public slots:
};

#endif // LIFT_H
