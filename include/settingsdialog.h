#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QStackedWidget>

class IOProtocolPage : public QWidget
{
public:
    IOProtocolPage(QWidget *parent = 0);
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
private:
    QListWidget *contentsWidget;
    QStackedWidget *pagesWidget;

    //QPushButton *okButton;
    //QPushButton *cancelButton;

};


#endif // SETTINGSDIALOG_H
