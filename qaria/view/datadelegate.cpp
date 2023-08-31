#include "datadelegate.h"

DataDelegate::DataDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    
}

/**
 * @brief Creates and returns an editor widget for the given item index and parent widget.
 * @param parent The parent widget.
 * @param option The style options for the item view.
 * @param index The model index representing the item.
 * @return The created editor widget.
 */
QWidget *DataDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    if (index.column() == 0 || index.column() == 7) {
        QComboBox* editor = new QComboBox(parent);

        if (index.column() == 0) {
            editor->addItem("P");
            editor->addItem("N");
            editor->addItem("G");
        } else /*23_05*/ if (index.column() == 7){
            editor->addItem("!");
            editor->addItem("!!");
            editor->addItem("!!!");
            editor->addItem("!!!!");
        }

        editor->setFrame(false);

        // Set the editor data
        setEditorData(editor, index);

        return editor;
    } else {
        // Create a QTextEdit editor for other columns
        QTextEdit* editor = new QTextEdit(parent);
        return editor;
    }
}

/**
 * @brief Sets the data of the editor based on the given item index.
 * @param editor The editor widget.
 * @param index The model index representing the item.
 */
void DataDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.column() == 0 || index.column() == 7) {
        // Editor is a combobox
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString value = index.model()->data(index, Qt::EditRole).toString();
        comboBox->setCurrentText(value);
    } else {
        // Editor is a QTextEdit
        QTextEdit *textEdit = static_cast<QTextEdit*>(editor);
        QString value = index.model()->data(index, Qt::EditRole).toString();
        textEdit->setText(value);
    }
}

/**
 * @brief Sets the data of the model based on the value of the editor.
 * @param editor The editor widget.
 * @param model The model to set the data in.
 * @param index The model index representing the item.
 */
void DataDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (index.column() == 0 || index.column() == 7) {
        // Editor is a combobox
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value, Qt::EditRole);
    } else {
        // Editor is a QTextEdit
        QTextEdit* textEdit = static_cast<QTextEdit*>(editor);
        QString value = textEdit->toPlainText();
        model->setData(index, value, Qt::EditRole);
    }
}

/**
 * @brief Updates the geometry of the editor widget.
 * @param editor The editor widget.
 * @param option The style options for the item view.
 * @param index The model index representing the item.
 */
void DataDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}



/**
 * @brief Displays the data for an AtmosphericEvent object in a widget
 * @param AEWidget Pointer to an AtmosphericEventWidget object to display the data in
 */
void DataDelegate::draw(QWidget* AEWidget, AtmosphericEvent* AE) const
{
    QLabel* luogoLabel = new QLabel(QString("Luogo: ") + QString::fromStdString(AE->getLuogo()));
    QLabel* temperaturaLabel = new QLabel(QString("Temperatura: ") + QString::number(AE->getTemperatura()));
    QLabel* quotaLabel = new QLabel(QString("Quota: ") + QString::number(AE->getQuota()));
    QLabel* dataOraInizioLabel = new QLabel("Data e ora inizio: " + AE->getOraInizio().toString("dd-MM-yyyy hh:mm"));
    QLabel* dataOraFineLabel = new QLabel("Data e ora fine: " + AE->getOraFine().toString("dd-MM-yyyy hh:mm"));
    QLabel* pericolositaLabel = new QLabel(QString("Pericolosità: ") + QString(AE->getPericolosita()));

    m_layout -> addWidget(luogoLabel, 0, 0);
    m_layout -> addWidget(temperaturaLabel, 1, 0);
    m_layout -> addWidget(quotaLabel, 2, 0);
    m_layout -> addWidget(dataOraInizioLabel, 3, 0);
    m_layout -> addWidget(dataOraFineLabel, 4, 0);
    m_layout -> addWidget(pericolositaLabel, 5, 0);

    QPixmap pix(AE->getPath());
    QPixmap scaledPix = pix.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_pixMapLabel -> setPixmap(scaledPix);

    m_layout -> addWidget(m_pixMapLabel, 0, 2, -1, -1);

    AEWidget -> setLayout(m_layout);
}



/* SNOW DELEGATE */
void SnowDelegate::draw(QWidget* AEWidget, AtmosphericEvent* AE) const
{
    DataDelegate::draw(AEWidget, AE);
    QLabel* quantitaCmLabel = new QLabel(QString("Quantità (cm): ") + QString::number(dynamic_cast<Snow*>(AE)->getQuantitaCm()));
    QLabel* valangaLabel = new QLabel(QString("Valanga: ") + QString::number(dynamic_cast<Snow*>(AE)->getValanga()));
    
    if (m_layout) {
        m_layout->addWidget(quantitaCmLabel, 0, 1);
        m_layout->addWidget(valangaLabel, 1, 1);

        AEWidget->setLayout(m_layout);
    }
}



/* RAIN DELEGATE */
void RainDelegate::draw(QWidget* AEWidget, AtmosphericEvent* AE) const
{
    DataDelegate::draw(AEWidget, AE);
    QLabel* quantitaMmLabel = new QLabel(QString("Quantità (mm): ") + QString::number(dynamic_cast<Rain*>(AE)->getQuantitaMm()));
    QLabel* grandineLabel = new QLabel(QString("Grandine: ") + QString::number(dynamic_cast<Rain*>(AE)->getFrana()));

    if (m_layout) {
        m_layout->addWidget(quantitaMmLabel, 0, 1);
        m_layout->addWidget(grandineLabel, 1, 1);

        AEWidget->setLayout(m_layout);
    }
}



/* HAILSTORM DELEGATE */
void HailStormDelegate::draw(QWidget* AEWidget, AtmosphericEvent* AE) const
{
    DataDelegate::draw(AEWidget, AE);
    QLabel* m_diametroMmLabel = new QLabel(QString("Diametro (mm): ") + QString::number(dynamic_cast<HailStorm*>(AE)->getDiametroMm()));

    if (m_layout) {
        m_layout -> addWidget(m_diametroMmLabel, 0, 1);

        AEWidget -> setLayout(m_layout);
    }
}