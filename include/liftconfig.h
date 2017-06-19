#ifndef LIFTCONFIG_H
#define LIFTCONFIG_H

#include "lift.h"

#include <QFile>
#include <QObject>

struct lift3DConf;

class LiftConfig : public QObject
{
    Q_OBJECT
public:
    int lifterAddr, lifterNet, lifterDevType;
    int move3dDeltaPosition, move3dTime, iconSize;
    QVector3D limitCubePoint0;
    QVector3D limitCubePoint1;
    QVector<lift3DConf> lift3DList;

    //Connections
    /*int udpPortConnection;
    QString mqttHostnameConnection;
    int mqttPortConnection;*/


    explicit LiftConfig(QObject *parent = 0);
    bool load(QFile &configFile);
signals:

public slots:
};

struct lift3DConf{
    int addr;
    int net;
    QVector3D pos;
    int lZero;
    int lEnd;

};

#endif // LIFTCONFIG_H
