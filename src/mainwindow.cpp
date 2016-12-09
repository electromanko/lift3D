#include <QtWidgets>
#include <QLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSplitter>
#include "include/mainwindow.h"
#include "include/glwidget.h"

#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout();

    glwidget =new GlWidget();
    paramwidget = new ParamWidget();
    QSplitter *hSplitter = new QSplitter(centralWidget);
    hSplitter->setOrientation(Qt::Horizontal);
    hSplitter->addWidget(glwidget);
    hSplitter->addWidget(paramwidget);

    mainLayout->addWidget(hSplitter);
     //mainLayout->addWidget(glwidget);
     //mainLayout->addWidget(button1);

    centralWidget->setLayout(mainLayout);
    //button1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding) ;
    //centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    centralWidget->resize(400,400);
    setCentralWidget(centralWidget);

    createActions();
    createMenus();

}

MainWindow::~MainWindow()
{
    delete glwidget;
}

void MainWindow::createActions(){
    actionQuit = new QAction(tr("&Quit"), this);
    actionQuit->setShortcuts(QKeySequence::Quit);
    actionQuit->setStatusTip(tr("Quit from app"));
    //connect(quitAction, &QAction::triggered, this, &MainWindow::newFile);

    actionAbout = new QAction(tr("&About"), this);
    actionAbout->setShortcuts(QKeySequence::Cancel);
    actionAbout->setStatusTip(tr("Quit from app"));
}

void MainWindow::createMenus(){
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addSeparator();
        fileMenu->addAction(actionQuit);

        fileMenu = menuBar()->addMenu(tr("&Help"));
        fileMenu->addSeparator();
        fileMenu->addAction(actionAbout);

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
