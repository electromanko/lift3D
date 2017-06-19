#include "include/settingsdialog.h"

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSettings>
#include <QTextEdit>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    protocolPage = new IOProtocolPage();
    pathsPage = new PathsPage();

    contentsWidget = new QListWidget;
    contentsWidget->setMovement(QListView::Static);
    contentsWidget->setMaximumWidth(128);
    //contentsWidget->setSpacing(12);

    QListWidgetItem *IOProtocolButton = new QListWidgetItem(contentsWidget);
    IOProtocolButton->setText(tr("Connetion"));
    IOProtocolButton->setTextAlignment(Qt::AlignHCenter);
    //IOProtocolButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *PathButton = new QListWidgetItem(contentsWidget);
    PathButton->setText(tr("Paths"));
    PathButton->setTextAlignment(Qt::AlignHCenter);
    //IOProtocolButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    pagesWidget = new QStackedWidget;
    pagesWidget->addWidget(protocolPage);
    pagesWidget->addWidget(pathsPage);


    contentsWidget->setCurrentRow(0);

    QPushButton *okButton = new QPushButton(tr("&Ok"));
    QPushButton *cancelButton = new QPushButton(tr("&Cancel"));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(contentsWidget);
    //QGroupBox *groupBox = new QGroupBox();//tr("Settings")
    //QHBoxLayout *hBoxLayout = new QHBoxLayout;
    //hBoxLayout->addWidget(pagesWidget);
    //groupBox->setLayout(hBoxLayout);
    //horizontalLayout->addWidget(groupBox, 1);
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

    connect(okButton, SIGNAL(clicked()), this, SLOT(acceptSettings()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(rejectSettings()));
    connect(contentsWidget, &QListWidget::currentItemChanged, this, &SettingsDialog::changePage);

}

void SettingsDialog::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    pagesWidget->setCurrentIndex(contentsWidget->row(current));
}

void SettingsDialog::acceptSettings()
{
    protocolPage->saveSettings();
    accept();
}

void SettingsDialog::rejectSettings()
{
    reject();
}



IOProtocolPage::IOProtocolPage(QWidget *parent) : QWidget(parent)
{
    //QPushButton *okButton = new QPushButton(tr("&Ok"));

    udpModeRButton = new QRadioButton(tr("UDP"), this);
    mqttModeRButton = new QRadioButton(tr("mqtt"), this);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *boxLayout = new QVBoxLayout;
    QGroupBox *groupBox = new QGroupBox(tr("Protocol"));//tr("Settings")

    //QLabel *label = new QLabel(tr("Protocol"),this);
    //label->setStyleSheet("font-weight: bold");
    //mainLayout->addWidget(label);
    mainLayout->addWidget(udpModeRButton);

    QHBoxLayout *hBoxLayout = new QHBoxLayout;
    QLabel *label = new QLabel(tr("Port "),this);
    udpPortLineEdit = new QLineEdit(this);
    udpPortLineEdit->setFixedWidth(50);
    hBoxLayout->addSpacing(20);
    hBoxLayout->addWidget(label);
    hBoxLayout->addWidget(udpPortLineEdit);
    hBoxLayout->addStretch(1);
    mainLayout->addLayout(hBoxLayout);

    mainLayout->addWidget(mqttModeRButton);
    hBoxLayout = new QHBoxLayout;
    label = new QLabel(tr("Hostname "),this);
    mqttHostLineEdit = new QLineEdit(this);
    mqttHostLineEdit->setFixedWidth(200);
    hBoxLayout->addSpacing(20);
    hBoxLayout->addWidget(label);
    hBoxLayout->addWidget(mqttHostLineEdit);
    hBoxLayout->addStretch(1);
    mainLayout->addLayout(hBoxLayout);

    hBoxLayout = new QHBoxLayout;
    label = new QLabel(tr("Port "),this);
    mqttPortLineEdit = new QLineEdit(this);
    mqttPortLineEdit->setFixedWidth(50);
    hBoxLayout->addSpacing(20);
    hBoxLayout->addWidget(label);
    hBoxLayout->addWidget(mqttPortLineEdit);
    hBoxLayout->addStretch(1);
    mainLayout->addLayout(hBoxLayout);

    mainLayout->addStretch(1);
    groupBox->setLayout(mainLayout);
    boxLayout->addWidget(groupBox);
    setLayout(boxLayout);
    connect(udpModeRButton,SIGNAL(clicked(bool)),this,SLOT(changeUDP()));
    connect(mqttModeRButton,SIGNAL(clicked(bool)),this,SLOT(changeMqtt()));
    loadSettings();
}

void IOProtocolPage::loadSettings()
{
    QSettings settings("gella", "Lift3D");
    QString protocolType = settings.value("connections/type","udp").toString();
    if (!protocolType.compare("udp")) changeUDP();
    else if (!protocolType.compare("mqtt")) changeMqtt();
    else {};
    mqttPortLineEdit->setText(settings.value("connections/mqtt/port", 1883).toString());
    mqttHostLineEdit->setText(settings.value("connections/mqtt/hostname", "liftmaster").toString());
    udpPortLineEdit->setText(settings.value("connections/udp/port", 7777).toString());
}

void IOProtocolPage::saveSettings()
{
    QSettings settings("gella", "Lift3D");
    if (udpModeRButton->isChecked()) settings.setValue("connections/type","udp");
    else if (mqttModeRButton)settings.setValue("connections/type","mqtt");
    else{};
    settings.setValue("connections/mqtt/port",mqttPortLineEdit->text().toInt());
    settings.setValue("connections/mqtt/hostname",mqttHostLineEdit->text());
    settings.setValue("connections/udp/port", udpPortLineEdit->text().toInt());
}

void IOProtocolPage::restoreSettings()
{
    QSettings settings("gella", "Lift3D");

    settings.remove("connections/type");
    settings.remove("connections/mqtt/port");
    settings.remove("connections/mqtt/hostname");
    settings.remove("connections/udp/port");
    loadSettings();
}

void IOProtocolPage::changeUDP()
{
    udpModeRButton->setChecked(true);
    udpPortLineEdit->setEnabled(true);
    mqttPortLineEdit->setEnabled(false);
    mqttHostLineEdit->setEnabled(false);
}

void IOProtocolPage::changeMqtt()
{
    mqttModeRButton->setChecked(true);
    udpPortLineEdit->setEnabled(false);
    mqttPortLineEdit->setEnabled(true);
    mqttHostLineEdit->setEnabled(true);
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
