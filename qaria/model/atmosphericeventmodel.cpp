#include "atmosphericeventmodel.h"

/**
 * @brief Constructor for the AtmosphericEventModel class
 * @param csvData A pointer to a CSVData object containing data for the atmospheric events
 * @param AEList A pointer to an AtmosphericEventList object containing the atmospheric events
 */
AtmosphericEventModel::AtmosphericEventModel(AEList* AEList) : m_AEList(AEList)
{
    QStringList headerLabels = {
        "Evento",
        "id",
        "Luogo",
        "Temperatura",
        "Quota",
        "Data d'inizio",
        "Data di fine",
        "Pericolosità"
    };

    setHorizontalHeaderLabels(headerLabels);

    QStandardItem *parentItem = invisibleRootItem();
    for (int i = 0; i < AEList -> getSize(); ++i) {
        QList<QStandardItem*> row;
        row = AEList -> getElement(i) -> getStandardItemRow();
        parentItem->appendRow(row);
    }
}

void AtmosphericEventModel::filterByEvent(QString eventType){
    removeRows(0, m_AEList -> getSize());
    AEList subList = m_AEList -> findByEventType(eventType);
    QStandardItem *parentItem = invisibleRootItem();
    for (int i = 0; i < subList.getSize(); ++i) {
        QList<QStandardItem*> row;
        row = subList.getElement(i) -> getStandardItemRow();
        parentItem -> appendRow(row);
    }
}

void AtmosphericEventModel::filterByDanger(QString eventType){
    removeRows(0, m_AEList -> getSize());
    AEList subList = m_AEList -> findByDangerLevel(eventType);
    QStandardItem *parentItem = invisibleRootItem();
    for (int i = 0; i < subList.getSize(); ++i) {
        QList<QStandardItem*> row;
        row = subList.getElement(i) -> getStandardItemRow();
        parentItem -> appendRow(row);
    }
}
