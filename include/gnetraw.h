#ifndef GNETRAW_H
#define GNETRAW_H

#include <QObject>
#include <QUdpSocket>
#include <QByteArray>
#include <QNetworkInterface>
#include <QDateTime>
#include "include/gdatagram.h"

class GnetRaw: public QObject
{
    Q_OBJECT
public:
    explicit GnetRaw(QObject *parent = 0);
    void initSocket();

    //void sendGDatagram(unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType, QVector<Gcpd> &cpd);
    void sendGDatagram(GDatagram &datagram);
    QVector<QHostAddress> getSelfAddress();

    ~GnetRaw();
private:
    QUdpSocket *udpSocket;
    QVector<QHostAddress> selfAddress;
signals:
    void received(QHostAddress ip, GDatagram datagram);
    void sended(QHostAddress ip, GDatagram datagram);
public slots:
    void readPendingDatagrams();

};



#endif // GNETRAW_H
