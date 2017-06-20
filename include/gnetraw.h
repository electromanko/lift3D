#ifndef GNETRAW_H
#define GNETRAW_H

#include <QObject>
#include <QUdpSocket>
#include <QByteArray>
#include <QNetworkInterface>
#include <QDateTime>
#include "include/gdatagram.h"
#include "qmqtt.h"

class GnetRaw: public QObject
{
    Q_OBJECT
public:
    explicit GnetRaw(QObject *parent = 0);

    int udpPort;

    static const int NO_CONNECTION=0;
    static const int UDP_CONNECTION=1;
    static const int MQTT_CONNECTION=2;

    void connect_udp(int port);
    void connect_mqtt(const QString &hostname, int port);
    int getConnectionType();
    void disconnect();

    //void sendGDatagram(unsigned char addrFrom, unsigned char netFrom, unsigned char addrTo, unsigned char netTo, unsigned char devType, QVector<Gcpd> &cpd);
    void sendGDatagram(GDatagram &datagram);
    QVector<QHostAddress> getSelfAddress();

    ~GnetRaw();

private:
    int connectionType;
    QUdpSocket *udpSocket;
    QMQTT::Client *mqttClient;
    QVector<QHostAddress> selfAddress;

signals:
    void received(QHostAddress ip, GDatagram datagram);
    void sended(QHostAddress ip, GDatagram datagram);

public slots:
    void readPendingDatagrams();
    void mqttOnConnected();
    void mqttOnDisonnected();
    void mqttOnError(const QMQTT::ClientError);
    void mqttOnReceived(const QMQTT::Message&);
};



#endif // GNETRAW_H
