#include "atmosphericevent.h"

void AtmosphericEvent::setNext(AtmosphericEvent *next)
{
    m_next = next;
}

void AtmosphericEvent::setEvent(const QString &newEvento)
{
    m_evento = newEvento;
}

void AtmosphericEvent::setId(unsigned int newId)
{
    m_id = newId;
}

AtmosphericEvent::AtmosphericEvent() : m_next(nullptr){}

AtmosphericEvent::AtmosphericEvent(AtmosphericEvent &ae) :
    m_evento        (ae.m_evento       ),
    m_id            (ae.m_id           ),
    m_luogo         (ae.m_luogo        ),
    m_temperatura   (ae.m_temperatura  ),
    m_quota         (ae.m_quota        ),
    m_dataOraInizio (ae.m_dataOraInizio),
    m_dataOraFine   (ae.m_dataOraFine  ),
    m_pericolosita  (ae.m_pericolosita ),
    m_next          (nullptr)
{

}

/**
 * @brief Populates an AtmosphericEvent object with data from a list of strings
 * @param row QStringList object representing a row of data
 */
void AtmosphericEvent::populate(QStringList row)
{
    if(row.size() >= 1){
        m_evento = row[0];
    }

    if(row.size() >= 2){
        m_id = row[1].toUInt();
    }

    if(row.size() >= 3){
        m_luogo = row[2].toStdString();
    }

    if(row.size() >= 4){
        m_temperatura = row[3].toInt();
    }

    if(row.size() >= 5){
        m_quota = row[4].toUInt();
    }

    if(row.size() >= 6){
        m_dataOraInizio = QDateTime::fromString(row[5], "dd-MM-yyyy hh:mm");
    }

    if(row.size() >= 7){
        m_dataOraFine = QDateTime::fromString(row[6], "dd-MM-yyyy hh:mm");
    }

    if(row.size() >= 8){
        m_pericolosita = row[7];
    }
}


/**
 * @brief Returns a list of QStandardItem pointers representing a row of data for an AtmosphericEvent object
 * @return QList<QStandardItem*> List of QStandardItem pointers representing a row of data for the event
 */
QList<QStandardItem*> AtmosphericEvent::getStandardItemRow()
{
    QList<QStandardItem*> row;
    row.append(new QStandardItem(QString(m_evento)));
    row.append(new QStandardItem(QString::number(m_id)));
    row.append(new QStandardItem(QString::fromStdString(m_luogo)));
    row.append(new QStandardItem(QString::number(m_temperatura)));
    row.append(new QStandardItem(QString::number(m_quota)));
    row.append(new QStandardItem(m_dataOraInizio.toString("dd-MM-yyyy hh:mm")));
    row.append(new QStandardItem(m_dataOraFine.toString("dd-MM-yyyy hh:mm")));
    row.append(new QStandardItem(QString(m_pericolosita)));
    return row;
}


Snow::Snow() : AtmosphericEvent()
{
    m_imagePath = ":/images/AESnow.svg";
}

void Snow::populate(QStringList row)
{
    AtmosphericEvent::populate(row);
    if(row.size() >= 8){
        m_valanga = row[7].toUInt();
    }

    if(row.size() >= 9){
        m_quantitaCm = row[8].toUInt();
    }
}

QList<QStandardItem*> Snow::getStandardItemRow()
{
    QList<QStandardItem*> row = AtmosphericEvent::getStandardItemRow();

    QList<QStandardItem*> valangaRow;
    valangaRow << new QStandardItem(QString("Valanga: ") + QString::number(m_valanga));
    row.first() -> appendRow(valangaRow);

    QList<QStandardItem*> quantitaRow;
    quantitaRow << new QStandardItem(QString("Quantità (cm): ") + QString::number(convertMillimetersToCentimeters()));
    row.first() -> appendRow(quantitaRow);

    return row;
}


Rain::Rain() : AtmosphericEvent()
{
    m_imagePath = ":/images/AERain.svg";
}

void Rain::populate(QStringList row)
{
    AtmosphericEvent::populate(row);
    if(row.size() >= 9){
        m_quantitaMm = row[8].toUInt();
    }

    if(row.size() >= 10){
        m_frana = row[9].toUInt();
    }
}

QList<QStandardItem*> Rain::getStandardItemRow()
{
    QList<QStandardItem*> row = AtmosphericEvent::getStandardItemRow();

    QList<QStandardItem*> quantitaRow;
    quantitaRow << new QStandardItem(QString("Quantità (mm): ") + QString::number(m_quantitaMm));
    row.first() -> appendRow(quantitaRow);

    QList<QStandardItem*> franaRow;
    franaRow << new QStandardItem(QString("Frana: ") + QString::number(m_frana));
    row.first() -> appendRow(franaRow);

    return row;
}


HailStorm::HailStorm() : AtmosphericEvent()
{
    m_imagePath = ":/images/AEHail.svg";
}

void HailStorm::populate(QStringList row)
{
    AtmosphericEvent::populate(row);
    if(row.size() >= 9){
        m_diametroMm = row[8].toUInt();
    }
}

QList<QStandardItem*> HailStorm::getStandardItemRow()
{
    QList<QStandardItem*> row = AtmosphericEvent::getStandardItemRow();
    //row.append(new QStandardItem(QString::number(m_diametroMm)));

    QList<QStandardItem*> diametroRow;
    diametroRow << new QStandardItem(QString("Diametro (mm): ") + QString::number(m_diametroMm));
    row.first() -> appendRow(diametroRow);

    return row;
}