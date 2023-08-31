#include "dataview.h"

#include <QHeaderView>
#include <QInputDialog>
#include <QMenu>

#include <iostream>

#include "model/datamodel.h"

/**
 * @brief Constructor for the DataView class, which is a subclass of QTableView.
 * @param parent The parent widget of the DataView instance.
 * @return A new instance of the DataView class, initialized with the provided parent widget.
 */
DataView::DataView(QWidget *parent): QTableView(parent)
{
    QHeaderView* vHeader = verticalHeader();
    vHeader -> setContextMenuPolicy(Qt::CustomContextMenu);
    connect(vHeader, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customVHeaderMenuRequested(QPoint)));
}

/**
 * @brief Inserts a new row above the currently selected row.
 */
void DataView::onInsertRowBeforeAction(){
    ((DataModel*) model()) -> insertNewRow(m_currentSection);
}

/**
 * @brief Inserts a new row under the currently selected row.
 */
void DataView::onInsertRowAfterAction(){
    ((DataModel*) model()) -> insertNewRow(m_currentSection + 1);
}
/**
 * @brief Deletes the currently selected row.
 */
void DataView::onDeleteRowAction(){
    ((DataModel*) model()) -> removeRow(m_currentSection);
}

/**
 * @brief Displays a context menu with options for inserting new columns in the DataView instance when the horizontal header is right-clicked.
 * @param pos The position of the mouse cursor when the context menu was requested.
 */

//Inside header: void paint(AtmosphericEvent* event, QWidget* widget);

void DataView::customVHeaderMenuRequested(QPoint pos){
    m_currentSection = verticalHeader() -> logicalIndexAt(pos);

    QMenu* menu = new QMenu(this);

    QAction* insertLeftAction = new QAction("Inserisci prima", this);
    connect(insertLeftAction, &QAction::triggered, this, &DataView::onInsertRowBeforeAction);

    QAction* insertRightAction = new QAction("Inserisci dopo", this);
    connect(insertRightAction, &QAction::triggered, this, &DataView::onInsertRowAfterAction);

    QAction* removeAction = new QAction("Elimina", this);
    connect(removeAction, &QAction::triggered, this, &DataView::onDeleteRowAction);

    menu -> addAction(insertLeftAction);
    menu -> addAction(insertRightAction);
    menu -> addAction(removeAction);

    menu -> popup(verticalHeader() -> viewport() -> mapToGlobal(pos));
}
