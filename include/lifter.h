#ifndef LIFTER_H
#define LIFTER_H

#include "include/gnetraw.h"
#include "lift.h"

#include <QObject>

class Lifter : public QObject
{
    Q_OBJECT
public:

    static const unsigned char CMD_READ=0;
    static const unsigned char CMD_WRITE=1;


    static const unsigned char PORT_FIND=1;
    static const unsigned char PORT_DIR_UP=35;
    static const unsigned char PORT_DIR_DN=36;
    static const unsigned char PORT_STOP=37;
    static const unsigned char PORT_PARK=38;

    explicit Lifter(unsigned int selfAddr=0, unsigned int selfNet=0,unsigned int selfDevType=0, QObject *parent = 0);
    virtual ~Lifter();
    void findLifts();
    void upDemand(int num);
    void downDemand(int num);
    void stop(int num);

protected:
    unsigned int selfAddr;
    unsigned int selfNet;
    unsigned int selfDevType;
    QList<Lift> lift;
    GnetRaw *gnet;

signals:
    void readyToSend(GDatagram datagram);

public slots:
    void datagramReceive(GDatagram datagram);
};

#endif // LIFTER_H
