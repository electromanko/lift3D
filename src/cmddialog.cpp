#include "include/cmddialog.h"


#include <QGridLayout>

class SelQComboBox :  public QComboBox
{
public:
    void focusInEvent( QFocusEvent* event )
    {
        QComboBox::focusInEvent( event );
        if( !(this->lineEdit()->hasSelectedText()) )
        {
            this->lineEdit()->selectAll();
            //qDebug("Change");
        }
    }
    void changeEvent(QEvent *e){
        //this->lineEdit()->selectAll();
        //e->type();
        //qDebug("Change");


    }
};

CmdDialog::CmdDialog(QWidget *parent) : QDialog(parent)
{

    comandCombo = new QComboBox();
    comandCombo->setEditable(true);
    comandCombo->addItem(QString(""));
    comandCombo->addItem(QString("READ(0)"),QVariant(0));
    comandCombo->addItem(QString("WRITE(1)"),QVariant(1));
    comandCombo->addItem(QString("WRITE_0B(31)"),QVariant(31));
    comandCombo->addItem(QString("WRITE_1B(33)"),QVariant(33));
    comandCombo->lineEdit()->setCursorPosition(0);

    portCombo = new QComboBox();
    portCombo->setEditable(true);
    portCombo->addItem(QString(""));
    portCombo->addItem(QString("POSITION(32)"),QVariant(32));
    portCombo->addItem(QString("DIR_UP(35)"),QVariant(35));
    portCombo->addItem(QString("DIR_DN(36)"),QVariant(36));
    portCombo->addItem(QString("STOP(37)"),QVariant(37));
    portCombo->addItem(QString("PARK(38)"),QVariant(38));


    comandCombo2 = new QComboBox();
    comandCombo2->setModel(comandCombo->model());
    comandCombo2->setEditable(true);

    portCombo2 = new QComboBox();
    portCombo2->setModel(portCombo->model());
    portCombo2->setEditable(true);

    dataLineEdit = new QLineEdit("");
    dataLineEdit->setFixedWidth(60);

    dataLineEdit2 = new QLineEdit("");
    dataLineEdit2->setFixedWidth(60);

    sendButton = new QPushButton(tr("&Send"),this);
    cancelButton = new QPushButton(tr("&Cancel"),this);

    QGridLayout *mainLayout = new QGridLayout;
    QGridLayout *hbLayout = new QGridLayout;
    QGridLayout *htLayout = new QGridLayout;

    htLayout->addWidget(comandCombo, 0,0);
    htLayout->addWidget(portCombo, 0,1);
    htLayout->addWidget(dataLineEdit,0,2);

    htLayout->addWidget(comandCombo2, 1,0);
    htLayout->addWidget(portCombo2, 1,1);
    htLayout->addWidget(dataLineEdit2,1,2);

    hbLayout->addWidget(sendButton, 0,1);
    hbLayout->addWidget(cancelButton, 0,2);

    mainLayout->addLayout(htLayout,0,0);
    mainLayout->addLayout(hbLayout,1,0);
    setLayout(mainLayout);

    //this->dumpObjectTree();

    QObject::connect(sendButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

CmdDialog::~CmdDialog()
{
}

QVector<Gcpd> CmdDialog::getCpd()
{
    QRegExp re("\\d*");
    QVector<Gcpd> v;
    int c,p,d;
    bool validate=true;
    QComboBox* cc[2]={comandCombo,comandCombo2};
    QComboBox* pc[2]={portCombo, portCombo2};
    QLineEdit* dl[2]={dataLineEdit, dataLineEdit2};
    for (int i=0;i<2;i++){
    validate = cc[i]->currentText().length()>0 &&
                pc[i]->currentText().length()>0 &&
                dl[i]->text().length()>0;

    if (cc[i]->currentIndex()!=0)
        c=cc[i]->currentData().toInt();
    else if (re.exactMatch(cc[i]->currentText()))
        c=cc[i]->currentText().toInt();
    else validate=false;

    if (pc[i]->currentIndex()!=0)
        p=pc[i]->currentData().toInt();
    else if (re.exactMatch(pc[i]->currentText()))
        p=pc[i]->currentText().toInt();
    else validate=false;

    if (re.exactMatch(dl[i]->text()))
        d=dl[i]->text().toInt();
    else validate=false;

    if (validate) qDebug() << QString("c%1,p%2,d%3").arg(c).arg(p).arg(d);
    v.append(Gcpd(1,1,1));
    }
    return v;
}
