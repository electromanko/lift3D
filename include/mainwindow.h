#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glwidget.h"
#include "joywidget.h"
#include "controlwidget.h"
#include "liftconfig.h"

#include <QFile>
#include <QMainWindow>


class MainWindow;


class MainWindow : public QMainWindow
{
    Q_OBJECT

    Lifter3d *lifter3D;
    QWidget *centralWidget;
    GlWidget *glwidget;
    ControlWidget *controlwidget;
    Joywidget *joywidget;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool eventFilter(QObject *target, QEvent *event);
    LiftConfig config;
protected:
    #ifndef QT_NO_CONTEXTMENU
        void contextMenuEvent(QContextMenuEvent *event) Q_DECL_OVERRIDE;
    #endif // QT_NO_CONTEXTMENU
private:

    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *helpMenu;

    QAction *actionQuit;
    QAction *actionAbout;

};

#endif // MAINWINDOW_H
