#include "include/iomqtt.h"

IOmqtt::IOmqtt(const QHostAddress& host,
                       const quint16 port,
                       QObject* parent)
                : QMQTT::Client(host, port, parent)
                    , number(0)
{
   connect(this, SIGNAL(connected()), this, SLOT(onConnected()));
   connect(this, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
   connect(this, SIGNAL(subscribed(const QString&, const quint8)), this, SLOT(onSubscribed(const QString&, const quint8)));
   connect(this, SIGNAL(received(const QMQTT::Message&)), this, SLOT(onReceived(const QMQTT::Message&)));
   connect(this, SIGNAL(error(const QMQTT::ClientError)), this, SLOT(onError(const QMQTT::ClientError)));

   setClientId("RomaQT");
   setUsername("");
   setPassword("");
}

void IOmqtt::onConnected()
{
   subscribe(EXAMPLE_TOPIC, 0);
   qDebug("Connected mqtt");
   QMQTT::Message message(number, EXAMPLE_TOPIC,
   QString("Number is %1").arg(number).toUtf8());
   publish(message);
   number++;
}

void IOmqtt::onDisconnected()
{

}

void IOmqtt::onSubscribed(const QString& topic, const quint8 qos)
{
    _qout << "subscribed " << topic << endl;
}

void IOmqtt::onReceived(const QMQTT::Message& message)
{
    _qout << "publish received: \"" << QString::fromUtf8(message.payload())
          << "\"" << endl;
}

void IOmqtt::onError(const QMQTT::ClientError error){
    qDebug("Error mqtt");
}
