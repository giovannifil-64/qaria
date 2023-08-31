#include "csvdata.h"

/**
 * @brief Constructor for the CSVData class
 * @param rows The number of rows to initialize the CSVData instance with.
 * @param columns The number of columns to initialize the CSVData instance with.
 * @return A new instance of the CSVData class, initialized with the specified number of rows and columns.
 */
CSVData::CSVData(bool newFile)
{
    QStringList headerLabels = {
            "Evento",
            "id",
            "Luogo",
            "Temperatura",
            "Quota",
            "Data d'inizio",
            "Data di fine",
            "Pericolosità",
            "Quantità",
            "Distacco",
            "Diametro"
    };

    int rows = 0;
    if(newFile == true){
        rows = 1;
    }

    int columns = headerLabels.size();

    for(int i = 0; i < columns; i++){
        m_header.append(headerLabels.at(i));
    }

    for(int i = 0; i < rows; i++){
        QStringList row = {"P", "1", "Padova", "0", "0", "01-01-1970 00:01", "01-01-1970 00:01", "!", "0", "0", "-"};
        m_rows.append(row);
    }
}

/**
 * @brief Gets the value at a specific row and column in the CSVData instance.
 * @param row The row index to get the value from.
 * @param column The column index to get the value from.
 * @return The value at the specified row and column. If the row or column index is invalid, returns "ERROR".
 */
QString CSVData::get(int row, int column)
{
    if (row < rowCount()){
        if (column < m_rows.at(row).count()){
            return m_rows.at(row).at(column);
        }else{
            return "ERROR";   //ERROR viene mostrato, ma non permette la modifica della cella
        }
    }else{
        return "ERROR";
    }
}

/**
 * @brief Sets the value at a specific row and column in the CSVData instance.
 * @param row The row index to set the value at.
 * @param column The column index to set the value at.
 * @param value The value to set at the specified row and column.
 * @return A boolean indicating whether the operation was successful. Returns true if the row and column index are valid, and false otherwise.
 */
bool CSVData::set(int row, int column, QString value)
{
    if (row < rowCount()){
        if (column < m_rows.at(row).count()){
            m_rows[row][column] = value;
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

/**
 * @brief this function takes in input the index and return the corrisponding header
 * @param integer rapresenting the index of the header
 * @return returns the header at a specific index, else returns an error
 */
QString CSVData::getHeader(int index)
{
    if(index < m_header.count()){
        return m_header.at(index);
    }else{
        return "error getting header";
    }
}

/**
 * @brief Gets the number of rows in the CSVData instance.
 * @return The number of rows in the CSVData instance.
 */
int CSVData::rowCount()
{
    return m_rows.count();
}

/**
 * @brief Gets the number of columns in the CSVData instance.
 * @return The number of columns in the CSVData instance.
 */
int CSVData::columnCount()
{
    return m_header.count();
}
