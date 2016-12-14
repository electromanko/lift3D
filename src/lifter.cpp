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
    connect(gnet, SIGNAL(received(QHostAddress, GDatagram)),
            this, SLOT(datagramReceive(QHostAddress, GDatagram)));
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
    if(num< liftList.size() && num>=0){
        lift = liftList.at(num);
        GDatagram datagram(0,selfAddr,selfNet,lift->addr, lift->net,selfDevType);
        datagram.appendCpd(Gcpd (CMD_WRITE,PORT_DIR_UP,1));
        gnet->sendGDatagram(datagram);
    }
}

void Lifter::downDemand(int num)
{
    Lift* lift;
    if(num< liftList.size()&& num>=0){
        lift = liftList.at(num);
        GDatagram datagram(0,selfAddr,selfNet,lift->addr, lift->net,selfDevType);
        datagram.appendCpd(Gcpd (CMD_WRITE,PORT_DIR_DN,1));
        gnet->sendGDatagram(datagram);
    }
}

void Lifter::stop(int num)
{
    Lift* lift;
    if(num< liftList.size()&& num>=0){
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


int Lifter::indexOfLiftList(QHostAddress ip, unsigned int addr, unsigned int net, unsigned int devType)
{
    foreach (Lift *lift, this->liftList){
        if (lift->ip== ip && lift->addr == addr && lift->net==net && lift->devType == devType) return liftList.indexOf(lift);
    }
    return -1;
}

void Lifter::datagramReceive(QHostAddress ip, GDatagram datagram)
{
    qDebug() << "Lifter:receive:datgram="<< datagram.toQByteArray().toHex();
    int index = this->indexOfLiftList(ip, datagram.addrFrom,datagram.netFrom, datagram.devType);
    if (index<0){
        this->liftList.append(new Lift(ip, datagram.addrFrom, datagram.netFrom,datagram.devType));
        emit addedLiftToList();
    }
    else {
        cpdProcessing(index, datagram.cpd);
    }
}

void Lifter::cpdProcessing(int index, QVector<Gcpd> &cpd)
{

    QVector<Gcpd>::iterator i;

    Lift *lift= liftList.at(index);
    for (i = cpd.begin(); i != cpd.end(); ++i){
        switch(i->port){ 
        case Lifter::PORT_FIND:
            if(i->command  == Lifter::CMD_READ){

            }
            else if(i->command  == Lifter::CMD_WRITE){

            }

            break;
        case Lifter::PORT_POSITION:
            if (i->command == Lifter::CMD_info_0B){
                lift->heightCurrent=i->data;
                lift->hcState|=Lift::STATE_ACTUAL|Lift::STATE_UPDATE;
                emit liftUpdated(index);
            }
            break;

        case Lifter::PORT_PARK:
            if (i->command == Lifter::CMD_INFO){
                if (i->data>0) lift->padked=true;
                else lift->padked=false;
                lift->pkState|=Lift::STATE_ACTUAL|Lift::STATE_UPDATE;
                emit liftUpdated(index);
            }
            break;
        }
    }
}
