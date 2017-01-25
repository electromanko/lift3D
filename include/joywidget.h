#ifndef JOYWIDGET_H
#define JOYWIDGET_H

#include <QWidget>

class joywidget : public QWidget
{
    Q_OBJECT
public:
    explicit joywidget(QWidget *parent = 0);
    QPushButton *xpButton;
    QPushButton *xmButton;
    QPushButton *ypButton;
    QPushButton *ymButton;
    QPushButton *zpButton;
    QPushButton *zmButton;

signals:

public slots:
};

#endif // JOYWIDGET_H
