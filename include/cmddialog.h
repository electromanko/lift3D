#ifndef CMDDIALOG_H
#define CMDDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QPushButton>

class CmdDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CmdDialog(QWidget *parent = 0);
    virtual ~CmdDialog();

    QPushButton *sendButton;
    QPushButton *cancelButton;

signals:

public slots:
};

#endif // CMDDIALOG_H
