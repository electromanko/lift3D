#include "include/iowidget.h"

#include <QGridLayout>

IOwidget::IOwidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;

    textEdit = new QTextEdit;
    mainLayout->addWidget(textEdit, 0,0);
    setLayout(mainLayout);
}
