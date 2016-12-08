#include "include/paramwidget.h"

#include <QGridLayout>

ParamWidget::ParamWidget(QWidget *parent) : QWidget(parent)
{
    gnet = new GnetRaw();
    upButton = new QPushButton(tr("&Up"));
    downButton = new QPushButton(tr("&Down"));
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(upButton, 0,0);
    mainLayout->addWidget(downButton, 1,0);
    setLayout(mainLayout);

    connect(upButton, SIGNAL(pressed()),
            this, SLOT(upDemand()));
    connect(upButton, SIGNAL(released()),
            this, SLOT(stopMove()));
    connect(downButton, SIGNAL(pressed()),
            this, SLOT(downDemand()));
    connect(downButton, SIGNAL(released()),
            this, SLOT(stopMove()));
}

void ParamWidget::upDemand()
{
    QVector<Gcpd> cpd;
    cpd.append(Gcpd(1,35,1));
    gnet->sendGDatagram(10,0,30,0,32,cpd);
    gnet->sendGDatagram(10,0,31,0,32,cpd);
    qDebug("upDemand");// << QString("star");
}

void ParamWidget::downDemand()
{
    QVector<Gcpd> cpd;
    cpd.append(Gcpd(1,36,1));
    gnet->sendGDatagram(10,0,30,0,32,cpd);
    gnet->sendGDatagram(10,0,31,0,32,cpd);
    qDebug("downDemand"); //<< QString("finish");
}

void ParamWidget::stopMove()
{
    QVector<Gcpd> cpd;
    cpd.append(Gcpd(1,37,1));
    gnet->sendGDatagram(10,0,30,0,32,cpd);
    gnet->sendGDatagram(10,0,31,0,32,cpd);
    qDebug("stop"); //<< QString("finish");
}
