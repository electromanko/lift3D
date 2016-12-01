#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glwidget.h"
#include "paramwidget.h"

#include <QMainWindow>


class MainWindow;


class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWidget *centralWidget;
    GlWidget *glwidget;
    ParamWidget *paramwidget;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

};

#endif // MAINWINDOW_H
