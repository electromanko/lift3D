#include "include/cmddialog.h"

#include <QGridLayout>

CmdDialog::CmdDialog(QWidget *parent) : QDialog(parent)
{
    sendButton = new QPushButton(tr("&Send"));
    cancelButton = new QPushButton(tr("&Cancel"));
    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->addWidget(sendButton, 1,0);
    mainLayout->addWidget(cancelButton, 1,1);
    setLayout(mainLayout);
}

CmdDialog::~CmdDialog()
{
    delete sendButton;
}
