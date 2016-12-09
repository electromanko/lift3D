#ifndef LIFT_H
#define LIFT_H

#include <QObject>

class Lift : public QObject
{
    Q_OBJECT
public:
    const int STATE_ACTUAL = (1<<0);

    explicit Lift(QObject *parent = 0);
    explicit Lift(unsigned int selfAddr,unsigned int  selfNet, QObject *parent = 0);
    unsigned int selfAddr;
    int saState;
    unsigned int selfNet;
    int snState;
    unsigned int heightCurrent;
    int hcState;
    unsigned int heightLink;
    int hlState;

signals:

public slots:
};

#endif // LIFT_H
