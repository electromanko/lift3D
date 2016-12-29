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
        lenght = lift->basePos3d.distanceToPoint(vector)-lift->lenghtCableRelease;
        lenght = lenght<0 ? 0 : lenght;
        this->goRaw(lift,lenght);
    }
}
