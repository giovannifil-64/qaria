#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QAbstractTableModel>

//#include "model/data.h"
#include "csvdata.h"


class DataModel: public QAbstractTableModel
{
    Q_OBJECT;
private:
    CSVData* m_csvData;

public:
    DataModel(CSVData* csvData, QObject *parent);
    CSVData* getCSVData() const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertNewRow(int row, const QModelIndex &parent = QModelIndex());
    void setCsvData(CSVData *newCsvData);
    void removeRow(int row, const QModelIndex &parent = QModelIndex());

signals:
    void dataEdited();
};

#endif // DATAMODEL_H
