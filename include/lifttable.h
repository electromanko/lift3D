#ifndef LIFTTABLE_H
#define LIFTTABLE_H

#include <include/lifter.h>
#include <QAbstractTableModel>

class LiftTable : public QAbstractTableModel
{
    Q_OBJECT

public:

    static const int COL_IP=0;
    static const int COL_GADDR=1;
    static const int COL_GNET=2;
    static const int COL_DEV_TYPE=3;
    static const int COL_HCURR=4;
    static const int COL_PARKED=5;
    static const int COL_SIZE=6;

    explicit LiftTable(Lifter *lifter,QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool insertRows(int position, int rows, const QModelIndex &index);
    bool removeRows(int position, int rows, const QModelIndex &index);
private:
    Lifter *lifter;
    int liftCount;

public slots:
    void addRows(int position, int count);
    void deleteRows(int position, int count);
    void liftUpdate(int index);
};

#endif // LIFTTABLE_H
