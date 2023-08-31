#include "datamodel.h"

DataModel::DataModel(CSVData* csvData, QObject *parent): QAbstractTableModel(parent), m_csvData(csvData)
{
}

/**
 * @brief this function returns the total row(s) from a given entity
 * @return returns the number of row(s) found
 */
int DataModel::rowCount(const QModelIndex& /*parent*/) const
{
    return m_csvData -> rowCount();
}

/**
 * @brief this function returns the total column(s) from a given entity
 * @return returns the number of column(s) found
 */
int DataModel::columnCount(const QModelIndex& /*parent*/) const
{
    return m_csvData -> columnCount();
}

/**
 * @brief Returns the data stored at the given model index for the specified role.
 * @param index The model index of the data to be returned.
 * @param role The role for which the data should be returned.
 * @return The data stored at the given model index for the specified role, or an
 *         invalid QVariant if the index is invalid or the role is not supported.
 */
QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole){
        return m_csvData -> get(index.row(), index.column());
    }

    return QVariant();
}

/**
 * @brief Returns the header data for the given section and orientation.
 * @param section The section for which the header data should be returned.
 * @param orientation The orientation of the header data.
 * @param role The role for which the header data should be returned.
 * @return The header data for the given section and orientation, or an invalid
 *         QVariant if the role is not supported or the section is invalid.
 */
QVariant DataModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole) {
        if(orientation == Qt::Horizontal){
            if(section < m_csvData -> columnCount()){
                return m_csvData -> getHeader(section);
            }
        }else{
            if(section < m_csvData -> rowCount()){
                return QString("%1").arg(section);
            }
        }
    }
    return QVariant();
}

/**
 * @brief Returns the item flags for the given model index.
 * @param index The model index for which the item flags should be returned.
 * @return The item flags for the given model index.
 */
Qt::ItemFlags DataModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
    }

    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemNeverHasChildren;
}

/**
 * @brief Sets the data at the given model index to the specified value for the given role.
 * @param index The model index of the data to be set.
 * @param value The value to set the data to.
 * @param role The role for which the data should be set.
 * @return "true" if the data was set successfully, "false" otherwise.
 */
bool DataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    (void) role;
    QString tmp = value.toString().replace(",", ".");

    bool isEdited = m_csvData -> set(index.row(), index.column(), tmp);
    if (isEdited == true) {
        emit dataEdited();
    }

    return isEdited;
}

/**
 * @brief Returns a pointer to the CSV data being managed by this model.
 * @return A pointer to the CSV data being managed by this model.
 */
CSVData* DataModel::getCSVData() const
{
    return m_csvData;
}

/**
 * @brief Sets the CSV data being managed by this model.
 * @param newCsvData A pointer to the new CSV data to be managed by this model.
 */
void DataModel::setCsvData(CSVData *newCsvData)
{
    m_csvData = newCsvData;
}

/**
 * @brief Inserts a new row into the model at the specified position.
 * @param row The position at which the new row should be inserted.
 * @param parent The parent index of the new row.
 * @return "true" if the row was inserted successfully, "false" otherwise.
 */
bool DataModel::insertNewRow(int row, const QModelIndex &parent)
{
    beginInsertRows(parent, row, row);
    QStringList newRow;
    for (int i = 0; i < m_csvData->m_header.size(); i++)
    {
        newRow << "";
    }
    m_csvData->m_rows.insert(row, newRow);
    endInsertRows();

    return true;
}

/**
 * @brief Remove a row inside the model at the specified position.
 * @param row The position at which the row should be deleted.
 * @param parent The parent index of the deleted row.
 * @return "true" if the row was deleted successfully, "false" otherwise.
 */
void DataModel::removeRow(int row, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row);
    m_csvData->m_rows.removeAt(row);
    endRemoveRows();
}
