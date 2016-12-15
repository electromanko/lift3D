#include "include/lifttable.h"

#include <QBrush>
#include <QFont>



LiftTable::LiftTable(Lifter *lifter, QObject *parent)
    : QAbstractTableModel(parent)
{
    this->lifter=lifter;
    this->liftCount= lifter->getLiftCount();
}

QVariant LiftTable::headerData(int section, Qt::Orientation orientation, int role) const
{

    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal) {
            switch (section)
            {


            case COL_IP:
                return QString("IP");
            case COL_GADDR:
                return QString("Addr");
            case COL_GNET:
                return QString("Net");
            case COL_DEV_TYPE:
                return QString("DevType");
            case COL_HCURR:
                return QString("Hc");
            case COL_PARKED:
                return QString("Parked");
            }
        }
    }
    return QVariant();

}

int LiftTable::rowCount(const QModelIndex &parent) const
{
    /*if (!parent.isValid())
        return 0;*/

    return liftCount;

}

int LiftTable::columnCount(const QModelIndex &parent) const
{
    /*if (!parent.isValid())
        return 0;

    return lifter->getLiftCount();*/
    return COL_SIZE;
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

                if (col == COL_IP) return QString("%1").arg(lift->ip.toString());
                if (col == COL_GADDR) return QString("%1").arg(lift->addr);
                if (col == COL_GNET) return QString("%1").arg(lift->net);
                if (col == COL_DEV_TYPE) return QString("%1").arg(lift->devType);
                if (col == COL_HCURR) return QString("%1").arg(lift->heightCurrent);
                if (col == COL_PARKED) return  lift->padked? QString("Parked"):QString("None");
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

            if ((col==COL_HCURR && !(lift->hcState&Lift::STATE_ACTUAL)) || (col==COL_PARKED && !(lift->pkState&Lift::STATE_ACTUAL))) {
                QBrush redBackground(Qt::lightGray);
                return redBackground;
            }
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

bool LiftTable::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    if (rows<=0) return false;
    beginInsertRows(QModelIndex(), position, position + rows - 1);

   /* for (int row = 0; row < rows; ++row) {
        //QPair<QString, QString> pair(" ", " ");
        //listOfPairs.insert(position, pair);
        liftCount=
    }*/
    liftCount+=rows;
    endInsertRows();
    return true;
}

bool LiftTable::removeRows(int position, int rows, const QModelIndex &index){
    Q_UNUSED(index);
    if (rows<=0) return false;
    beginRemoveRows(QModelIndex(), position, position + rows - 1);
    liftCount-=rows;
    endRemoveRows();
}

void LiftTable::addRows(int position, int rows)
{
    insertRows(position,rows,QModelIndex());
}

void LiftTable::deleteRows(int position, int rows)
{
    removeRows(position,rows,QModelIndex());
}

void LiftTable::liftUpdate(int index)
{
    QModelIndex idxL = this->index(index,0);
    QModelIndex idxR = this->index(index,COL_SIZE-1);
    emit dataChanged(idxL,idxR);
}

