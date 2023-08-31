#ifndef CSVDATA_H
#define CSVDATA_H

#include <QStringList>

class CSVData
{
public:
    QStringList m_header;
    QList<QStringList> m_rows;

    CSVData(bool newFile = false);
    QString get(int row, int column);
    QString getHeader(int index);
    int rowCount();
    int columnCount();
    bool set(int row, int column, QString value);
};

#endif // CSVDATA_H
