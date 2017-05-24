#include <QtWidgets>
#include <QLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSplitter>
#include <include/joywidget.h>
#include "include/mainwindow.h"
#include "include/glwidget.h"

#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QFile c("./config.gc");
    if (!c.exists()){
        c.setFileName("../Lift3D/config.gc");
    }
    if (!config.load(c)) {
        QErrorMessage errorMessage;
        errorMessage.showMessage(tr("Error cofig file"));
        errorMessage.exec();
    }
    gnet = new GnetRaw();
    lifter3D = new Lifter3d(gnet, config.limitCubePoint0,config.limitCubePoint1,config.lifterAddr,config.lifterNet,
                            config.lifterDevType,this);
    foreach (lift3DConf conf, config.lift3DList) {
        lifter3D->addLift3d(conf.addr,conf.net,conf.lZero,conf.lEnd,conf.pos);
    }
    centralWidget = new QWidget(this);
    //QHBoxLayout *mainLayout = new QHBoxLayout();



    //QSplitter *hSplitter = new QSplitter(centralWidget);
    //hSplitter->setOrientation(Qt::Horizontal);
    //hSplitter->addWidget(glwidget);
    //hSplitter->addWidget(controlwidget);
    //hSplitter->addWidget(joywidget);

    //mainLayout->addWidget(hSplitter);
     //mainLayout->addWidget(glwidget);
     //mainLayout->addWidget(button1);

    /*centralWidget->setLayout(mainLayout);
    //button1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding) ;
    //centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    centralWidget->resize(400,400);
    setCentralWidget(centralWidget);*/

    createActions();
    createMenus();
    //createDockWindows();
    createSimpleWindows();
    installEventFilter(this);
}

MainWindow::~MainWindow()
{
    //delete glwidget;
    delete gnet;
}

void MainWindow::createActions(){
    actionQuit = new QAction(tr("&Quit"), this);
    actionQuit->setShortcuts(QKeySequence::Quit);
    actionQuit->setStatusTip(tr("Quit from app"));
    connect(actionQuit, &QAction::triggered, this, &MainWindow::close);

    actionAbout = new QAction(tr("&About"), this);
    actionAbout->setShortcuts(QKeySequence::Cancel);
    actionAbout->setStatusTip(tr("Quit from app"));
}

void MainWindow::createMenus(){
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addSeparator();
        fileMenu->addAction(actionQuit);

        viewMenu = menuBar()->addMenu(tr("&View"));

        fileMenu = menuBar()->addMenu(tr("&Help"));
        fileMenu->addSeparator();
        fileMenu->addAction(actionAbout);

}

void MainWindow::createDockWindows(){
    //glwidget =new GlWidget(this);

    controlwidget = new ControlWidget(lifter3D, this);
    joywidget = new Joywidget(lifter3D, config.iconSize, config.move3dDeltaPosition, config.move3dTime, this);
    iowidget = new IOwidget(this);
    connect(gnet, SIGNAL(received(QHostAddress, GDatagram)), iowidget, SLOT(receivedDatagram(QHostAddress, GDatagram)));
    connect(gnet, SIGNAL(sended(QHostAddress, GDatagram)), iowidget, SLOT(sendedDatagram(QHostAddress, GDatagram)));

    QDockWidget *dock = new QDockWidget(tr("Control"), this);
    //dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(controlwidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("Joystick"), this);
    //dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(joywidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget(tr("IO"), this);
    //dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(iowidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());
}

void MainWindow::createSimpleWindows(){
    //glwidget =new GlWidget(this);

    controlwidget = new ControlWidget(lifter3D, this);
    //joywidget = new Joywidget(lifter3D, config.iconSize, config.move3dDeltaPosition, config.move3dTime, this);
    //iowidget = new IOwidget(this);
    //connect(gnet, SIGNAL(received(QHostAddress, GDatagram)), iowidget, SLOT(receivedDatagram(QHostAddress, GDatagram)));
    //connect(gnet, SIGNAL(sended(QHostAddress, GDatagram)), iowidget, SLOT(sendedDatagram(QHostAddress, GDatagram)));

    /*QDockWidget *dock = new QDockWidget(tr("Control"), this);
    //dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(controlwidget);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());*/
    QHBoxLayout *mainLayout = new QHBoxLayout();

    QSplitter *hSplitter = new QSplitter(centralWidget);
    hSplitter->setOrientation(Qt::Horizontal);
    //hSplitter->addWidget(glwidget);
    hSplitter->addWidget(controlwidget);
    //hSplitter->addWidget(joywidget);

    mainLayout->addWidget(hSplitter);


    centralWidget->setLayout(mainLayout);

    setCentralWidget(centralWidget);
    //centralWidget->resize(800,600);
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(actionQuit);
    menu.addAction(actionAbout);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->isAutoRepeat())return QObject::eventFilter(target, event);
            switch (keyEvent->key()){
            case Qt::Key_W:
                controlwidget->upDemand();
                return true;
            case Qt::Key_S:
                controlwidget->downDemand();
                return true;
            case Qt::Key_P:
                controlwidget->park();
                return true;
            case Qt::Key_F:
                controlwidget->findLift();
                return true;
            case Qt::Key_Space:
                controlwidget->stopAll();
                return true;
            case Qt::Key_G:
            case Qt::Key_Return:
                controlwidget->goTo();
                return true;
            case Qt::Key_C:
                controlwidget->sendCmd();
                return true;
            /*case Qt::Key_6:
                joywidget->move3dFlag=Joywidget::MOVE_XP;
                qDebug("key6");
                return true;
            case Qt::Key_4:
                joywidget->move3dFlag=Joywidget::MOVE_XM;
                return true;
            case Qt::Key_8:
                joywidget->move3dFlag=Joywidget::MOVE_YP;
                return true;
            case Qt::Key_2:
                joywidget->move3dFlag=Joywidget::MOVE_YM;
                return true;
            case Qt::Key_9:
                joywidget->move3dFlag=Joywidget::MOVE_ZP;
                return true;
            case Qt::Key_3:
                joywidget->move3dFlag=Joywidget::MOVE_ZM;
                return true;
                */

            }
        } else if (event->type() == QEvent::KeyRelease) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->isAutoRepeat())return QObject::eventFilter(target, event);
            switch (keyEvent->key()){
            case Qt::Key_W:
            case Qt::Key_S:
            /*case Qt::Key_6:
            case Qt::Key_4:
            case Qt::Key_8:
            case Qt::Key_2:
            case Qt::Key_9:
            case Qt::Key_3:*/
                //joywidget->move3dFlag=Joywidget::MOVE_STOP;
                controlwidget->stopMove();
                return true;
            }
        }

    return QObject::eventFilter(target, event);
}

