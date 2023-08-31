#ifndef DATAVIEW_H
#define DATAVIEW_H

#include <QTableView>

class DataView: public QTableView
{
    Q_OBJECT;
private:
    int m_currentSection;
    QString showNewHeaderNameDialog(QString currentName);

public:
    DataView(QWidget *parent);

public slots:
    void onInsertRowBeforeAction();
    void onInsertRowAfterAction();
    void onDeleteRowAction();
    void customVHeaderMenuRequested(QPoint pos);
};

#endif // DATAVIEW_H
