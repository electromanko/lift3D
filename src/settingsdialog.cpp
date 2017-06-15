#include "include/settingsdialog.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QRadioButton>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    contentsWidget = new QListWidget;
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    //contentsWidget->setSpacing(12);

    QListWidgetItem *IOProtocolButton = new QListWidgetItem(contentsWidget);
    IOProtocolButton->setText(tr("Protocol"));
    IOProtocolButton->setTextAlignment(Qt::AlignHCenter);
    //IOProtocolButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *PathButton = new QListWidgetItem(contentsWidget);
    PathButton->setText(tr("Paths"));
    PathButton->setTextAlignment(Qt::AlignHCenter);
    //IOProtocolButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(new IOProtocolPage);
    pagesWidget->addWidget(new PathsPage);


    contentsWidget->setCurrentRow(0);

    QPushButton *okButton = new QPushButton(tr("&Ok"));
    QPushButton *cancelButton = new QPushButton(tr("&Cancel"));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    horizontalLayout->addWidget(pagesWidget, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Settings"));

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(contentsWidget, &QListWidget::currentItemChanged, this, &SettingsDialog::changePage);
}

void SettingsDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}



IOProtocolPage::IOProtocolPage(QWidget *parent) : QWidget(parent)
{
    //QPushButton *okButton = new QPushButton(tr("&Ok"));
    QRadioButton *udpModeRButton = new QRadioButton(tr("UDP"), this);
    QRadioButton *mqttModeRButton = new QRadioButton(tr("mqtt"), this);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(udpModeRButton);
    mainLayout->addWidget(mqttModeRButton);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

}



PathsPage::PathsPage(QWidget *parent) : QWidget(parent)
{
    //QPushButton *okButton = new QPushButton(tr("&Ok"));
    QLineEdit *configFilePath = new QLineEdit();
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configFilePath);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

}
