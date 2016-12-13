#include "include/lifter.h"

Lifter::Lifter(QObject *parent) : QObject(parent)
{

}

Lifter::Lifter(unsigned int selfAddr, unsigned int selfNet , unsigned int selfDevType, QObject *parent) : QObject(parent)
{
    this->selfAddr=selfAddr;
    this->selfNet=selfNet;
    this->selfDevType= selfDevType;
    gnet= new GnetRaw();
    connect(gnet, SIGNAL(received(GDatagram)),
            this, SLOT(datagramReceive(GDatagram)));
}

Lifter::~Lifter()
{
    qDeleteAll(liftList);
    liftList.clear();
    delete gnet;
}

void Lifter::findLifts()
{
    GDatagram datagram(0,selfAddr,selfNet,255,0,selfDevType);
    datagram.appendCpd(Gcpd (CMD_READ,PORT_FIND,1));
    gnet->sendGDatagram(datagram);
}

void Lifter::upDemand(int num)
{
    Lift* lift;
    if(num< liftList.size()){
        lift = liftList.at(num);
        GDatagram datagram(0,selfAddr,selfNet,lift->addr, lift->net,selfDevType);
        datagram.appendCpd(Gcpd (CMD_WRITE,PORT_DIR_UP,1));
        gnet->sendGDatagram(datagram);
    }
}

void Lifter::downDemand(int num)
{
    Lift* lift;
    if(num< liftList.size()){
        lift = liftList.at(num);
        GDatagram datagram(0,selfAddr,selfNet,lift->addr, lift->net,selfDevType);
        datagram.appendCpd(Gcpd (CMD_WRITE,PORT_DIR_DN,1));
        gnet->sendGDatagram(datagram);
    }
}

void Lifter::stop(int num)
{
    Lift* lift;
    if(num< liftList.size()){
        lift = liftList.at(num);
        GDatagram datagram(0,selfAddr,selfNet,lift->addr, lift->net,selfDevType);
        datagram.appendCpd(Gcpd (CMD_WRITE,PORT_STOP,1));
        gnet->sendGDatagram(datagram);
    }
}

int Lifter::getLiftCount()
{
    return this->liftList.size();
}

Lift* Lifter::getLift(int i)
{
    if (i<liftList.size()){
    return this->liftList.at(i);
    } else return NULL;
}


int Lifter::indexOfLiftList(unsigned int addr, unsigned int net, unsigned int devType)
{
    foreach (Lift *lift, this->liftList){
        if (lift->addr == addr && lift->net==net && lift->devType == devType) return liftList.indexOf(lift);
    }
    return -1;
}

void Lifter::datagramReceive(GDatagram datagram)
{
    qDebug() << "Lifter:receive:datgram="<< datagram.toQByteArray().toHex();
    int index = this->indexOfLiftList(datagram.addrFrom,datagram.netFrom, datagram.devType);
    if (index<0)this->liftList.append(new Lift(datagram.addrFrom, datagram.netFrom,datagram.devType));
    else {
        cpdProcessing(liftList.at(index), datagram.cpd);
    }
}

void Lifter::cpdProcessing(Lift *lift, QVector<Gcpd> &cpd)
{
    QVector<Gcpd>::iterator i;

    for (i = cpd.begin(); i != cpd.end(); ++i){
        switch(i->port){
            case Lifter::PORT_FIND:
            if(i->command  == Lifter::CMD_READ){

            }
            else if(i->command  == Lifter::CMD_WRITE){

            }

            break;

        }
    }
}
