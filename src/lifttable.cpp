#include "include/lifttable.h"

#include <QBrush>
#include <QFont>



LiftTable::LiftTable(Lifter *lifter, QObject *parent)
    : QAbstractTableModel(parent)
{
    this->lifter=lifter;
}

QVariant LiftTable::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {
            case 0:
                return QString("Addr");
            case 1:
                return QString("Net");
            case 2:
                return QString("DevType");
            }
        }
    }
    return QVariant();

}

int LiftTable::rowCount(const QModelIndex &parent) const
{
    /*if (!parent.isValid())
        return 0;*/

    return lifter->getLiftCount();

}

int LiftTable::columnCount(const QModelIndex &parent) const
{
    /*if (!parent.isValid())
        return 0;

    return lifter->getLiftCount();*/
    return 3;
}

QVariant LiftTable::data(const QModelIndex &index, int role) const
{
    /*if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();*/

        int row = index.row();
        int col = index.column();
        Lift* lift = lifter->getLift(row);

        switch(role){
        case Qt::DisplayRole:

            if (lift!= NULL){
                if (col == 0) return QString("%1").arg(lift->addr);
                if (col == 1) return QString("%1").arg(lift->net);
                if (col == 2) return QString("%1").arg(lift->devType);
            }
            break;
        case Qt::FontRole:
            /*if (row == 0 && col == 0) //change font only for cell(0,0)
            {
                QFont boldFont;
                boldFont.setBold(true);
                return boldFont;
            }*/
            break;
        case Qt::BackgroundRole:

            /*if (row == 1 && col == 2)  //change background only for cell(1,2)
            {
                QBrush redBackground(Qt::red);
                return redBackground;
            }*/
            break;
        case Qt::TextAlignmentRole:

            /*if (row == 1 && col == 1) //change text alignment only for cell(1,1)
            {
                return Qt::AlignRight + Qt::AlignVCenter;
            }*/
            break;
        case Qt::CheckStateRole:

           /* if (row == 1 && col == 0) //add a checkbox to cell(1,0)
            {
                return Qt::Checked;
            }*/
            break;
        }
        return QVariant();
}

void LiftTable::update()
{
    QModelIndex top = createIndex(0,0);

    //emit a signal to make the view reread identified data
    //emit rowsInserted(top,0, 2);
}
