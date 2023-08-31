#ifndef ATMOSPHERICEVENT_H
#define ATMOSPHERICEVENT_H

#include <QDateTime>
#include <QList>
#include <QStandardItem>
#include <QString>
#include <QPixmap>

#include <string>
#include <iostream>

class AtmosphericEvent
{
private:
    QString m_evento;
    unsigned int m_id;
    std::string m_luogo;
    int m_temperatura;
    unsigned int m_quota;
    QDateTime m_dataOraInizio;
    QDateTime m_dataOraFine;
    QString m_pericolosita;

    AtmosphericEvent* m_next;

protected:
    QString m_imagePath;

public:
    AtmosphericEvent();
    AtmosphericEvent(AtmosphericEvent& ae);
    virtual ~AtmosphericEvent() = default;

    virtual void populate(QStringList row);
    virtual QList<QStandardItem*> getStandardItemRow();
    void setNext(AtmosphericEvent* next);

    QString getEvento() const {return m_evento;}
    std::string getLuogo() const {return m_luogo;}
    int getTemperatura() const {return m_temperatura;}
    unsigned int getQuota() const {return m_quota;}
    QDateTime getOraInizio() const {return m_dataOraInizio;}
    QDateTime getOraFine() const {return m_dataOraFine;}
    QString getPericolosita() const {return m_pericolosita;}
    QString getEvent() const {return m_evento;}
    AtmosphericEvent* getNext() const {return m_next;}
    unsigned int getId() const {return m_id;}

    QString getPath() const {return m_imagePath;}

    void setEvent(const QString &newEvento);
    void setId(unsigned int newId);
};

class Snow: public AtmosphericEvent
{
private:
    unsigned int m_quantitaCm;
    unsigned int m_valanga;

public:
    Snow();
    /**
     * @brief Converts height in millimeters to centimeters.
     * @param heightInMillimeters The height in millimeters.
     * @return The height in centimeters.
     */
    int convertMillimetersToCentimeters() const {return m_quantitaCm / 10;} 

    void populate(QStringList row) override;
    QList<QStandardItem*> getStandardItemRow() override;

    QString getPath() const {return m_imagePath;}
    unsigned int getQuantitaCm() const {return m_quantitaCm;}
    unsigned int getValanga() const {return m_valanga;}
};

class Rain: public AtmosphericEvent
{
private:
    unsigned int m_quantitaMm;
    unsigned int m_frana;

public:
    Rain();
    void populate(QStringList row) override;
    QList<QStandardItem*> getStandardItemRow() override;

    QString getPath() const {return m_imagePath;}
    unsigned int getQuantitaMm() const {return m_quantitaMm;}
    unsigned int getFrana() const {return m_frana;}
};

class HailStorm: public AtmosphericEvent
{
private:
    unsigned int m_diametroMm;

public:
    HailStorm();
    void populate(QStringList row) override;
    QList<QStandardItem*> getStandardItemRow() override;

    QString getPath() const {return m_imagePath;}
    unsigned int getDiametroMm() const {return m_diametroMm;}
};


#endif // ATMOSPHERICEVENT_H
