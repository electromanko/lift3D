#ifndef PARAMWIDGET_H
#define PARAMWIDGET_H

#include "gnetraw.h"
#include "lifter.h"

#include <QPushButton>
#include <QWidget>

class ParamWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParamWidget(QWidget *parent = 0);
    virtual ~ParamWidget();
    QPushButton *upButton;
    QPushButton *downButton;
    QPushButton *findButton;

private:
    GnetRaw *gnet;
    Lifter *lifter;
signals:

public slots:
    void upDemand();
    void downDemand();
    void stopMove();
    void findLift();
};

#endif // PARAMWIDGET_H
