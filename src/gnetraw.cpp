#include "include/gnetraw.h"
#include <QNetworkInterface>

GnetRaw::GnetRaw(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    mqttClient = new QMQTT::Client;

    connectionType = GnetRaw::NO_CONNECTION;
    udpPort=0;
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
            qDebug() <<"Self ip address: " << address.toString();
        selfAddress.append(address);
    }
    foreach (const QNetworkInterface &interface, QNetworkInterface::allInterfaces()) {
        //if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        qDebug() <<"Self interface: " << interface.humanReadableName() << interface.hardwareAddress();
        //selfAddress.append(address);
    }

}

void GnetRaw::connect_mqtt(const QString &hostname, int port){

    connect(mqttClient, SIGNAL(connected()), this, SLOT(mqttOnConnected()));
    connect(mqttClient, SIGNAL(disconnected()), this, SLOT(mqttOnDisconnected()));
    //connect(this, SIGNAL(subscribed(const QString&, const quint8)), this, SLOT(onSubscribed(const QString&, const quint8)));
    connect(mqttClient, SIGNAL(received(const QMQTT::Message&)), this, SLOT(mqttOnReceived(const QMQTT::Message&)));
    connect(mqttClient, SIGNAL(error(const QMQTT::ClientError)), this, SLOT(mqttOnError(const QMQTT::ClientError)));
    connectionType = GnetRaw::MQTT_CONNECTION;

    mqttClient->setHostName(hostname);
    mqttClient->setPort(port);
    mqttClient->setClientId("RomaQT");
    mqttClient->setUsername("");
    mqttClient->setPassword("");
    mqttClient->connectToHost();
}

int GnetRaw::getConnectionType()
{
    return connectionType;
}

void GnetRaw::connect_udp(int port){

    udpPort=port;
    udpSocket->bind(QHostAddress::AnyIPv4, udpPort, QUdpSocket::ShareAddress);


    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
    connectionType = GnetRaw::UDP_CONNECTION;
}

void GnetRaw::disconnect(){
    if (connectionType == GnetRaw::MQTT_CONNECTION){
        mqttClient->disconnectFromHost();
    }
    else if (connectionType == GnetRaw::UDP_CONNECTION){
        udpSocket->abort();
        connectionType = GnetRaw::NO_CONNECTION;
    }
}

void GnetRaw::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        //processTheDatagram(datagram);
        bool selfA=false;
        foreach (const QHostAddress &address, selfAddress) {
            if(address==sender) {
                selfA=true;
                break;
            }
        }
        GDatagram dt = GDatagram(datagram);
        dt.setDateStamp();
        if(selfA){
            emit sended(sender, dt);
            qDebug() << "echo: " << sender.toString() << GDatagram(datagram).toString();
        }
        else {
            emit received(sender, dt);
            qDebug() << "in: " << sender.toString() << datagram.toHex();
        }
    }
}

void GnetRaw::mqttOnConnected()
{
    if (connectionType == GnetRaw::MQTT_CONNECTION){
        mqttClient->subscribe("raw/+/gnet", 0);
        qDebug("Connected mqtt");
        /*QMQTT::Message message(number, EXAMPLE_TOPIC,
        QString("Number is %1").arg(number).toUtf8());
        publish(message);
        number++;*/
     }

}

void GnetRaw::mqttOnDisonnected()
{
    qDebug("Disconnected mqtt");
    connectionType = GnetRaw::NO_CONNECTION;
}

void GnetRaw::mqttOnError(const QMQTT::ClientError error)
{
    if (connectionType == GnetRaw::MQTT_CONNECTION){
        //error
        qDebug("error");
    }
}

void GnetRaw::mqttOnReceived(const QMQTT::Message &message)
{
        //message
    QHostAddress sender("0.0.0.0");
    QString str = QString::fromUtf8(message.payload());
    GDatagram gdatagram( message.payload());
    gdatagram.setDateStamp();
    //qDebug(qPrintable(gdatagram.toString()));
    emit received(sender, gdatagram);

}
/* DEPRECATE!!! */
/*void GnetRaw::sendGDatagram(unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType, QVector<Gcpd> &cpd)
{
    QByteArray datagram = QByteArray::number(8+cpd.count()*3);
    datagram[0]=7+cpd.count()*3; //Size val
    datagram[1]=(addrFrom);
    datagram[2]=((char)1); // DatagramType
    datagram[3]=((char)0); //Number
    datagram[4]=(netFrom);
    datagram[5]=(addrTo);
    datagram[6]=(netTo);
    datagram[7]=(devType);
    QVector<Gcpd>::iterator i;
    int n=8;
    for (i = cpd.begin(); i != cpd.end(); ++i){
        datagram[n]=i->command;
        datagram[n+1]=i->port;
        datagram[n+2]=i->data;
        n+=3;
    }
    qDebug() << datagram.toHex();
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, 7777);
}*/

void GnetRaw::sendGDatagram(GDatagram &gdatagram)
{
    if (connectionType==UDP_CONNECTION){
    QByteArray datagram = gdatagram.toQByteArray();
    udpSocket->writeDatagram(datagram.data(), datagram.size(),
                             QHostAddress::Broadcast, udpPort);
    }
    else if (connectionType==MQTT_CONNECTION){
        qDebug("send");
        QMQTT::Message message(0, QString("raw/RomaQT/gnet/SET"), gdatagram.toQByteArray());
        mqttClient->publish(message);
        emit sended(QHostAddress("0.0.0.0"), gdatagram);
    }
}

QVector<QHostAddress> GnetRaw::getSelfAddress()
{
    return selfAddress;
}

GnetRaw::~GnetRaw()
{
    if (connectionType==UDP_CONNECTION){
        udpSocket->abort();
        delete udpSocket;
    }
}
