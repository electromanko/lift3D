#include "include/joywidget.h"

joywidget::joywidget(QWidget *parent) : QWidget(parent)
{
     QGridLayout *mainLayout = new QGridLayout;

     xpButton = new QPushButton(tr("&x+"));
     xpButton->setFocusPolicy(Qt::NoFocus);


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

     mainLayout->addWidget(xpButton, 2,0);
     mainLayout->addWidget(xmButton, 2,0);
     mainLayout->addWidget(ypButton, 2,0);
     mainLayout->addWidget(ymButton, 2,0);
     mainLayout->addWidget(zpButton, 2,0);
     mainLayout->addWidget(zmButton, 2,0);

     setLayout(mainLayout);
}
