#include "csvfile.h"


CSVFile::CSVFile(const QString &name) : QFile(name)
{

}

/**
 * @brief Reads a CSV file and stores its data in an instance of the CSVData class
 * @return A pointer to an instance of the CSVData class, containing the data from the CSV file.
 */
CSVData* CSVFile::readCSV()
{
    CSVData* csvData = new CSVData();
    bool firstRow = true;

    if (!open(QIODevice::ReadOnly)) {
        return csvData;
    }

    while (!atEnd()) {
        QStringList row;
        QByteArray lineBA = readLine();
        QString lineString(lineBA);
        row = lineString.trimmed().split(',');
        if(firstRow == true){
            csvData -> m_header = row;
            firstRow = false;
        }else{
            csvData -> m_rows.append(row);
        }
    }

    close();

    return csvData;
}

/**
 * @brief Write the data from a CSVData object to a CSV file.
 * @param csvData Pointer to the CSVData object containing the data to be written.
 * @return 0 if the operation was successful, 1 if an error occurred.
 */
int CSVFile::writeCSV(CSVData* csvData)
{
    std::ofstream out(fileName().toStdString(), std::ofstream::trunc);
    if (!out) {
        qDebug() << errorString();
        return 1;
    }

    for (const auto& element : csvData->m_header) {
        out << element.toStdString();
        if (&element != &csvData->m_header.back()) {
            out << ",";
        }
    }
    out << "\n";

    for (const auto& row : csvData->m_rows) {
        for (const auto& element : row) {
            out << element.toStdString();
            if (&element != &row.back()) {
                out << ",";
            }
        }
        out << "\n";
    }
    out.close();

    return 0;
}
