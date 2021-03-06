#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glwidget.h"
#include "joywidget.h"
#include "controlwidget.h"
#include "liftconfig.h"
#include "iowidget.h"

#include <QFile>
#include <QMainWindow>

#include <include/iomqtt.h>


class MainWindow;


class MainWindow : public QMainWindow
{
    Q_OBJECT

    GnetRaw *gnet;
    Lifter3d *lifter3D;
    QWidget *centralWidget;
    GlWidget *glwidget;
    ControlWidget *controlwidget;
    Joywidget *joywidget;
    IOwidget *iowidget;
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

    IOmqtt *mqttExample;

    void createActions();
    void createMenus();
    void createDockWindows();
    void createSimpleWindows();


    void closeEvent(QCloseEvent *event);
    void readSettings();

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *toolsMenu;
    QMenu *helpMenu;

    QAction *actionQuit;
    QAction *actionAbout;
    QAction *actionSettings;

    QDockWidget *dockIOwidget;
public slots:
    void createAboutMessageBox();
    void createSettingsDialog();

};

#endif // MAINWINDOW_H
