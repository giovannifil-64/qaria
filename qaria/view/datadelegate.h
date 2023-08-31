#ifndef DATADELEGATE_H
#define DATADELEGATE_H

#include <QComboBox>
#include <QDateTime>
#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QPixmap>
#include <QSpinBox>
#include <QStandardItem>
#include <QStyledItemDelegate>
#include <QString>
#include <QTextEdit>

#include "model/atmosphericevent.h"

class DataDelegate : public QStyledItemDelegate
{
    Q_OBJECT

protected:
    QString* m_imagePath = new QString();
    QLabel* m_pixMapLabel = new QLabel;
    QGridLayout* m_layout = new QGridLayout();
    AtmosphericEvent* m_next;

public:
    DataDelegate(QObject *parent = nullptr);
    ~DataDelegate() = default;
    
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    
    virtual void draw(QWidget* AEWidget, AtmosphericEvent* AE) const;
};

class SnowDelegate : public Snow, public DataDelegate
{
public:
    virtual void draw(QWidget* AEWidget, AtmosphericEvent* AE) const;
};

class RainDelegate : public Rain, public DataDelegate
{
public:
    virtual void draw(QWidget* AEWidget, AtmosphericEvent* AE) const;
};

class HailStormDelegate : public HailStorm, public DataDelegate
{
public:
    virtual void draw(QWidget* AEWidget, AtmosphericEvent* AE) const;
};

#endif // DATADELEGATE_H