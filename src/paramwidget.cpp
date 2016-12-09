#include "include/paramwidget.h"

#include <QGridLayout>

ParamWidget::ParamWidget(QWidget *parent) : QWidget(parent)
{
    //gnet = new GnetRaw();
    lifter = new Lifter(15,0,32);
    upButton = new QPushButton(tr("&Up"));
    downButton = new QPushButton(tr("&Down"));
    findButton = new QPushButton(tr("&Find"));
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(findButton, 0,0);
    mainLayout->addWidget(upButton, 1,0);
    mainLayout->addWidget(downButton, 2,0);

    setLayout(mainLayout);

    connect(findButton, SIGNAL(clicked()),
            this, SLOT(findLift()));
    connect(upButton, SIGNAL(pressed()),
            this, SLOT(upDemand()));
    connect(upButton, SIGNAL(released()),
            this, SLOT(stopMove()));
    connect(downButton, SIGNAL(pressed()),
            this, SLOT(downDemand()));
    connect(downButton, SIGNAL(released()),
            this, SLOT(stopMove()));
}

ParamWidget::~ParamWidget()
{
    delete lifter;
}

void ParamWidget::upDemand()
{
    GDatagram datagram(0,10,0,30,0,32);
    datagram.appendCpd(Gcpd(1,35,1));
    //QVector<Gcpd> cpd;
    //cpd.append(Gcpd(1,35,1));
    //gnet->sendGDatagram(10,0,30,0,32,cpd);
    //gnet->sendGDatagram(10,0,31,0,32,cpd);
    gnet->sendGDatagram(datagram);
    datagram.addrTo = 31;
    gnet->sendGDatagram(datagram);
    qDebug("upDemand");// << QString("star");
}

void ParamWidget::downDemand()
{
    /*QVector<Gcpd> cpd;
    cpd.append(Gcpd(1,36,1));
    gnet->sendGDatagram(10,0,30,0,32,cpd);
    gnet->sendGDatagram(10,0,31,0,32,cpd);*/
    GDatagram datagram(0,10,0,30,0,32);
    datagram.appendCpd(Gcpd(1,36,1));
    gnet->sendGDatagram(datagram);
    datagram.addrTo = 31;
    gnet->sendGDatagram(datagram);

    qDebug("downDemand"); //<< QString("finish");
}

void ParamWidget::stopMove()
{
    /*QVector<Gcpd> cpd;
    cpd.append(Gcpd(1,37,1));
    gnet->sendGDatagram(10,0,30,0,32,cpd);
    gnet->sendGDatagram(10,0,31,0,32,cpd);*/
    GDatagram datagram(0,10,0,30,0,32);
    datagram.appendCpd(Gcpd(1,37,1));
    gnet->sendGDatagram(datagram);
    datagram.addrTo = 31;
    gnet->sendGDatagram(datagram);
    qDebug("stop"); //<< QString("finish");
}

void ParamWidget::findLift()
{
    lifter->findLifts();
}

