#include "include/liftconfig.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

LiftConfig::LiftConfig(QObject *parent) : QObject(parent)
{

}

bool LiftConfig::load(QFile &configFile){
    lifterAddr=lifterNet=lifterDevType=0;
    move3dDeltaPosition=5;
    move3dTime=100;
    iconSize=64;
    if (!configFile.open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open config file.");
            return false;
        }
        QByteArray saveData = configFile.readAll();

        QJsonDocument configJson(QJsonDocument::fromJson(saveData));

        //read(loadDoc.object());
        QJsonObject jroot= configJson.object();
        QJsonValue val = jroot["lifterAddr"];
        if (val!=QJsonValue::Undefined) lifterAddr= val.toInt(0);
        else return false;
        val = jroot["lifterNet"];
        if (val!=QJsonValue::Undefined) lifterNet= val.toInt(0);
        else return false;
        val = jroot["lifterDevType"];
        if (val!=QJsonValue::Undefined) lifterDevType= val.toInt(0);
        else return false;

        //move3dDeltaPosition, move3dTime, iconSize
        val = jroot["move3dDeltaPosition"];
        if (val!=QJsonValue::Undefined) move3dDeltaPosition= val.toInt(0);
        else return false;
        val = jroot["move3dTime"];
        if (val!=QJsonValue::Undefined) move3dTime= val.toInt(0);
        else return false;
        val = jroot["iconSize"];
        if (val!=QJsonValue::Undefined) iconSize = val.toInt(0);
        else return false;

        val = jroot["limitCubePoint0"];
        if (val!=QJsonValue::Undefined && val.isObject()) {
            QJsonObject limitCubePoint0Obj= val.toObject();
            val = limitCubePoint0Obj["x"];
            if (val!=QJsonValue::Undefined)  limitCubePoint0.setX(val.toInt(0));
            else return false;
            val = limitCubePoint0Obj["y"];
            if (val!=QJsonValue::Undefined) limitCubePoint0.setY(val.toInt(0));
            else return false;
            val = limitCubePoint0Obj["z"];
            if (val!=QJsonValue::Undefined) limitCubePoint0.setZ(val.toInt(0));
            else return false;
        }
        else return false;
        val = jroot["limitCubePoint1"];
        if (val!=QJsonValue::Undefined && val.isObject()) {
            QJsonObject limitCubePoint1Obj= val.toObject();
            val = limitCubePoint1Obj["x"];
            if (val!=QJsonValue::Undefined)  limitCubePoint1.setX(val.toInt(0));
            else return false;
            val = limitCubePoint1Obj["y"];
            if (val!=QJsonValue::Undefined) limitCubePoint1.setY(val.toInt(0));
            else return false;
            val = limitCubePoint1Obj["z"];
            if (val!=QJsonValue::Undefined) limitCubePoint1.setZ(val.toInt(0));
            else return false;
        }
        else return false;

        val = jroot["lift3D"];
        if (val!=QJsonValue::Undefined && val.isArray()) {
            QJsonArray liftArray = val.toArray();
            foreach (QJsonValue  item, liftArray) {
                lift3DConf itemConf;
                QJsonObject itemObj = item.toObject();
                val = itemObj["addr"];
                if (val!=QJsonValue::Undefined) itemConf.addr = val.toInt(0);
                else return false;
                val = itemObj["net"];
                if (val!=QJsonValue::Undefined) itemConf.net = val.toInt(0);
                else return false;
                val = itemObj["lZero"];
                if (val!=QJsonValue::Undefined) itemConf.lZero = val.toInt(0);
                else return false;
                val = itemObj["lEnd"];
                if (val!=QJsonValue::Undefined) itemConf.lEnd = val.toInt(0);
                else return false;
                val = itemObj["x"];
                if (val!=QJsonValue::Undefined) itemConf.pos.setX(val.toInt(0));
                else return false;
                val = itemObj["y"];
                if (val!=QJsonValue::Undefined) itemConf.pos.setY(val.toInt(0));
                else return false;
                val = itemObj["z"];
                if (val!=QJsonValue::Undefined) itemConf.pos.setZ(val.toInt(0));
                else return false;
                this->lift3DList.append(itemConf);
            }
        }
        else return false;
        return true;
}
