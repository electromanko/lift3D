#include "include/paramwidget.h"

#include <QGridLayout>



ParamWidget::ParamWidget(QWidget *parent) : QWidget(parent)
{
    //gnet = new GnetRaw();
    lifter = new Lifter(15,0,32);
    liftTableView = new QTableView();
    upButton = new QPushButton(tr("&Up"));
    downButton = new QPushButton(tr("&Down"));
    findButton = new QPushButton(tr("&Find"));
    QGridLayout *mainLayout = new QGridLayout;

    liftTableModel = new LiftTable(lifter);
    liftTableView->setModel(liftTableModel);

    mainLayout->addWidget(liftTableView, 0,0);
    mainLayout->addWidget(findButton, 1,0);
    mainLayout->addWidget(upButton, 2,0);
    mainLayout->addWidget(downButton, 3,0);

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
   /* GDatagram datagram(0,10,0,30,0,32);
    datagram.appendCpd(Gcpd(1,35,1));
    //QVector<Gcpd> cpd;
    //cpd.append(Gcpd(1,35,1));
    //gnet->sendGDatagram(10,0,30,0,32,cpd);
    //gnet->sendGDatagram(10,0,31,0,32,cpd);

    gnet->sendGDatagram(datagram);
    datagram.addrTo = 31;
    gnet->sendGDatagram(datagram);*/
    lifter->upDemand(0);
    lifter->upDemand(1);
    qDebug("upDemand");// << QString("star");
}

void ParamWidget::downDemand()
{
    /*QVector<Gcpd> cpd;
    cpd.append(Gcpd(1,36,1));
    gnet->sendGDatagram(10,0,30,0,32,cpd);
    gnet->sendGDatagram(10,0,31,0,32,cpd);*/

    /*GDatagram datagram(0,10,0,30,0,32);
    datagram.appendCpd(Gcpd(1,36,1));
    gnet->sendGDatagram(datagram);
    datagram.addrTo = 31;
    gnet->sendGDatagram(datagram);*/

    lifter->downDemand(0);
    lifter->downDemand(1);
    qDebug("downDemand"); //<< QString("finish");
}

void ParamWidget::stopMove()
{
    /*QVector<Gcpd> cpd;
    cpd.append(Gcpd(1,37,1));
    gnet->sendGDatagram(10,0,30,0,32,cpd);
    gnet->sendGDatagram(10,0,31,0,32,cpd);*/

    /*GDatagram datagram(0,10,0,30,0,32);
    datagram.appendCpd(Gcpd(1,37,1));
    gnet->sendGDatagram(datagram);
    datagram.addrTo = 31;
    gnet->sendGDatagram(datagram);*/
    lifter->stop(0);
    lifter->stop(1);
    //liftTableModel->update();
    qDebug("stop"); //<< QString("finish");
}

void ParamWidget::findLift()
{
    lifter->findLifts();
}

