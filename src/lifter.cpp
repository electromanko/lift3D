#include "include/lifter.h"

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

}

void Lifter::downDemand(int num)
{

}

void Lifter::stop(int num)
{

}

void Lifter::datagramReceive(GDatagram datagram)
{
    qDebug() << "Lifter:receive:datgram="<< datagram.toQByteArray().toHex();
}
