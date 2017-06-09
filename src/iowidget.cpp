#include "include/iowidget.h"

#include <QGridLayout>
#include <QMenu>
#include <QMouseEvent>

class IOQTextEdit :  public QTextEdit
{
public:
    void contextMenuEvent(QContextMenuEvent *event)
    {
        QMenu *menu = createStandardContextMenu();
        QAction* clearAction = menu->addAction(tr("Clear"));//tr("Clear"), clear()
        //...
        QAction* selectedItem= menu->exec(event->globalPos());
        if (selectedItem==clearAction){
            this->clear();
        }
        delete menu;
    }
};

IOwidget::IOwidget(QWidget *parent) : QWidget(parent)
{
    QGridLayout *mainLayout = new QGridLayout;

    textEdit = new IOQTextEdit;
    textEdit->setReadOnly(true);
    mainLayout->addWidget(textEdit, 0,0);
    setLayout(mainLayout);
}

IOwidget::receivedDatagram(QHostAddress ip, GDatagram datagram)
{
    textEdit->setTextColor(Qt::black);
    textEdit->append(QString("-> ")+datagram.toString());
}

IOwidget::sendedDatagram(QHostAddress ip, GDatagram datagram)
{
    textEdit->setTextColor(Qt::blue);
    textEdit->append(QString("<- ")+datagram.toString());
}

