#ifndef LIFTER3D_H
#define LIFTER3D_H

#include <QObject>
#include "lifter.h"

class Lifter3d : public Lifter
{
public:
    Lifter3d(unsigned int selfAddr=0, unsigned int selfNet=0,unsigned int selfDevType=0, QObject *parent = 0);
    void moveDirection3d(QVector3D vector);
private:
    QList<QPair<Lift*, QVector3D*>> vectorList;
};

#endif // LIFTER3D_H
