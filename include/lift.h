#ifndef LIFT_H
#define LIFT_H

#include <QObject>

class Lift : public QObject
{
    Q_OBJECT
public:
    const unsigned char  STATE_ACTUAL = (1<<0);
    const unsigned char  STATE_UPDATE = (1<<1);

    explicit Lift(QObject *parent =0);
    explicit Lift(unsigned int selfAddr=0,unsigned int  selfNet=0, unsigned int devType=0, QObject *parent = 0);
    unsigned int addr;
    unsigned char saState;

    unsigned int net;
    unsigned char snState;

    unsigned int devType;
    unsigned char dtState;

    unsigned int heightCurrent;
    unsigned char hcState;

    unsigned int heightLink;
    unsigned char hlState;

signals:

public slots:
};

#endif // LIFT_H
