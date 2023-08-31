#ifndef AELIST_H
#define AELIST_H

#include <QString>

#include "atmosphericevent.h"
#include "csvdata.h"

class AEList
{
private:
    AtmosphericEvent* m_head = nullptr;

public:
    AEList();

    void addElement(AtmosphericEvent* ae);
    AtmosphericEvent* getElement(int index);
    void removeElement(unsigned int id);
    AtmosphericEvent* getElementById(unsigned int id);
    AEList findByEventType(QString eventType);
    AEList findByDangerLevel(QString dangerLevel);

    void clear();
    void populate(CSVData* csvData);
    int getSize();

    QStringList getEventTypes();
    QStringList getDangerLevels();
};

#endif // AELIST_H
