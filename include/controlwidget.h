#ifndef PARAMWIDGET_H
#define PARAMWIDGET_H

#include "gnetraw.h"
//#include "lifter.h"
#include "lifter3d.h"
#include "lifttable.h"

#include <QTableView>
#include <QPushButton>
#include <QWidget>
#include <QTimer>
#include <QLabel>

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    const int move3DdeltaPosition=5;
    const int move3DTime=100;

    enum {MOVE_STOP=0,MOVE_XP,MOVE_XM,MOVE_YP,MOVE_YM,MOVE_ZP,MOVE_ZM,MOVE_GOTO} move3DFlag;

    explicit ControlWidget(Lifter *lifter, QWidget *parent = 0);
    virtual ~ControlWidget();
    QTableView  *liftTableView;
    LiftTable *liftTableModel;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *findButton;
    QPushButton *parkButton;
    QSlider *heightSlider;
    QTimer *moveTimer;

    bool timerStartFlag;

    //bool eventFilter(QObject *target, QEvent *event);

    /*QLabel *xLabel;
    QLabel *yLabel;
    QLabel *zLabel;*/

private:
    GnetRaw *gnet;
    Lifter *lifter;
    void adjustLiftTableSize();
    QVector3D posCursor3d;

signals:

public slots:
    void upDemand();
    void downDemand();
    void stopMove();
    void stopAll();
    void findLift();
    void park();
    void goTo();
    void sendCmd();
    void goSlider(int value);
    //void moveTimerTimeout();
};

#endif // PARAMWIDGET_H
