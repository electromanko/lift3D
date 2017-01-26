#ifndef JOYWIDGET_H
#define JOYWIDGET_H

#include <QPushButton>
#include <QWidget>


class Joywidget : public QWidget
{
    Q_OBJECT
public:
    explicit Joywidget(QWidget *parent = 0);
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
