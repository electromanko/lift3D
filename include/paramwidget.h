#ifndef PARAMWIDGET_H
#define PARAMWIDGET_H

#include "gnetraw.h"

#include <QPushButton>
#include <QWidget>

class ParamWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ParamWidget(QWidget *parent = 0);
    QPushButton *upButton;
    QPushButton *downButton;

private:
    GnetRaw *gnet;
signals:

public slots:
    void upDemand();
    void downDemand();
    void stopMove();
};

#endif // PARAMWIDGET_H
