#ifndef LIFTER3D_H
#define LIFTER3D_H

#include <QObject>
#include "lifter.h"

class Lifter3d : public Lifter
{
public:
    Lifter3d(GnetRaw* gnet, const QVector3D &limitCubePoint0, const QVector3D &limitCubePoint1,unsigned int selfAddr=0, unsigned int selfNet=0,unsigned int selfDevType=0,  QObject *parent = 0);
    ~Lifter3d();
    bool moveDirect3d(const QVector3D &vector);
    void eventNewLift(Lift* lift); //override
    void addLift3d(int addr, int net, int lenghtZero, int lenghtEnd, const QVector3D &base);
    bool park3d();
    QVector3D limitCubePoint0;
    QVector3D limitCubePoint1;
protected:


private:
    QVector<Lift*> liftList3d;

};


#endif // LIFTER3D_H
