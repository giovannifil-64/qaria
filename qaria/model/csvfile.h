#ifndef CSVFILE_H
#define CSVFILE_H

#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <fstream>

#include "csvdata.h"

class CSVFile : public QFile
{
public:
    CSVFile(const QString &name);
    CSVData* readCSV();
    int writeCSV(CSVData* csvData);
};

#endif // CSVFILE_H
