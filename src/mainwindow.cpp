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
    QPushButton *button1 = new QPushButton("One");

    glwidget =new GlWidget();
    QSplitter *hSplitter = new QSplitter(centralWidget);
    hSplitter->setOrientation(Qt::Horizontal);
    hSplitter->addWidget(glwidget);
    hSplitter->addWidget(button1);

    mainLayout->addWidget(hSplitter);
     //mainLayout->addWidget(glwidget);
     //mainLayout->addWidget(button1);

    centralWidget->setLayout(mainLayout);
    //button1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding) ;
    //centralWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    centralWidget->resize(400,400);
    setCentralWidget(centralWidget);


}

MainWindow::~MainWindow()
{
    delete glwidget;
}
