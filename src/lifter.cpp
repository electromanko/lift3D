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
    clearLiftList();
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

void Lifter::stopAll()
{
    GDatagram datagram(0,selfAddr,selfNet,255, 255,selfDevType);
    datagram.appendCpd(Gcpd (CMD_WRITE,PORT_STOP,1));
    gnet->sendGDatagram(datagram);
}


void Lifter::goPark(int num)
{
    Lift* lift;
    if(num< liftList.size()&& num>=0){
        lift = liftList.at(num);
        GDatagram datagram(0,selfAddr,selfNet,lift->addr, lift->net,selfDevType);
        datagram.appendCpd(Gcpd (CMD_WRITE,PORT_PARK,1));
        gnet->sendGDatagram(datagram);
    }
}

void Lifter::goMm(int num, int height)
{
    Lift* lift;
    int dm=height/100;
    int cm=(height%100)/10;
    int mm=height-dm*100-cm*10;
    //qDebug()<<dm<< " "<<cm<< " "<<mm;
    if(num< liftList.size()&& num>=0){
        lift = liftList.at(num);
        GDatagram datagram(0,selfAddr,selfNet,lift->addr, lift->net,selfDevType);
        datagram.appendCpd(Gcpd (CMD_WRITE_1B,PORT_POSITION,cm));
        datagram.appendCpd(Gcpd (CMD_WRITE_0B,PORT_POSITION,dm<0xff?dm:0xff));
        gnet->sendGDatagram(datagram);

    }
}

void Lifter::goMm75(int num, int height)
{
    Lift* lift;
    int dm=height/100;
    int mm=height%100;
    qDebug()<<dm<< " "<<mm;
    if(num< liftList.size()&& num>=0){
        lift = liftList.at(num);
        GDatagram datagram(0,selfAddr,selfNet,lift->addr, lift->net,selfDevType);
        datagram.appendCpd(Gcpd (CMD_WRITE_0B,PORT_POS_MM,dm));
        datagram.appendCpd(Gcpd (CMD_WRITE_1B,PORT_POS_MM,mm));
        gnet->sendGDatagram(datagram);

    }
}

void Lifter::goRaw(int num, int height)
{
    Lift* lift;
    int dm=height/100;
    int mm=height%100;
    qDebug()<<dm<< " "<<mm;
    if(num< liftList.size()&& num>=0){
        lift = liftList.at(num);
        GDatagram datagram(0,selfAddr,selfNet,lift->addr, lift->net,selfDevType);
        datagram.appendCpd(Gcpd (CMD_WRITE_0B,PORT_POS_RAW,dm));
        datagram.appendCpd(Gcpd (CMD_WRITE_1B,PORT_POS_RAW,mm));
        gnet->sendGDatagram(datagram);

    }
}

void Lifter::sendCmd(int num, QVector<Gcpd> &cpd)
{
    Lift* lift;

    if(num< liftList.size()&& num>=0){
        lift = liftList.at(num);
        GDatagram datagram(0,selfAddr,selfNet,lift->addr, lift->net,selfDevType, cpd);
        //datagram.appendCpd(Gcpd (CMD_WRITE_1B,PORT_POSITION,cm));
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

void Lifter::clearLiftList()
{
    emit removedLiftToList(0,liftList.size());
    qDeleteAll(liftList);
    liftList.clear();

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
    qDebug() << "Lifter:receive:datgram="<< datagram.toString();
    if (datagram.devType!=41) return;
    int index = this->indexOfLiftList(ip, datagram.addrFrom,datagram.netFrom, datagram.devType);
    if (index<0){
        Lift* lift = new Lift(ip, datagram.addrFrom, datagram.netFrom,datagram.devType);
        this->liftList.append(lift);
        emit addedLiftToList(this->liftList.indexOf(lift),1);
    }
    else {
        cpdProcessing(index, datagram.cpd);
    }
}

void Lifter::cpdProcessing(int index, QVector<Gcpd> &cpd)
{
    static unsigned int cm=0;
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
            if (i->command == Lifter::CMD_INFO_0B){
                lift->heightCurrent=i->data*100+cm*10;
                lift->hcState|=Lift::STATE_ACTUAL|Lift::STATE_UPDATE;
                emit liftUpdated(index);
            } else if(i->command == Lifter::CMD_INFO_1B){
                cm=i->data;
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
