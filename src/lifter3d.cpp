#include "include/lifter3d.h"

Lifter3d::Lifter3d(unsigned int selfAddr, unsigned int selfNet,unsigned int selfDevType, QObject *parent)
    : Lifter (selfAddr, selfNet, selfDevType, parent)
{

}

Lifter3d::~Lifter3d()
{
    qDeleteAll(liftList3d);
    liftList3d.clear();
}

void Lifter3d::moveDirect3d(const QVector3D &vector)
{
    int lenght;
    foreach (Lift *lift, this->liftList3d){
        lenght = (int)lift->basePos3d.distanceToPoint(vector)-lift->lenghtCableRelease;
        lenght = lenght<0 ? 0 : lenght;
        this->goRaw(lift,lenght);
    }
}

void Lifter3d::eventNewLift(Lift *lift)
{

    for(int i=0;i<3;i++){
        if(lift->addr == (unsigned int)iLift[i]) {
            lift->basePos3d.setX(xLift[i]);
            lift->basePos3d.setY(yLift[i]);
            lift->basePos3d.setZ(zLift[i]);
            lift->lenghtCableRelease= lLift[i];
            this->liftList3d.append(lift);
            qDebug("new lift3d");
            break;
        }
    }
}

void Lifter3d::addLift3d(Lift *lift, int num, const QVector3D &base, int len)
{

}
