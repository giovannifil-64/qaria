#include "aelist.h"

AEList::AEList() : m_head(nullptr)
{

}

/**
 * @brief Adds an AtmosphericEvent to the list.
 * @param ae The AtmosphericEvent to add.
 */
void AEList::addElement(AtmosphericEvent* ae)
{
    AtmosphericEvent* current = m_head;
    if (current == nullptr) {
        m_head = ae;
    } else {
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        current->setNext(ae);
    }
}

/**
 * @brief Returns the AtmosphericEvent at the specified index.
 * @param index The index of the AtmosphericEvent.
 * @return The AtmosphericEvent at the specified index, or nullptr if not found.
 */
AtmosphericEvent* AEList::getElement(int index)
{
    AtmosphericEvent* current = m_head;
    int i = 0;
    while (current != nullptr) {
        if (i == index) {
            return current;
        }
        current = current->getNext();
        i++;
    }
    return nullptr;
}

/**
 * @brief Removes the AtmosphericEvent with the specified ID from the list.
 * @param id The ID of the AtmosphericEvent to remove.
 */
void AEList::removeElement(unsigned int id)
{
    AtmosphericEvent* current = m_head;
    AtmosphericEvent* previous = nullptr;
    while (current != nullptr) {
        if (current->getId() == id) {
            if (previous == nullptr) {
                m_head = current->getNext();
            } else {
                previous->setNext(current->getNext());
            }
            delete current;
            return;
        }
        previous = current;
        current = current->getNext();
    }
}

/**
 * @brief Returns the AtmosphericEvent with the specified ID.
 * @param id The ID of the AtmosphericEvent to find.
 * @return The AtmosphericEvent with the specified ID, or nullptr if not found.
 */
AtmosphericEvent* AEList::getElementById(unsigned int id)
{
    AtmosphericEvent* current = m_head;
    while (current != nullptr) {
        if (current->getId() == id) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

/**
 * @brief Finds AtmosphericEvents with the specified event type.
 * @param eventType The event type to search for.
 * @return A new AEList containing the matching AtmosphericEvents.
 */
AEList AEList::findByEventType(QString eventType)
{
    AEList list;
    for (AtmosphericEvent* current = m_head; current != nullptr; current = current->getNext()) {
        if (current->getEvent() == eventType) {
            AtmosphericEvent* matchingEvent = new AtmosphericEvent(*current);
            list.addElement(matchingEvent);
        }
    }
    return list;
}

/**
 * @brief Finds AtmosphericEvents with the specified danger level.
 * @param dangerLevel The danger level to search for.
 * @return A new AEList containing the matching AtmosphericEvents.
 */
AEList AEList::findByDangerLevel(QString dangerLevel)
{
    AEList list;
    AtmosphericEvent* current = m_head;
    while (current != nullptr) {
        if (current->getPericolosita() == dangerLevel) {
            AtmosphericEvent* matchingEvent = new AtmosphericEvent(*current);
            list.addElement(matchingEvent);
        }
        current = current->getNext();
    }
    return list;
}

/**
 * @brief Returns a QStringList of unique event types in the list.
 * @return A QStringList of event types.
 */
QStringList AEList::getEventTypes()
{
    QStringList list;
    AtmosphericEvent* current = m_head;
    while (current != nullptr) {
        if (!list.contains(current->getEvent())) {
            list.append(current->getEvent());
        }
        current = current->getNext();
    }
    return list;
}

/**
 * @brief Returns a QStringList of unique danger levels in the list.
 * @return A QStringList of danger levels.
 */
QStringList AEList::getDangerLevels()
{
    QStringList list;
    AtmosphericEvent* current = m_head;
    while (current != nullptr) {
        if (!list.contains(current->getPericolosita())) {
            list.append(current->getPericolosita());
        }
        current = current->getNext();
    }
    return list;
}

/**
 * @brief Clears the AEList by deleting all AtmosphericEvent objects.
 */
void AEList::clear()
{
    AtmosphericEvent* current = m_head;
    AtmosphericEvent* next = nullptr;
    while (current != nullptr) {
        next = current->getNext();
        delete current;
        current = next;
    }
    m_head = nullptr;
}

/**
 * @brief Populates the AEList from the provided CSVData.
 * @param csvData The CSVData object containing the data to populate from.
 */
void AEList::populate(CSVData* csvData)
{
    int row = csvData->rowCount();
    for (int i = 0; i < row; i++) {
        if (csvData->get(i, 0) == "P") {
            Rain* rain = new Rain();
            rain->populate(csvData->m_rows.at(i));
            addElement(rain);
        } else if (csvData->get(i, 0) == "N") {
            Snow* snow = new Snow();
            snow->populate(csvData->m_rows.at(i));
            addElement(snow);
        } else if (csvData->get(i, 0) == "G") {
            HailStorm* hailStorm = new HailStorm();
            hailStorm->populate(csvData->m_rows.at(i));
            addElement(hailStorm);
        } else {
            AtmosphericEvent* AE = new AtmosphericEvent();
            AE->populate(csvData->m_rows.at(i));
            addElement(AE);
        }
    }
}

/**
 * @brief Returns the size of the AEList.
 * @return The number of AtmosphericEvent objects in the list.
 */
int AEList::getSize()
{
    AtmosphericEvent* current = m_head;
    int i = 0;
    while (current != nullptr) {
        current = current->getNext();
        i++;
    }
    return i;
}

