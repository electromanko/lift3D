#ifndef GNETRAW_H
#define GNETRAW_H

#include <QObject>
#include <QUdpSocket>
#include <QByteArray>
#include <QNetworkInterface>

class Gcpd;
class GDatagram;
class GnetRaw: public QObject
{
    Q_OBJECT
public:
    explicit GnetRaw(QObject *parent = 0);
    void initSocket();

    void sendGDatagram(unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType, QVector<Gcpd> &cpd);
    void sendGDatagram(GDatagram &datagram);

    ~GnetRaw();
private:
    QUdpSocket *udpSocket;
    QVector<QHostAddress> selfAddress;
signals:
    void received(QHostAddress ip, GDatagram datagram);
public slots:
    void readPendingDatagrams();

};

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


    unsigned char addrFrom;
    unsigned char netFrom;
    unsigned char addrTo;
    unsigned char netTo;
    unsigned char devType;
    unsigned char number;
    unsigned int getSize();
    void appendCpd(const Gcpd &cpd);
    void clearCpd();
    QByteArray toQByteArray();
    QString toString();

    QVector<Gcpd> cpd;
};

#endif // GNETRAW_H
