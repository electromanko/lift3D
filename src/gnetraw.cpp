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
        if(selfA){
            qDebug() << "echo: " << sender.toString() << datagram.toHex();
        }
        else {
            emit received(GDatagram(datagram));
            qDebug() << "in: " << sender.toString() << datagram.toHex();
        }
    }
}

void GnetRaw::sendGDatagram(unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType, QVector<Gcpd> &cpd)
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
}

void GnetRaw::sendGDatagram(GDatagram &gdatagram)
{
    QByteArray datagram = gdatagram.toQByteArray();
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

GDatagram::GDatagram()
{
    number=addrFrom=netFrom=addrTo=netTo=devType=0;
}

GDatagram::GDatagram(unsigned char number, unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType, QVector<Gcpd> &cpd)
{
    this->number = number;
    this->addrFrom = addrFrom;
    this->netFrom = netFrom;
    this->addrTo = addrTo;
    this->netTo = netTo;
    this->devType = devType;
    this->cpd = cpd;
}

GDatagram::GDatagram(unsigned char number, unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType)
{
    this->number = number;
    this->addrFrom = addrFrom;
    this->netFrom = netFrom;
    this->addrTo = addrTo;
    this->netTo = netTo;
    this->devType = devType;
}

GDatagram::~GDatagram()
{

}

unsigned int GDatagram::getSize()
{
    return (GDatagram::DATAGRAM_SIZE+cpd.count()* Gcpd::CPD_SIZE + 1);
}

void GDatagram::appendCpd(const Gcpd &cpd)
{
   this->cpd.append(cpd);
}

void GDatagram::clearCpd()
{
   this->cpd.clear();
}

QByteArray GDatagram::toQByteArray()
{
    QByteArray datagram = QByteArray::number(this->getSize());
    datagram[0]=GDatagram::DATAGRAM_SIZE+cpd.count()* Gcpd::CPD_SIZE; //Size val
    datagram[1]= addrFrom;
    datagram[2]=GDatagram::DATAGRAM_TYPE;
    datagram[3]= number; //Number
    datagram[4]= netFrom;
    datagram[5]= addrTo;
    datagram[6]= netTo;
    datagram[7]= devType;
    QVector<Gcpd>::iterator i;
    int n=8;
    for (i = cpd.begin(); i != cpd.end(); ++i){
        datagram[n]=i->command;
        datagram[n+1]=i->port;
        datagram[n+2]=i->data;
        n+=3;
    }
    return datagram;
}

GDatagram::GDatagram(QByteArray array)
{
   int size = array[0];
   if ((size+1 == array.size()) || (array.size() <= GDatagram::DATAGRAM_SIZE+Gcpd::CPD_SIZE+1)){
    this->number = array[3];
    this->addrFrom = array[1];
    this->netFrom = array[4];
    this->addrTo = array[5];
    this->netTo = array[6];
    this->devType = array[7];

    for (int i=GDatagram::DATAGRAM_SIZE+1; i<size;i+=3){
        this->appendCpd(Gcpd(array[i],array[i+1], array[i+2]));
        }

   }
}
