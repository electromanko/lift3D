#ifndef GNETRAW_H
#define GNETRAW_H

#include <QObject>
#include <QUdpSocket>
#include <QByteArray>
#include <QNetworkInterface>

class Gcpd;
class GnetRaw: public QObject
{
    Q_OBJECT
public:
    explicit GnetRaw(QObject *parent = 0);
    void initSocket();

    void sendGDatagram(unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType, QVector<Gcpd> &cpd);
    ~GnetRaw();
private:
    QUdpSocket *udpSocket;
    QVector<QHostAddress> selfAddress;
signals:
    recive();
public slots:
    void readPendingDatagrams();

};

class Gcpd{
public:
    Gcpd(unsigned char command=0, unsigned char port=0, unsigned char data=0);
    unsigned char command;
    unsigned char port;
    unsigned char data;
};

#endif // GNETRAW_H
