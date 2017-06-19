#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QStackedWidget>

class IOProtocolPage : public QWidget
{
    Q_OBJECT
public:
    QRadioButton *udpModeRButton;
    QRadioButton *mqttModeRButton;

    QLineEdit *udpPortLineEdit;
    QLineEdit *mqttHostLineEdit;
    QLineEdit *mqttPortLineEdit;

    IOProtocolPage(QWidget *parent = 0);

    void loadSettings();
    void saveSettings();
    void restoreSettings();
public slots:
    void changeUDP();
    void changeMqtt();
};

class PathsPage : public QWidget
{
public:
    PathsPage(QWidget *parent = 0);
};

class SettingsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SettingsDialog(QWidget *parent = 0);
public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void acceptSettings();
    void rejectSettings();
private:
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;

    IOProtocolPage *protocolPage;
    PathsPage *pathsPage;

    //QPushButton *okButton;
    //QPushButton *cancelButton;

};


#endif // SETTINGSDIALOG_H
