#include "include/lift.h"

Lift::Lift(QObject *parent) : QObject(parent)
{
   saState=snState=hcState=hlState=0;
}

Lift::Lift(unsigned int selfAddr, unsigned int selfNet, QObject *parent) : QObject(parent)
{
    this->selfAddr=selfAddr;
    saState=Lift::STATE_ACTUAL;
    this->selfNet=selfNet;
    snState=Lift::STATE_ACTUAL;
    hcState=hlState=0;
}
