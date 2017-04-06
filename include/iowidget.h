#ifndef IOWIDGET_H
#define IOWIDGET_H

#include "gnetraw.h"

#include <QTextEdit>
#include <QWidget>

class IOwidget : public QWidget
{
    Q_OBJECT
public:
    explicit IOwidget(QWidget *parent = 0);
    QTextEdit* textEdit;
signals:

public slots:
    receivedDatagram (QHostAddress ip, GDatagram datagram);
    sendedDatagram (GDatagram datagram);
};

#endif // IOWIDGET_H
