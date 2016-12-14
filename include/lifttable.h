#ifndef LIFTTABLE_H
#define LIFTTABLE_H

#include <include/lifter.h>
#include <QAbstractTableModel>

class LiftTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit LiftTable(Lifter *lifter,QObject *parent = 0);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool insertRows(int position, int rows, const QModelIndex &index);
    void update();
private:
    Lifter *lifter;
};

#endif // LIFTTABLE_H
