#include "include/gnetraw.h"

GnetRaw::GnetRaw(QObject *parent) : QObject(parent)
{
    initSocket();
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             qDebug() <<"Self ip address: " << address.toString();
        selfAddress.append(address);
    }
}


void GnetRaw::initSocket()
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4, 7777, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(readPendingDatagrams()));
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
        if(selfA)qDebug() << "echo: " << sender.toString() << datagram.toHex();
            else qDebug() << "in: " << sender.toString() << datagram.toHex();
    }
}

void GnetRaw::sendGDatagram(unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType, QVector<Gcpd> &cpd){
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
}

GnetRaw::~GnetRaw()
{
    udpSocket->abort();
    delete udpSocket;
}

Gcpd::Gcpd(unsigned char command, unsigned char port, unsigned char data)
{
    this->command=command;
    this->data=data;
    this->port=port;
}
