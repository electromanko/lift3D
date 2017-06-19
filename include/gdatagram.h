#ifndef GDATAGRAM_H
#define GDATAGRAM_H

#include <QDateTime>
#include <QVector>



class Gcpd{
public:
    static const unsigned char CPD_SIZE=3;
    Gcpd(unsigned char command=0, unsigned char port=0, unsigned char data=0);
    unsigned char command;
    unsigned char port;
    unsigned char data;
};

class GDatagram{
public:
    static const unsigned char DATAGRAM_TYPE=1;
    static const unsigned char DATAGRAM_SIZE=7;

    GDatagram();
    GDatagram(unsigned char number, unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType, QVector<Gcpd> &cpd);
    GDatagram(unsigned char number, unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType);
    GDatagram(QByteArray array);
    ~GDatagram();

    QDateTime date;
    unsigned char addrFrom;
    unsigned char netFrom;
    unsigned char addrTo;
    unsigned char netTo;
    unsigned char devType;
    unsigned char number;
    unsigned int getSize();
    void setDateStamp();
    void setDateStamp(QDateTime t);
    void appendCpd(const Gcpd &cpd);
    void clearCpd();

    QByteArray toQByteArray();
    QString toString();

    QVector<Gcpd> cpd;
};

#endif // GDATAGRAM_H
