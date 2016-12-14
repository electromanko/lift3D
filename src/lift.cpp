#include "include/lift.h"

Lift::Lift(QObject *parent) : QObject(parent)
{
   saState=snState=hcState=hlState=0;
}

Lift::Lift(QHostAddress ip,unsigned int selfAddr, unsigned int selfNet, unsigned int devType, QObject *parent) : QObject(parent)
{
    this->ip=ip;
    this->addr=selfAddr;
    saState=Lift::STATE_ACTUAL;
    this->net=selfNet;
    snState=Lift::STATE_ACTUAL;
    this->devType=devType;
    dtState=Lift::STATE_ACTUAL;

    this->heightCurrent=0;
    this->heightLink=0;
    this->padked=false;

    pkState=hcState=hlState=0;

}

Lift::~Lift()
{

}


