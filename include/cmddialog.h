#ifndef CMDDIALOG_H
#define CMDDIALOG_H

#include "gnetraw.h"

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

class CmdDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CmdDialog(QWidget *parent = 0);
    virtual ~CmdDialog();

    QComboBox *comandCombo, *comandCombo2, *portCombo, *portCombo2;
    QLineEdit *dataLineEdit, *dataLineEdit2;
    QPushButton *sendButton;
    QPushButton *cancelButton;

    QVector<Gcpd> getCpd();

signals:

public slots:
};

#endif // CMDDIALOG_H
