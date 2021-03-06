#ifndef LIFTER_H
#define LIFTER_H

#include "include/gnetraw.h"
#include "include/lift.h"

#include <QObject>

class Lifter : public QObject
{
    Q_OBJECT
public:

    static const unsigned char CMD_READ=0;
    static const unsigned char CMD_WRITE=1;
    static const unsigned char CMD_INFO=3;

    static const unsigned char CMD_WRITE_0B=31;
    static const unsigned char CMD_WRITE_1B=33;

    static const unsigned char CMD_INFO_0B=46;
    static const unsigned char CMD_INFO_1B=47;

    static const unsigned char PORT_FIND=1;

    /* Legacy position port. Accuracy in cm */
    static const unsigned char PORT_POSITION=32;

    static const unsigned char PORT_DIR_UP=35;
    static const unsigned char PORT_DIR_DN=36;
    static const unsigned char PORT_STOP=37;
    static const unsigned char PORT_PARK=38;
    /* New position port. Accuracy in mm */
    static const unsigned char PORT_POS_MM=75;
    static const unsigned char PORT_POS_RAW=76;

    //explicit Lifter(QObject *parent = 0);
    explicit Lifter(GnetRaw *gnet, unsigned int selfAddr=0, unsigned int selfNet=0,unsigned int selfDevType=0, QObject *parent = 0);
    virtual ~Lifter();
    void findLifts();
    void upDemand(int num);
    void downDemand(int num);
    void stop(int num);
    void stopAll();
    void goPark(int num);
    void goPark(Lift *lift);
    void goMm(int num, int height);
    void goMm75(int num, int height);
    void goRaw(int num, int height);
    void goRaw(Lift* lift, int lenght);
    void getParkState(Lift* lift);
    void getHeight(Lift* lift);

    void sendCmd(int num, QVector<Gcpd> &cpd);
    int getLiftCount();
    Lift* getLift(int i);
    void clearLiftList();
     virtual void eventNewLift(Lift* lift);

protected:
    unsigned int selfAddr;
    unsigned int selfNet;
    unsigned int selfDevType;
    QList<Lift*> liftList;
    GnetRaw *gnet;
    int indexOfLiftList(QHostAddress ip, unsigned int addr, unsigned int net, unsigned int devType);
    int indexOfLiftList(unsigned int addr, unsigned int net, unsigned int devType);


private:

    void cpdProcessing(int index, QVector<Gcpd> &cpd);


signals:
    void readyToSend(GDatagram datagram);
    void addedLiftToList(int position,int row);
    void removedLiftToList(int position,int row);
    void liftUpdated(int index);
public slots:
    void datagramReceive(QHostAddress ip, GDatagram datagram);

};

#endif // LIFTER_H
