#ifndef IOWIDGET_H
#define IOWIDGET_H

#include <QTextEdit>
#include <QWidget>

class IOwidget : public QWidget
{
    Q_OBJECT
public:
    explicit IOwidget(QWidget *parent = 0);
    QTextEdit* textEdit;
signals:

public slots:
};

#endif // IOWIDGET_H
