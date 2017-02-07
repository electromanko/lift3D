#include "include/joywidget.h"

#include <QGridLayout>
#include <QMouseEvent>

Joywidget::Joywidget(Lifter3d *lifter, int iconSize, int move3dDeltaPosition, int move3dTime, QWidget *parent) : QWidget(parent)
{
    QIcon icon;
#define policyV QSizePolicy::MinimumExpanding
#define policyH  QSizePolicy::MinimumExpanding
    this->iconSize=iconSize;
    this->move3dDeltaPosition=move3dDeltaPosition;
    this->move3dTime=move3dTime;
    move3dFlag=MOVE_STOP;


    this->lifter3d=lifter;
    cursorSetup();
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(moveTimerTimeout()));

     QGridLayout *mainLayout = new QGridLayout;

     xpButton = new QPushButton();
     //xpButton->setText(tr("&x+"));
     xpButton->setFocusPolicy(Qt::NoFocus);
     xpButton->setGeometry(QRect(0,0,10,10));
     //QPixmap pix(":/icon/png/128x128/right_arrow.png");

     //icon.addPixmap(pix);
     icon.addFile(":/icon/png/128x128/right_arrow.png");
     xpButton->setIcon(icon);
     xpButton->setIconSize(QSize(iconSize,iconSize));

     xpButton->setSizePolicy(policyH,policyV);

     xmButton = new QPushButton();
     //xpButton->setText(tr("&x-"));
     xmButton->setFocusPolicy(Qt::NoFocus);
     icon.addFile(":/icon/png/128x128/left_arrow.png");
     xmButton->setIcon(icon);
     xmButton->setIconSize(QSize(iconSize,iconSize));
     xmButton->setSizePolicy(policyH,policyV);

     ypButton = new QPushButton();
     ypButton->setFocusPolicy(Qt::NoFocus);
     icon.addFile(":/icon/png/128x128/up_arrow.png");
     ypButton->setIcon(icon);
     ypButton->setIconSize(QSize(iconSize,iconSize));
     ypButton->setSizePolicy(policyH,policyV);

     ymButton = new QPushButton();
     ymButton->setFocusPolicy(Qt::NoFocus);
     icon.addFile(":/icon/png/128x128/down_arrow.png");
     ymButton->setIcon(icon);
     ymButton->setIconSize(QSize(iconSize,iconSize));
     ymButton->setSizePolicy(policyH,policyV);

     zpButton = new QPushButton();
     zpButton->setFocusPolicy(Qt::NoFocus);
     icon.addFile(":/icon/png/128x128/plus.png");
     zpButton->setIcon(icon);
     zpButton->setIconSize(QSize(iconSize,iconSize));
     zpButton->setSizePolicy(policyH,policyV);

     zmButton = new QPushButton();
     zmButton->setFocusPolicy(Qt::NoFocus);
     icon.addFile(":/icon/png/128x128/minus.png");
     zmButton->setIcon(icon);
     zmButton->setIconSize(QSize(iconSize,iconSize));
     zmButton->setSizePolicy(policyH,policyV);

     stopButton = new QPushButton();
     stopButton->setFocusPolicy(Qt::NoFocus);
     icon.addFile(":/icon/png/128x128/close.png");
     stopButton->setIcon(icon);
     stopButton->setIconSize(QSize(iconSize,iconSize));
     stopButton->setSizePolicy(policyH,policyV);

     parkButton = new QPushButton();
     parkButton->setFocusPolicy(Qt::NoFocus);
     icon.addFile(":/icon/png/128x128/house.png");
     parkButton->setIcon(icon);
     parkButton->setIconSize(QSize(iconSize,iconSize));
     parkButton->setSizePolicy(policyH,policyV);

     gotoButton = new QPushButton();
     parkButton->setFocusPolicy(Qt::NoFocus);
     icon.addFile(":/icon/png/128x128/pencil.png");
     gotoButton->setIcon(icon);
     gotoButton->setIconSize(QSize(iconSize,iconSize));
     gotoButton->setSizePolicy(policyH,policyV);

     coordLabel = new QLabel();

     mainLayout->addWidget(xpButton, 1,2);
     mainLayout->addWidget(xmButton, 1,0);
     mainLayout->addWidget(ypButton, 0,1);
     mainLayout->addWidget(ymButton, 2,1);
     mainLayout->addWidget(zpButton, 0,2);
     mainLayout->addWidget(zmButton, 2,2);

     mainLayout->addWidget(stopButton, 1,1);
     mainLayout->addWidget(parkButton, 0,0);
     mainLayout->addWidget(gotoButton, 2,0);
    mainLayout->addWidget(coordLabel, 3,0);

     setLayout(mainLayout);
     moveTimer->start(move3dTime);
     connect(xpButton, SIGNAL(pressed()),
             this, SLOT(xp()));
     connect(xpButton, SIGNAL(released()),
             this, SLOT(stop()));
     connect(xmButton, SIGNAL(pressed()),
             this, SLOT(xm()));
     connect(xmButton, SIGNAL(released()),
             this, SLOT(stop()));
     connect(ypButton, SIGNAL(pressed()),
             this, SLOT(yp()));
     connect(ypButton, SIGNAL(released()),
             this, SLOT(stop()));
     connect(ymButton, SIGNAL(pressed()),
             this, SLOT(ym()));
     connect(ymButton, SIGNAL(released()),
             this, SLOT(stop()));
     connect(zpButton, SIGNAL(pressed()),
             this, SLOT(zp()));
     connect(zpButton, SIGNAL(released()),
             this, SLOT(stop()));
     connect(zmButton, SIGNAL(pressed()),
             this, SLOT(zm()));
     connect(zmButton, SIGNAL(released()),
             this, SLOT(stop()));
     connect(parkButton, SIGNAL(released()),
             this, SLOT(park()));
}

void Joywidget::moveTimerTimeout(){
    coordLabel->setText(QString("%1,%2,%3").arg(QString::number(posCursor3d.x())).arg(QString::number(posCursor3d.y())).arg(QString::number(posCursor3d.z())));
    QVector3D pc3d=posCursor3d;
    if(move3dFlag==MOVE_STOP){}
    else
    {
    switch (move3dFlag){
    case MOVE_XP:
        pc3d.setX(pc3d.x()+move3dDeltaPosition);
        break;
    case MOVE_XM:
        pc3d.setX(pc3d.x()-move3dDeltaPosition);
        break;
    case MOVE_YP:
            pc3d.setY(pc3d.y()+move3dDeltaPosition);
        break;
    case MOVE_YM:
            pc3d.setY(pc3d.y()-move3dDeltaPosition);
        break;
    case MOVE_ZP:
            pc3d.setZ(pc3d.z()+move3dDeltaPosition);
        break;
    case MOVE_ZM:
            pc3d.setZ(pc3d.z()-move3dDeltaPosition);
        break;
    case MOVE_GOTO:
        break;

    }
    /*xLabel->setText(QString::number(posCursor3d.x()));
    yLabel->setText(QString::number(posCursor3d.y()));
    zLabel->setText(QString::number(posCursor3d.z()));*/

    if (lifter3d->moveDirect3d(pc3d)) posCursor3d=pc3d;
    }
}

void Joywidget::xp()
{
    move3dFlag=MOVE_XP;
}

void Joywidget::xm()
{
    move3dFlag=MOVE_XM;
}

void Joywidget::yp()
{
    move3dFlag=MOVE_YP;
}

void Joywidget::ym()
{
    move3dFlag=MOVE_YM;
}

void Joywidget::zp()
{
    move3dFlag=MOVE_ZP;
}

void Joywidget::zm()
{
    move3dFlag=MOVE_ZM;
}

void Joywidget::stop()
{
    move3dFlag=MOVE_STOP;
}

void Joywidget::park()
{
    this->lifter3d->park3d();
}

void Joywidget::go()
{

}

void Joywidget::cursorSetup(){
    posCursor3d=lifter3d->limitCubePoint0;
}

bool Joywidget::eventFilter(QObject *target, QEvent *event)
{
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->isAutoRepeat())return QObject::eventFilter(target, event);
            switch (keyEvent->key()){

            case Qt::Key_6:
                move3dFlag=MOVE_XP;
                return true;
            case Qt::Key_4:
                move3dFlag=MOVE_XM;
                return true;
            case Qt::Key_8:
                move3dFlag=MOVE_YP;
                return true;
            case Qt::Key_2:
                move3dFlag=MOVE_YM;
                return true;
            case Qt::Key_9:
                move3dFlag=MOVE_ZP;
                return true;
            case Qt::Key_3:
                move3dFlag=MOVE_ZM;
                return true;
            }
        } else if (event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->isAutoRepeat())return QObject::eventFilter(target, event);
            switch (keyEvent->key()){
                case Qt::Key_6:
                case Qt::Key_4:
                case Qt::Key_8:
                case Qt::Key_2:
                case Qt::Key_9:
                case Qt::Key_3:
                move3dFlag=MOVE_STOP;
                //stopMove();
                return true;
            }
        }

    return QObject::eventFilter(target, event);
}
