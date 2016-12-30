#ifndef LIFTER3D_H
#define LIFTER3D_H

#include <QObject>
#include "lifter.h"

class Lifter3d : public Lifter
{
public:
    Lifter3d(unsigned int selfAddr=0, unsigned int selfNet=0,unsigned int selfDevType=0, QObject *parent = 0);
    ~Lifter3d();
    void moveDirect3d(const QVector3D &vector);
    void eventNewLift(Lift* lift); //override

protected:


private:
    QList<Lift*> liftList3d;
    void addLift3d(Lift* lift, int num, const QVector3D &base, int len);
    const int iLift[3]={31,22,30};
    const int xLift[3]={0,430,1440};//{0,2300,0};
    const int yLift[3]={2300,2140,2300};//{1440,2300,0};
    const int zLift[3]={0,1440,0};//{430,2140,1440};
    const int lLift[3]={1060,1100,1000};
};


#endif // LIFTER3D_H
