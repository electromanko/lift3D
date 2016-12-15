#ifndef PARAMWIDGET_H
#define PARAMWIDGET_H

#include "gnetraw.h"
#include "lifter.h"
#include "lifttable.h"

#include <QTableView>
#include <QPushButton>
#include <QWidget>

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

    bool eventFilter(QObject *target, QEvent *event);
private:
    GnetRaw *gnet;
    Lifter *lifter;
signals:

public slots:
    void upDemand();
    void downDemand();
    void stopMove();
    void stopAll();
    void findLift();
    void park();
};

#endif // PARAMWIDGET_H
