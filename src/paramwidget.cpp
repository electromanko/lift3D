#include "include/paramwidget.h"
#include "include/cmddialog.h"

#include <QGridLayout>
#include <QHeaderView>
#include <QMouseEvent>
#include <QShortcut>
#include <QInputDialog>


ParamWidget::ParamWidget(QWidget *parent) : QWidget(parent)
{
    //gnet = new GnetRaw();
    lifter = new Lifter(15,0,32);
    liftTableView = new QTableView();

    upButton = new QPushButton(tr("&Up"));
    upButton->setFocusPolicy(Qt::NoFocus);
    //upButton->setShortcut(QKeySequence(Qt::Key_8));

    downButton = new QPushButton(tr("&Down"));
    downButton->setFocusPolicy(Qt::NoFocus);
    //downButton->setShortcut(QKeySequence(Qt::Key_2));

    findButton = new QPushButton(tr("&Find"));
    findButton->setFocusPolicy(Qt::NoFocus);

    parkButton = new QPushButton(tr("&Park"));
    parkButton->setFocusPolicy(Qt::NoFocus);

    QGridLayout *mainLayout = new QGridLayout;

    liftTableModel = new LiftTable(lifter);
    liftTableView->setModel(liftTableModel);
    liftTableView->horizontalHeader()->setStretchLastSection(true);
    QHeaderView *verticalHeader = liftTableView->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    verticalHeader->setDefaultSectionSize(24);
    liftTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    liftTableView->verticalHeader()->hide();
    liftTableView->installEventFilter(this);
    liftTableView->setShowGrid(false);


    mainLayout->addWidget(liftTableView, 0,0);
    mainLayout->addWidget(findButton, 1,0);
    mainLayout->addWidget(upButton, 2,0);
    mainLayout->addWidget(downButton, 3,0);
    mainLayout->addWidget(parkButton, 4,0);

    adjustLiftTableSize();
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
    connect(parkButton, SIGNAL(clicked()),
            this, SLOT(park()));

    connect(lifter,SIGNAL(addedLiftToList(int, int )),
            liftTableModel, SLOT(addRows(int, int )));
    connect(lifter,SIGNAL(removedLiftToList(int, int )),
            liftTableModel, SLOT(deleteRows(int, int )));

    connect(lifter,SIGNAL(liftUpdated(int)),
            liftTableModel, SLOT(liftUpdate(int)));
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
    QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
    QList<QModelIndex>::iterator i;
    for (i=list.begin();i!=list.end();++i){
        lifter->upDemand(i->row());
    }
    //lifter->upDemand(0);
    //lifter->upDemand(1);
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

    //lifter->downDemand(0);
    //lifter->downDemand(1);

    //lifter->downDemand(liftTableView->selectionModel()->currentIndex().row());
    QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
    QList<QModelIndex>::iterator i;
    for (i=list.begin();i!=list.end();++i){
        lifter->downDemand(i->row());
    }
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

    //lifter->stop(0);
    //lifter->stop(1);
    //lifter->stop(liftTableView->selectionModel()->currentIndex().row());
    QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
    QList<QModelIndex>::iterator i;
    for (i=list.begin();i!=list.end();++i){
        lifter->stop(i->row());
    }
    qDebug("stop"); //<< QString("finish");
}

void ParamWidget::stopAll()
{
 lifter->stopAll();
}

void ParamWidget::findLift()
{
    lifter->findLifts();
}

void ParamWidget::park()
{
    QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
    QList<QModelIndex>::iterator i;
    for (i=list.begin();i!=list.end();++i){
        lifter->goPark(i->row());
    }
    //lifter->goPark(liftTableView->selectionModel()->currentIndex().row());

}

void ParamWidget::goTo()
{
    bool ok;
    int hmm = QInputDialog::getInt(this, tr("Go"),
                                 tr("Height(mm):"), 0, 0, 11000, 1, &ok);
    if (ok)
    {
        QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
        QList<QModelIndex>::iterator i;
        for (i=list.begin();i!=list.end();++i){
            lifter->goMm(i->row(), hmm);
        }
        qDebug("stop"); //<< QString("finish");
    }
}

void ParamWidget::sendCmd(){
   CmdDialog dialog(this);
   dialog.exec();
}

bool ParamWidget::eventFilter(QObject *target, QEvent *event)
{

        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->isAutoRepeat())return QObject::eventFilter(target, event);
            switch (keyEvent->key()){
            case Qt::Key_W:
                upDemand();
                return true;
            case Qt::Key_S:
                downDemand();
                return true;
            case Qt::Key_P:
                park();
                return true;
            case Qt::Key_Space:
                stopAll();
                return true;
            case Qt::Key_G:
            case Qt::Key_Return:
                goTo();
                return true;
            case Qt::Key_C:
                sendCmd();
                return true;
            }
        } else if (event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->isAutoRepeat())return QObject::eventFilter(target, event);
            switch (keyEvent->key()){
            case Qt::Key_W:
            case Qt::Key_S:
                stopMove();
                return true;
            }
        }

    return QObject::eventFilter(target, event);
}

void ParamWidget::adjustLiftTableSize()
{
    liftTableView->resizeColumnToContents(1);
    liftTableView->resizeColumnToContents(2);
    liftTableView->resizeColumnToContents(3);
    liftTableView->resizeColumnToContents(4);
    liftTableView->resizeColumnToContents(5);

    QRect rect = liftTableView->geometry();
    rect.setWidth(2 + liftTableView->verticalHeader()->width() +
            liftTableView->columnWidth(0) + liftTableView->columnWidth(1) + liftTableView->columnWidth(2)
                  + liftTableView->columnWidth(3) + liftTableView->columnWidth(4) + liftTableView->columnWidth(5));
    liftTableView->setGeometry(rect);
}


