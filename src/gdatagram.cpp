#include "include/gdatagram.h"

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

void GDatagram::setDateStamp()
{
    this->date = QDateTime::currentDateTimeUtc();
}

void GDatagram::setDateStamp(QDateTime t)
{
    this->date = t;
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

QString GDatagram::toString()
{//.arg(this->date.toString())
    QString str;
    str = QString("t (%1):sz %2:n %3:af %4:nf %5:at %6:nt %7:dt %8:")\
            .arg(this->date.toString("dd HH:mm:ss"))\
            .arg(this->getSize()-1)\
            .arg(this->number)\
            .arg(this->addrFrom)\
            .arg(this->netFrom)\
            .arg(this->addrTo)\
            .arg(this->netTo)\
            .arg(this->devType)\
            ;
    QVector<Gcpd>::iterator i;
    for (i = cpd.begin(); i != cpd.end(); ++i){
        str+= QString ("(c %1:p %2:d %3)").arg(i->command).arg(i->port).arg(i->data);
    }
    return str;
}

GDatagram::GDatagram(QByteArray array)
{
   int size = array[0];
   if ((size+1 == array.size()) && (array.size() >= GDatagram::DATAGRAM_SIZE+Gcpd::CPD_SIZE+1)){
    this->number = array[3];
    this->addrFrom = array[1];
    this->netFrom = array[4];
    this->addrTo = array[5];
    this->netTo = array[6];
    this->devType = array[7];

    for (int i=GDatagram::DATAGRAM_SIZE+1; i<size;i+=3){
        this->appendCpd(Gcpd(array[i],array[i+1], array[i+2]));
        }

   } else {
       this->number = 0;
       this->addrFrom = 0;
       this->netFrom = 0;
       this->addrTo = 0;
       this->netTo = 0;
       this->devType = 0;
   }
}
