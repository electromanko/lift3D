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

class ParamWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParamWidget(QWidget *parent = 0);
    virtual ~ParamWidget();
    QTableView  *liftTableView;
    LiftTable *liftTableModel;
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *findButton;
    QPushButton *parkButton;
    QSlider *heightSlider;
    QTimer *moveTimer;

    bool timerStartFlag;

    bool eventFilter(QObject *target, QEvent *event);
private:
    GnetRaw *gnet;
    Lifter3d *lifter;
    void adjustLiftTableSize();
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
    void moveTimerTimeout();
};

#endif // PARAMWIDGET_H
