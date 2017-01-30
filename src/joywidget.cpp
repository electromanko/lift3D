#include "include/joywidget.h"

#include <QGridLayout>

Joywidget::Joywidget(QWidget *parent) : QWidget(parent)
{
     QGridLayout *mainLayout = new QGridLayout;



     xpButton = new QPushButton(tr("&x+"));
     xpButton->setFocusPolicy(Qt::NoFocus);
     xpButton->setGeometry(QRect(0,0,10,10));


     xmButton = new QPushButton(tr("&x-"));
     xmButton->setFocusPolicy(Qt::NoFocus);

     ypButton = new QPushButton(tr("&y+"));
     ypButton->setFocusPolicy(Qt::NoFocus);

     ymButton = new QPushButton(tr("&y-"));
     ymButton->setFocusPolicy(Qt::NoFocus);

     zpButton = new QPushButton(tr("&z+"));
     zpButton->setFocusPolicy(Qt::NoFocus);

     zmButton = new QPushButton(tr("&z-"));
     zmButton->setFocusPolicy(Qt::NoFocus);

     mainLayout->addWidget(xpButton, 1,2);
     mainLayout->addWidget(xmButton, 1,0);
     mainLayout->addWidget(ypButton, 0,1);
     mainLayout->addWidget(ymButton, 2,1);
     mainLayout->addWidget(zpButton, 0,2);
     mainLayout->addWidget(zmButton, 2,2);


     setLayout(mainLayout);
}
