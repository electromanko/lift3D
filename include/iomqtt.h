#ifndef IOMQTT_H
#define IOMQTT_H

#include "qmqtt.h"

const QString EXAMPLE_TOPIC = "qmqtt/exampletopic";

class IOmqtt : public QMQTT::Client
{
    Q_OBJECT
public:

    explicit IOmqtt(const QHostAddress& host = QHostAddress::LocalHost,
                       const quint16 port = 1883,
                       QObject* parent = NULL);
    virtual ~IOmqtt() {}

private:
    int number;
    QTextStream _qout;

public slots:
    void onConnected();
    void onDisconnected();
    void onSubscribed(const QString& topic, const quint8 qos);
    void onReceived(const QMQTT::Message& message);
    void onError(const QMQTT::ClientError error);
};

#endif // IOMQTT_H
