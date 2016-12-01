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
