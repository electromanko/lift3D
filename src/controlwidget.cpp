#include "include/controlwidget.h"
#include "include/cmddialog.h"

#include <QGridLayout>
#include <QHeaderView>
#include <QMouseEvent>
#include <QShortcut>
#include <QInputDialog>




/*const QString EXAMPLE_TOPIC = "qmqtt/exampletopic";
quint16 _number;*/

ControlWidget::ControlWidget (Lifter *lifter, QWidget *parent) : QWidget(parent)
{

    /*_number=0;
    client = new QMQTT::Client(QHostAddress("192.168.24.142"), 1883);
    connect(client, SIGNAL(connected()), this, SLOT(onConnected()));
    client->setClientId("RomaQT");
    client->setUsername("");
    client->setPassword("");
    client->connectToHost();*/
    /*IOmqtt mqttExample(QHostAddress("192.168.24.145"),1883);
    //mqttExample.setHostName("liftmaster");
    //mqttExample.setHost(QHostAddress("192.168.24.142"));
    mqttExample.connectToHost();*/

    move3DFlag=MOVE_STOP;
    //posCursor3d.setX(500);
    //posCursor3d.setY(500);
    //posCursor3d.setZ(500);
    this->lifter = lifter;

    liftTableView = new QTableView();

    upButton = new QPushButton(tr("&Up"));
    upButton->setFocusPolicy(Qt::NoFocus);
    upButton->setStatusTip(tr("Up key: w"));
    //upButton->setShortcut(QKeySequence(Qt::Key_8));

    downButton = new QPushButton(tr("&Down"));
    downButton->setFocusPolicy(Qt::NoFocus);
    downButton->setStatusTip(tr("Down key: s"));
    //downButton->setShortcut(QKeySequence(Qt::Key_2));

    findButton = new QPushButton(tr("&Find"));
    findButton->setFocusPolicy(Qt::NoFocus);
    findButton->setStatusTip(tr("Find key: f"));

    stopButton = new QPushButton(tr("&Stop"));
    stopButton->setStatusTip(tr("Stop ALL key: Space"));
    stopButton->setFocusPolicy(Qt::NoFocus);

    gotoButton = new QPushButton(tr("&Goto"));
    gotoButton->setFocusPolicy(Qt::NoFocus);
    gotoButton->setStatusTip(tr("Goto key: g | Enter"));

    parkButton = new QPushButton(tr("&Park"));
    parkButton->setFocusPolicy(Qt::NoFocus);
    parkButton->setStatusTip(tr("Park key: p"));

    heightSlider = new QSlider(Qt::Horizontal);
    //heightSlider->se

    QGridLayout *mainLayout = new QGridLayout;
    QGridLayout *controlLayout = new QGridLayout;

    liftTableModel = new LiftTable(lifter);
    liftTableView->setModel(liftTableModel);
    liftTableView->horizontalHeader()->setStretchLastSection(true);
    QHeaderView *verticalHeader = liftTableView->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
    verticalHeader->setDefaultSectionSize(24);
    liftTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    liftTableView->verticalHeader()->hide();
    //liftTableView->installEventFilter(this);
    liftTableView->setShowGrid(false);

    /*moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(moveTimerTimeout()));*/

    mainLayout->addWidget(liftTableView, 0,0);
    mainLayout->addLayout(controlLayout, 1,0);
        controlLayout->addWidget(parkButton, 0,0);
        controlLayout->addWidget(gotoButton, 1,0);
        controlLayout->addWidget(findButton, 2,0);

        controlLayout->addWidget(upButton, 0,1);
        controlLayout->addWidget(downButton, 1,1);
        controlLayout->addWidget(stopButton, 2,1);

    //mainLayout->addWidget(heightSlider,5,0);


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
    connect(stopButton, SIGNAL(clicked()),
            this, SLOT(stopMove()));
    connect(gotoButton, SIGNAL(clicked()),
                    this, SLOT(goTo()));
    connect(parkButton, SIGNAL(clicked()),
            this, SLOT(park()));
    connect(heightSlider, SIGNAL(valueChanged(int)),
            this, SLOT(goSlider(int)));

    connect(lifter,SIGNAL(addedLiftToList(int, int )),
            liftTableModel, SLOT(addRows(int, int )));
    connect(lifter,SIGNAL(removedLiftToList(int, int )),
            liftTableModel, SLOT(deleteRows(int, int )));

    connect(lifter,SIGNAL(liftUpdated(int)),
            liftTableModel, SLOT(liftUpdate(int)));
    //this->dumpObjectTree();
    //moveTimer->start(move3DTime);

}

ControlWidget::~ControlWidget()
{
}

void ControlWidget::upDemand()
{
    QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
    QList<QModelIndex>::iterator i;
    for (i=list.begin();i!=list.end();++i){
        lifter->upDemand(i->row());
    }
    qDebug("upDemand");
}

void ControlWidget::downDemand()
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

void ControlWidget::stopMove()
{

    //lifter->stop(liftTableView->selectionModel()->currentIndex().row());
    QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
    QList<QModelIndex>::iterator i;
    for (i=list.begin();i!=list.end();++i){
        lifter->stop(i->row());
    }
    qDebug("stop"); //<< QString("finish");
}

void ControlWidget::stopAll()
{
 lifter->stopAll();
}

void ControlWidget::findLift()
{
    lifter->findLifts();
}

void ControlWidget::park()
{
    QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
    QList<QModelIndex>::iterator i;
    for (i=list.begin();i!=list.end();++i){
        lifter->goPark(i->row());
    }
    //lifter->goPark(liftTableView->selectionModel()->currentIndex().row());

}

void ControlWidget::goTo()
{
    bool ok;
    int hmm = QInputDialog::getInt(this, tr("Go"),
                                 tr("Height(mm):"), 0, 0, 100000, 1, &ok);
    if (ok)
    {
        QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
        QList<QModelIndex>::iterator i;
        for (i=list.begin();i!=list.end();++i){
            lifter->goMm75(i->row(), hmm);
        }
        qDebug("goTo"); //<< QString("finish");
    }
}

void ControlWidget::goToRaw()
{
    bool ok;
    int hmm = QInputDialog::getInt(this, tr("Go RAW"),
                                 tr("Height(mm):"), 0, 0, 100000, 1, &ok);
    if (ok)
    {
        QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
        QList<QModelIndex>::iterator i;
        for (i=list.begin();i!=list.end();++i){
            lifter->goRaw(i->row(), hmm);
        }
        qDebug("goTo"); //<< QString("finish");
    }
}

void ControlWidget::goSlider(int value){
    qDebug() << value;
    int hmm=value;
    QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
    QList<QModelIndex>::iterator i;
    for (i=list.begin();i!=list.end();++i){
        lifter->goRaw(i->row(), hmm);
    }
}
/*
void ControlWidget::moveTimerTimeout()
{
    if(move3DFlag==MOVE_STOP){}
    else
    {switch (move3DFlag){
    case MOVE_XP:
        posCursor3d.setX(posCursor3d.x()+move3DdeltaPosition);
        break;
    case MOVE_XM:
        posCursor3d.setX(posCursor3d.x()-move3DdeltaPosition);
        break;
    case MOVE_YP:
            posCursor3d.setY(posCursor3d.y()+move3DdeltaPosition);
        break;
    case MOVE_YM:
            posCursor3d.setY(posCursor3d.y()-move3DdeltaPosition);
        break;
    case MOVE_ZP:
            posCursor3d.setZ(posCursor3d.z()+move3DdeltaPosition);
        break;
    case MOVE_ZM:
            posCursor3d.setZ(posCursor3d.z()-move3DdeltaPosition);
        break;
    case MOVE_GOTO:
        break;

    }
    xLabel->setText(QString::number(posCursor3d.x()));
    yLabel->setText(QString::number(posCursor3d.y()));
    zLabel->setText(QString::number(posCursor3d.z()));

    //lifter->moveDirect3d(posCursor3d);
    }
}
*/
void ControlWidget::sendCmd(){
   CmdDialog dialog(this);

   if (dialog.exec() == QDialog::Accepted ) {
       qDebug() << "You pressed OK!";
        QVector<Gcpd> vect = dialog.getCpd();
        if (vect.count()==0) return;
        QList<QModelIndex> list=liftTableView->selectionModel()->selectedRows();
        QList<QModelIndex>::iterator i;
        for (i=list.begin();i!=list.end();++i){
            lifter->sendCmd(i->row(), vect);
        }
      }
}
/*
bool ControlWidget::eventFilter(QObject *target, QEvent *event)
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
            case Qt::Key_F:
                findLift();
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
            case Qt::Key_Z:

                return true;
            case Qt::Key_X:
                return true;
            }
        } else if (event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->isAutoRepeat())return QObject::eventFilter(target, event);
            switch (keyEvent->key()){
            case Qt::Key_W:
            case Qt::Key_S:
                move3DFlag=MOVE_STOP;
                stopMove();
                return true;
            }
        }

    return QObject::eventFilter(target, event);
}
*/
void ControlWidget::adjustLiftTableSize()
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
/*
void ControlWidget::onConnected(){
    client->subscribe(EXAMPLE_TOPIC, 0);
    qDebug("Connected mqtt");
    QMQTT::Message message(_number, EXAMPLE_TOPIC,
    QString("Number is %1").arg(_number).toUtf8());
    client->publish(message);

}
*/
