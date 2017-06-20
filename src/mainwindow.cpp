#include <iostream>
#include <QtWidgets>
#include <QLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSplitter>
#include <include/joywidget.h>
#include <include/settingsdialog.h>
#include "include/mainwindow.h"
#include "include/glwidget.h"

#include "ui_mainwindow.h"
//extern Q_CORE_EXPORT int qt_ntfs_permission_lookup;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QSettings settings("gella", "Lift3D");
    QString protocolType = settings.value("connections/type","udp").toString();

    /*QIcon icon(":/icon/WinchLogo.ico");
    setWindowIcon(icon);*/

    //mqttExample = new IOmqtt(QHostAddress("192.168.24.142"),1883);
    //mqttExample = new IOmqtt(QString("liftmaster"),1883);

    /*mqttExample = new IOmqtt();
    mqttExample->setHostName(QString("liftmaster"));

    //mqttExample.setHostName("liftmaster");
    //mqttExample.setHost(QHostAddress("192.168.24.142"));
    mqttExample->connectToHost();*/

    QFile c("config.gc");

    if (!c.exists()) {
        QErrorMessage errorMessage;
        QFile dc(":/defaultConfig.gc");
        //qDebug()<<dc.open(QFile::ReadOnly);
        //qDebug()<<dc.errorString();
        //qt_ntfs_permission_lookup++;
        if (!dc.copy("config.gc")){
            errorMessage.showMessage(tr("False write default cofig file: ")+dc.errorString()+tr(". Load defaul file"));
            errorMessage.exec();
            c.setFileName(dc.fileName());
        } else {
            errorMessage.showMessage(tr("Create default cofig file"));
            errorMessage.exec();
        }
    }
    if (!config.load(c)){
        QErrorMessage errorMessage;
        errorMessage.showMessage(tr("Error parce cofig file"));
        errorMessage.exec();
    }
    gnet = new GnetRaw();
    if (!protocolType.compare("udp")) gnet->connect_udp(settings.value("connections/udp/port","udp").toInt());
    else if (!protocolType.compare("mqtt")) gnet->connect_mqtt(settings.value("connections/mqtt/hostname","liftmaster").toString(), settings.value("connections/mqtt/port","1883").toInt());

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
    statusBar()->showMessage(QString("self IP: ")+ gnet->getSelfAddress().at(0).toString());
    installEventFilter(this);
    controlwidget->findLift();
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
    //actionAbout->setShortcuts(QKeySequence::Cancel);
    actionAbout->setStatusTip(tr("About app"));
    //createAboutMessageBox();
    connect(actionAbout, SIGNAL(triggered()), this, SLOT(createAboutMessageBox()));

    actionSettings = new QAction(tr("&Settings"), this);
    actionSettings->setStatusTip(tr("Settings"));
    connect(actionSettings, SIGNAL(triggered()), this, SLOT(createSettingsDialog()));
}

void MainWindow::createMenus(){
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addSeparator();
        fileMenu->addAction(actionQuit);

        viewMenu = menuBar()->addMenu(tr("&View"));

        toolsMenu = menuBar()->addMenu(tr("&Tools"));
        toolsMenu->addAction(actionSettings);

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
    iowidget = new IOwidget(this);
    connect(gnet, SIGNAL(received(QHostAddress, GDatagram)), iowidget, SLOT(receivedDatagram(QHostAddress, GDatagram)));
    connect(gnet, SIGNAL(sended(QHostAddress, GDatagram)), iowidget, SLOT(sendedDatagram(QHostAddress, GDatagram)));

    dockIOwidget = new QDockWidget(tr("IO"), this);
    //dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockIOwidget->setWidget(iowidget);
    addDockWidget(Qt::RightDockWidgetArea, dockIOwidget);
    //dock->hide();
    viewMenu->addAction(dockIOwidget->toggleViewAction());

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
    readSettings();

}

void MainWindow::createAboutMessageBox(){
    QMessageBox::about(this, tr("About"), tr("Winch control program."));
    //QMessageBox::aboutQt(this, tr("About"));

}

void MainWindow::createSettingsDialog(){
    QSettings settings("gella", "Lift3D");
    SettingsDialog settingsDialog(this);

    if (settingsDialog.exec() == QDialog::Accepted ) {
            QString protocolType = settings.value("connections/type","udp").toString();
            gnet->disconnect();
            if (!protocolType.compare("mqtt")){ //gnet->getConnectionType()==GnetRaw::UDP_CONNECTION &&
                gnet->connect_mqtt(settings.value("connections/mqtt/hostname","liftmaster").toString(), settings.value("connections/mqtt/port","1883").toInt());
            }
            else if (!protocolType.compare("udp")){ //gnet->getConnectionType()==GnetRaw::MQTT_CONNECTION &&
                gnet->disconnect();
                gnet->connect_udp(settings.value("connections/udp/port","udp").toInt());
            }
            controlwidget->findLift();
       }
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(actionQuit);
    //menu.addAction(actionAbout);
    menu.exec(event->globalPos());
}
#endif // QT_NO_CONTEXTMENU

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    //qDebug("EventFilter type: %d", event->type());
        if (event->type() == QEvent::ShortcutOverride ) {//QEvent::KeyPress || event->type() == QEvent::KeyPress
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
                if (keyEvent->modifiers() & Qt::ControlModifier)controlwidget->goToRaw();
                    else controlwidget->goTo();
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
                joywidget->move3dFlag=Joywsidget::MOVE_YP;
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

void MainWindow::closeEvent(QCloseEvent *event)
  {
      QSettings settings("gella", "Lift3D");
      settings.setValue("geometry", saveGeometry());
      settings.setValue("windowState", saveState());
      settings.setValue("dockIOwidget/hidden", dockIOwidget->isHidden());
      QMainWindow::closeEvent(event);
  }

void MainWindow::readSettings()
{
    QSettings settings("gella", "Lift3D");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
    if (settings.value("dockIOwidget/hidden", true).toBool())dockIOwidget->hide();
    else dockIOwidget->show();
}
