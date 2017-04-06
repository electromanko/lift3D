#include "include/iowidget.h"

#include <QGridLayout>

IOwidget::IOwidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;

    textEdit = new QTextEdit;
    mainLayout->addWidget(textEdit, 0,0);
    setLayout(mainLayout);
}

IOwidget::receivedDatagram(QHostAddress ip, GDatagram datagram)
{
    textEdit->append(datagram.toString());
}

IOwidget::sendedDatagram(GDatagram datagram)
{

}
