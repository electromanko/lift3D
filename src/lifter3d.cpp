#include "include/lifter3d.h"

Lifter3d::Lifter3d(const QVector3D &limitCubePoint0, const QVector3D &limitCubePoint1, unsigned int selfAddr, unsigned int selfNet, unsigned int selfDevType,  QObject *parent)
    : Lifter (selfAddr, selfNet, selfDevType, parent)
{
    this->limitCubePoint0=limitCubePoint0;
    this->limitCubePoint1=limitCubePoint1;
}

Lifter3d::~Lifter3d()
{
    qDeleteAll(liftList3d);
    liftList3d.clear();
}

bool Lifter3d::moveDirect3d(const QVector3D &vector)
{
    int lenght;
    int maxLenght;
    foreach (Lift *lift, this->liftList3d){
        lenght = (int)lift->basePos3d.distanceToPoint(vector)-lift->lenghtZero;
        maxLenght = lift->lenghtEnd - lift->lenghtZero;
        if (lenght<0 || lenght> maxLenght ) return false;
        if (vector.x()<this->limitCubePoint0.x() || vector.x()>this->limitCubePoint1.x())return false;
        if (vector.y()<this->limitCubePoint0.y() || vector.y()>this->limitCubePoint1.y())return false;
        if (vector.z()<this->limitCubePoint0.z() || vector.z()>this->limitCubePoint1.z())return false;
    }
    foreach (Lift *lift, this->liftList3d){
        lenght = (int)lift->basePos3d.distanceToPoint(vector)-lift->lenghtZero;
        lenght = lenght<0 ? 0 : lenght;
        maxLenght = lift->lenghtEnd - lift->lenghtZero;
        lenght = lenght> maxLenght ? maxLenght: lenght;
        this->goRaw(lift,lenght);
    }
    return true;
}

bool Lifter3d::park3d(){
    foreach (Lift *lift, this->liftList3d){
        this->goPark(lift);
    }
    return true;
}

void Lifter3d::eventNewLift(Lift *lift)
{
    /*
    for(int i=0;i<3;i++){
        if(lift->addr == (unsigned int)iLift[i]) {
            lift->basePos3d.setX(xLift[i]);
            lift->basePos3d.setY(yLift[i]);
            lift->basePos3d.setZ(zLift[i]);
            lift->lenghtZero= lLift[i];
            this->liftList3d.append(lift);
            qDebug("new lift3d");
            break;
        }
    }
    */
}

void Lifter3d::addLift3d(int addr, int net, int lenghtZero, int lenghtEnd,const QVector3D &base)
{
  Lift *lift = new Lift();
  lift->addr=addr;
  lift->net=net;
  lift->devType= Lift::BASE_DEV_TYPE;
  lift->lenghtZero=lenghtZero;
  lift->lenghtEnd=lenghtEnd;
  lift->basePos3d=base;
  this->liftList3d.append(lift);
}
