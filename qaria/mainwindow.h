#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QPushButton>
#include <QMessageBox>
#include <QMenu>
#include <QMenuBar>
#include <QList>
#include <QTreeView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QToolButton>
#include <QDebug>
#include <QFileInfo>
#include <QShortcut>
#include <QAction>
#include <QInputDialog>
#include <QCloseEvent>
#include <QComboBox>
#include <QHeaderView>
#include <QPalette>

#include "view/dataview.h"
#include "view/datadelegate.h"

#include "model/atmosphericeventmodel.h"
#include "model/datamodel.h"
#include "model/csvdata.h"
#include "model/aelist.h"

class MainWindow: public QMainWindow
{
    Q_OBJECT
private:
    CSVData* m_csvData;

    DataModel* m_dataModel;
    DataView* m_dataView;
    DataDelegate* m_comboBoxDelegate;

    QTreeView* m_treeView;
    AtmosphericEventModel* m_AEModel;

    AEList m_AEList;

    QWidget* m_centralWdgt;
    QString m_currentFileName;

    /* Buttons */
    QPushButton* m_newFileButton;
    QPushButton* m_openFileButton;
    QPushButton* m_saveFileButton;
    QPushButton* m_saveAsFileButton;
    QPushButton* m_viewData;

    /* Filters */
    QWidget* m_filterWidget;

    QComboBox* m_filterByComboBox;
    QComboBox* m_filterTextComboBox;
    QPushButton* m_filterByButton;
    QPushButton* m_filterResetButton;

    const QString m_appName = "qaria";
    QString m_newFileName = "untitled.csv";

    const QString stylingEnabled;

    QMessageBox::StandardButton showSaveMessageBox();

    QWidget* m_AEWidget = nullptr;

    void closeEvent(QCloseEvent* event) override;

    bool checkSavedStatus();

    void saveCSVData(QString fileName);
    void loadCSVData();

    bool m_editMode;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onNewButtonReleased();
    void onOpenButtonReleased();
    void onSaveButtonReleased();
    void onDataModelEdited();
    void onSaveAsButtonReleased();
    void onViewDataButtonReleased();
    void onTreeViewClicked(const QModelIndex& modelIndex);
    void onTreeViewExpandedCollapsed(const QModelIndex& modelIndex);
    void onFilterByComboBoxTextChanged(const QString& text);

    void onFilterByButtonReleased();
    void onFilterResetButtonReleased();

};
#endif // MAINWINDOW_H
