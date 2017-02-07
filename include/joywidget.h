#ifndef JOYWIDGET_H
#define JOYWIDGET_H

#include "lifter3d.h"

#include <QEvent>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QWidget>


class Joywidget : public QWidget
{
    Q_OBJECT
public:
    explicit Joywidget(Lifter3d *lifter,int iconSize=64, int move3dDeltaPosition=5, int move3dTime=100, QWidget *parent = 0);
    int move3dDeltaPosition;
    int move3dTime;
    enum {MOVE_STOP=0,MOVE_XP,MOVE_XM,MOVE_YP,MOVE_YM,MOVE_ZP,MOVE_ZM,MOVE_GOTO} move3dFlag;

    QVector3D posCursor3d;
    int iconSize;
    QPushButton *xpButton;
    QPushButton *xmButton;
    QPushButton *ypButton;
    QPushButton *ymButton;
    QPushButton *zpButton;
    QPushButton *zmButton;
    QPushButton *stopButton;
    QPushButton *parkButton;
    QPushButton *gotoButton;
    QLabel *coordLabel;
    Lifter3d *lifter3d;
    QTimer *moveTimer;
    bool eventFilter(QObject *target, QEvent *event);
private:

    void cursorSetup();

signals:

public slots:
    void moveTimerTimeout();
    void xp();
    void xm();
    void yp();
    void ym();
    void zp();
    void zm();
    void stop();
    void park();
    void go();
};

#endif // JOYWIDGET_H
