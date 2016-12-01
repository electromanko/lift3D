#include "include/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    /*GlWidget glwidget;
    ui->setupUi(this);
    ui->glStackedWidget->addWidget(glwidget);*/
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
