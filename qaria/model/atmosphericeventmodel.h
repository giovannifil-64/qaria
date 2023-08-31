#ifndef ATMOSPHERICEVENTMODEL_H
#define ATMOSPHERICEVENTMODEL_H

#include <QStandardItemModel>

#include "model/aelist.h"


class AtmosphericEventModel: public QStandardItemModel
{
private:
    AEList* m_AEList;

public:
    AtmosphericEventModel(AEList* AEList);
    void filterByEvent(QString eventType);
    void filterByDanger(QString eventType);
};

#endif // ATMOSPHERICEVENTMODEL_H
