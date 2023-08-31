#include "mainwindow.h"

#include "model/csvfile.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    m_currentFileName = m_newFileName;

    bool newFileFlag = true;
    m_csvData = new CSVData(newFileFlag);
    m_AEList.addElement(new AtmosphericEvent);

    QString windowTitle = QString("%1").arg(m_appName);
    setWindowTitle(windowTitle);

    m_centralWdgt = new QWidget(parent);
    setCentralWidget(m_centralWdgt);
    m_centralWdgt -> setLayout(new QVBoxLayout(parent));

    m_dataModel = new DataModel(m_csvData, this);
    connect(m_dataModel, &DataModel::dataEdited, this, &MainWindow::onDataModelEdited);

    m_dataView = new DataView(this);
    m_dataView -> setModel(m_dataModel);
    m_dataView -> setStyleSheet("QTableView::item{border : 1px solid gray}");
    m_dataView -> horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);

    m_comboBoxDelegate = new DataDelegate(this);
    m_dataView -> setItemDelegate(m_comboBoxDelegate);

    m_AEModel = new AtmosphericEventModel(&m_AEList);

    m_treeView = new QTreeView();
    m_treeView -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_treeView -> setModel(m_AEModel);

    QString stylingEnabled = ":enabled {background-color: #0a84ff; border-radius: 5px; color: white} :hover{background-color: #1e8eff;} :disabled {background-color: #8e8e93; border-radius: 5px; color: white}";

    m_editMode = true;

    QWidget* buttonsWidget = new QWidget(this);
    buttonsWidget -> setLayout(new QHBoxLayout);
    buttonsWidget -> setMaximumWidth(2000);

    m_filterWidget = new QWidget(this);
    m_filterWidget -> setLayout(new QHBoxLayout);
    m_filterWidget -> setMaximumWidth(1000);

    QWidget* mainWidget = new QWidget(this);
    mainWidget->setLayout(new QVBoxLayout);

    m_newFileButton = new QPushButton(this);
    m_newFileButton -> setFocusPolicy(Qt::StrongFocus);
    m_newFileButton -> setIcon(QIcon(":/images/fileNew.svg"));
    m_newFileButton -> setIconSize(QSize(44, 44));
    m_newFileButton -> setText("Nuovo File");
    m_newFileButton -> setFixedSize(QSize(135, 50));
    m_newFileButton -> setShortcut(QKeySequence("Ctrl+Shift+N"));
    m_newFileButton -> setStyleSheet(stylingEnabled);

    m_openFileButton = new QPushButton(this);
    m_openFileButton -> setFocusPolicy(Qt::StrongFocus);
    m_openFileButton -> setIcon(QIcon(":/images/fileOpen.svg"));
    m_openFileButton -> setIconSize(QSize(44, 44));
    m_openFileButton -> setText("Apri");
    m_openFileButton -> setFixedSize(QSize(135, 50));
    m_openFileButton -> setShortcut(QKeySequence("Ctrl+Shift+O"));
    m_openFileButton -> setStyleSheet(stylingEnabled);

    m_saveFileButton = new QPushButton(this);
    m_saveFileButton -> setFocusPolicy(Qt::StrongFocus);
    m_saveFileButton -> setIcon(QIcon(":/images/fileSave.svg"));
    m_saveFileButton -> setIconSize(QSize(44, 44));
    m_saveFileButton -> setText("Salva");
    m_saveFileButton -> setFixedSize(QSize(135, 50));
    m_saveFileButton -> setEnabled(false);
    m_saveFileButton -> setShortcut(QKeySequence("Ctrl+Shift+S"));
    m_saveFileButton -> setStyleSheet(stylingEnabled);

    m_saveAsFileButton = new QPushButton(this);
    m_saveAsFileButton -> setFocusPolicy(Qt::StrongFocus);
    m_saveAsFileButton -> setIcon(QIcon(":/images/fileSaveAs.svg"));
    m_saveAsFileButton -> setIconSize(QSize(44, 44));
    m_saveAsFileButton -> setText("Salva come");
    m_saveAsFileButton -> setFixedSize(QSize(135, 50));
    m_saveAsFileButton -> setEnabled(false);
    m_saveAsFileButton -> setShortcut(QKeySequence("Ctrl+Shift+A"));
    m_saveAsFileButton -> setStyleSheet(stylingEnabled);

    m_viewData = new QPushButton(this);
    m_viewData -> setFocusPolicy(Qt::StrongFocus);
    m_viewData -> setIcon(QIcon(":/images/viewData.svg"));
    m_viewData -> setIconSize(QSize(44, 44));
    m_viewData -> setText("Mostra dati");
    m_viewData -> setFixedSize(QSize(135, 50));
    m_viewData -> setShortcut(QKeySequence("Ctrl+Shift+V"));
    m_viewData -> setStyleSheet(stylingEnabled);

    connect(m_newFileButton, &QPushButton::released, this, &MainWindow::onNewButtonReleased);
    connect(m_openFileButton, &QPushButton::released, this, &MainWindow::onOpenButtonReleased);
    connect(m_saveFileButton, &QPushButton::released, this, &MainWindow::onSaveButtonReleased);
    connect(m_saveAsFileButton, &QPushButton::released, this, &MainWindow::onSaveAsButtonReleased);
    connect(m_viewData, &QPushButton::released, this, &MainWindow::onViewDataButtonReleased);

    m_filterByComboBox = new QComboBox;
    m_filterByComboBox -> addItem("Tutti");
    m_filterByComboBox -> addItem("Evento");
    m_filterByComboBox -> addItem("Pericolosità");

    m_filterTextComboBox = new QComboBox;
    m_filterTextComboBox -> setEnabled(false);

    m_filterByButton = new QPushButton(this);
    m_filterByButton -> setText("Filtra");
    m_filterByButton -> setMaximumHeight(30);
    m_filterByButton -> setStyleSheet(stylingEnabled);

    m_filterResetButton = new QPushButton(this);
    m_filterResetButton -> setFixedSize(QSize(100, 30));
    m_filterResetButton -> setText("Reset");
    m_filterResetButton -> setStyleSheet(":enabled {background-color: #ff453a; border-radius: 5px; color: white} :hover{background-color: #ff584e;} :disabled {background-color: #8e8e93; border-radius: 5px; color: white}");

    connect(m_filterByComboBox, &QComboBox::currentTextChanged, this, &MainWindow::onFilterByComboBoxTextChanged);
    connect(m_filterByButton, &QPushButton::released, this, &MainWindow::onFilterByButtonReleased);
    connect(m_filterResetButton, &QPushButton::released, this, &MainWindow::onFilterResetButtonReleased);


    m_centralWdgt -> layout() -> addWidget(mainWidget);

    buttonsWidget -> layout() -> addWidget(m_newFileButton);
    buttonsWidget -> layout() -> addWidget(m_openFileButton);
    buttonsWidget -> layout() -> addWidget(m_saveFileButton);
    buttonsWidget -> layout() -> addWidget(m_saveAsFileButton);
    buttonsWidget -> layout() -> addWidget(m_viewData);
    mainWidget -> layout() -> addWidget(buttonsWidget);
    
    m_filterWidget -> layout() -> addWidget(m_filterByComboBox);
    m_filterWidget -> layout() -> addWidget(m_filterTextComboBox);
    m_filterWidget -> layout() -> addWidget(m_filterByButton);
    m_filterWidget -> layout() -> addWidget(m_filterResetButton);
    mainWidget -> layout() -> addWidget(m_filterWidget);
    mainWidget -> layout() -> setAlignment(Qt::AlignCenter);


    m_centralWdgt -> layout() -> addWidget(m_dataView);
    m_filterWidget -> setEnabled(false);
    m_treeView -> setVisible(false);
    m_centralWdgt -> layout() -> addWidget(m_treeView);


    QMenu* file = menuBar() -> addMenu("&File");

    auto* newFile = new QAction("&Nuovo...", this);
    auto* saveFile = new QAction("&Salva File", this);
    auto* saveAsFile = new QAction("&Salva Come", this);
    auto* openFile = new QAction("&Apri...", this);
    auto* viewData = new QAction("&Mostra i Dati", this);

    newFile -> setShortcut(tr("Ctrl+Shift+N"));
    saveFile -> setShortcut(tr("Ctrl+Shift+S"));
    saveAsFile -> setShortcut(tr("Ctrl+Shift+A"));
    openFile -> setShortcut(tr("Ctrl+Shift+O"));
    viewData -> setShortcut(tr("Ctrl+Shift+V"));

    file -> addAction(newFile);
    file -> addAction(saveFile);
    file -> addAction(saveAsFile);
    file -> addAction(openFile);
    file -> addAction(viewData);

    connect(newFile, &QAction::triggered, this, &MainWindow::onNewButtonReleased);
    connect(saveFile, &QAction::triggered, this, &MainWindow::onSaveButtonReleased);
    connect(saveAsFile, &QAction::triggered, this, &MainWindow::onSaveAsButtonReleased);
    connect(openFile, &QAction::triggered, this, &MainWindow::onOpenButtonReleased);
    connect(viewData, &QAction::triggered, this, &MainWindow::onViewDataButtonReleased);

    connect(m_treeView, &QTreeView::clicked, this, &MainWindow::onTreeViewClicked);
    connect(m_treeView, &QTreeView::expanded, this, &MainWindow::onTreeViewExpandedCollapsed);
    connect(m_treeView, &QTreeView::collapsed, this, &MainWindow::onTreeViewExpandedCollapsed);


    windowTitle = QString("%1 - %2").arg(m_appName, m_currentFileName);
    setWindowTitle(windowTitle);

}

MainWindow::~MainWindow()
{

}

/**
 * @brief Opens a dialog box to select a CSV file and sets the selected file as the current file.
 */
void MainWindow::onNewButtonReleased()
{
    if(checkSavedStatus() == true){
        bool newFileFlag = true;
        m_csvData = new CSVData(newFileFlag);
        loadCSVData();
        m_currentFileName = m_newFileName;
        m_saveFileButton -> setEnabled(false);
        m_saveAsFileButton -> setEnabled(false);
        QString windowTitle = QString("%1 - %2").arg(m_appName, m_currentFileName);
        setWindowTitle(windowTitle);
    }
    if(m_AEWidget != nullptr){
        m_AEWidget -> setVisible(false);
    }
}

/**
 * @brief This function is called when the "Open" button is clicked. It opens a file dialog to allow the user to select a CSV file to open.
 *        If the "Save" button is enabled, the function will show a message box asking the user if they want to save their current file.
 *        If the user selects "Cancel" in the message box, the function will return without doing anything else.
 *        Otherwise, it will open the selected CSV file and load its data into the application, updating the window title to reflect the current file name.
 */
void MainWindow::onOpenButtonReleased()
{
    if(m_saveFileButton -> isEnabled()){
        if(showSaveMessageBox() == QMessageBox::Cancel){
            return;
        }
    }

    m_currentFileName = QFileDialog::getOpenFileName(this, tr("Seleziona un file CSV"), "", tr("Comma Separated Values (*.csv)"));
    m_csvData = new CSVData;

    if(m_currentFileName != ""){
        CSVFile csvfile(m_currentFileName);
        m_csvData = csvfile.readCSV();
        loadCSVData();
        QString windowTitle = QString("%1 - %2").arg(m_appName, m_currentFileName);
        setWindowTitle(windowTitle);
    }
}

/**
 * @brief this function saves the file. If the is a new file created in the app, the Save As dialog box will appear,
 *        instead just save the file
 */
void MainWindow::onSaveButtonReleased()
{
    if(m_currentFileName == m_newFileName){
        onSaveAsButtonReleased();
    }else{
        saveCSVData(m_currentFileName);
        m_saveFileButton -> setEnabled(false);
        m_saveAsFileButton -> setEnabled(false);
        QString windowTitle = QString("%1 - %2").arg(m_appName, m_currentFileName);
        setWindowTitle(windowTitle);

    }
}

/**
 * @brief this function enables the "Save" and "Save As" buttons, and changes the title by adding a "*" to indicate a modified file
 */
void MainWindow::onDataModelEdited()
{
    m_saveFileButton -> setEnabled(true);
    m_saveAsFileButton -> setEnabled(true);
    QString windowTitle = QString("%1 - * %2").arg(m_appName, m_currentFileName);
    setWindowTitle(windowTitle);
}

/**
 * @brief this function opens a QFileDialog for giving a name and selecting the path of where to save the file
 */
void MainWindow::onSaveAsButtonReleased()
{
    m_currentFileName = QFileDialog::getSaveFileName(this, tr(""), ".", tr("Comma Separated Values (*.csv)"));
    saveCSVData(m_currentFileName);
    m_saveFileButton -> setEnabled(false);
    m_saveAsFileButton -> setEnabled(false);
    QString windowTitle = QString("%1 - %2").arg(m_appName, m_currentFileName);
    setWindowTitle(windowTitle);
}

/**
 * @brief This function toggles the visibility of the data view and tree view widgets. If the edit mode is true,
 *        the visibility of the data view widget is set to true, the visibility of the tree view widget is set to false,
 *        and the text and icon of the view data button are changed. If the edit mode is false,
 *        the visibility of the data view widget is set to false, the visibility of the tree view widget is set to true,
 *        and the text and icon of the view data button are changed.
 */
void MainWindow::onViewDataButtonReleased()
{
    if(m_editMode == true){
        m_viewData -> setText("Modifica dati");
        m_viewData -> setIcon(QIcon(":/images/editData.svg"));
        m_viewData -> setIconSize(QSize(44, 44));
        m_editMode = false;
        m_filterWidget -> setEnabled(true);



        m_dataView -> setVisible(false);
        m_treeView -> setVisible(true);
        if(m_AEWidget != nullptr){
            m_AEWidget -> setVisible(true);
        }

    }else{
        m_viewData -> setText("Mostra dati");
        m_viewData -> setIcon(QIcon(":/images/viewData.svg"));
        m_viewData -> setIconSize(QSize(44, 44));
        m_editMode = true;
        m_filterWidget -> setEnabled(false);
        m_dataView -> setVisible(true);
        m_treeView -> setVisible(false);
        if(m_AEWidget != nullptr){
            m_AEWidget -> setVisible(false);
        }
    }
}

/**
 * @brief this function writes the changes into the given CSV file
 * @param QString fileName: thhe name of the file that will be override
 */
void MainWindow::saveCSVData(QString fileName)
{
    CSVFile csvfile(fileName);
    DataModel* dataModel = (DataModel*) m_dataView -> model();
    CSVData* csvData = dataModel -> getCSVData();
    csvfile.writeCSV(csvData);

    m_AEList.clear();
    m_AEList.populate(m_csvData);
    m_AEModel = new AtmosphericEventModel(&m_AEList);
    m_treeView -> setModel(m_AEModel);
}

/**
 * @brief this function load the given CSV file
 * @param csvdata is the given file that will be shown in the main window
 */
void MainWindow::loadCSVData()
{
    m_dataModel = new DataModel(m_csvData, this);
    connect(m_dataModel, &DataModel::dataEdited, this, &MainWindow::onDataModelEdited);

    m_dataView -> setModel(m_dataModel);

    m_AEList.clear();
    m_AEList.populate(m_csvData);

    m_AEModel = new AtmosphericEventModel(&m_AEList);
    m_treeView -> setModel(m_AEModel);

    for (int i = 0; i < m_dataModel->columnCount(); i++){
        m_dataView -> resizeColumnToContents(i);
    }

    for (int i = 0; i < m_AEModel->columnCount(); i++){
        m_treeView -> resizeColumnToContents(i);
    }
}

QMessageBox::StandardButton MainWindow::showSaveMessageBox()
{
    QMessageBox msgBox;
    msgBox.setText("Il file è stato modificato");
    msgBox.setInformativeText("Vuoi salvare le modifiche?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Yes);
    QMessageBox::StandardButton ret = (QMessageBox::StandardButton)msgBox.exec();

    return ret;
}

/**
 * @brief when the "X" button for closing the window is pressed,
 *        a message box appears ONLY if there are unsaved changes to the file
 */
void MainWindow::closeEvent(QCloseEvent* event)
{
    if(m_saveFileButton->isEnabled()){
        QMessageBox::StandardButton resBtn = showSaveMessageBox();
        if(resBtn == QMessageBox::Yes){
            if(m_currentFileName == m_newFileName){
                onSaveAsButtonReleased();
            }else{
                saveCSVData(m_currentFileName);
            }
        }
        if (resBtn == QMessageBox::Cancel) {
            event -> ignore();
        }else{
            event -> accept();
        }
    }
}

/**
 * @brief Checks the saved status and performs necessary actions if the file is unsaved.
 * @return True if the file is saved or no actions are required, false otherwise.
 */
bool MainWindow::checkSavedStatus()
{
    if(m_saveFileButton->isEnabled()){
        QMessageBox::StandardButton resBtn = showSaveMessageBox();
        if(resBtn == QMessageBox::Yes){
            if(m_currentFileName == m_newFileName){
                onSaveAsButtonReleased();
            }else{
                saveCSVData(m_currentFileName);
            }
        }
    }
    return true;
}


/**
 * @brief This function gets the row number of the clicked item or its parent,
 *        gets the corresponding atmospheric event from the list of atmospheric events,
 *        removes and deletes the existing atmospheric event widget (if it exists),
 *        creates a new atmospheric event widget, and paints the atmospheric event on it.
 * @param modelIndex The model index of the clicked item.
 * @return This function does not return anything.
 */
void MainWindow::onTreeViewClicked(const QModelIndex& modelIndex)
{
    int row = modelIndex.row();
    QModelIndex idModelindex;

    if (modelIndex.parent().isValid()) {
        row = modelIndex.parent().row();
        idModelindex = modelIndex.parent().sibling(row, 1);

    }else{
        idModelindex = modelIndex.sibling(row, 1);

    }

    QStandardItem* idItem = m_AEModel -> itemFromIndex(idModelindex);
    QString idString = idItem->text();

    bool convertionDone;
    int id = idString.toInt(&convertionDone);

    if(convertionDone == false){
        return;
    }

    AtmosphericEvent* AE = m_AEList.getElementById(id);
    if(AE == NULL){
        return;
    }

    if (m_AEWidget != nullptr) {
        m_centralWdgt->layout()->removeWidget(m_AEWidget);
        delete m_AEWidget;
    }
    
    DataDelegate* dd = new DataDelegate();
    m_AEWidget = new QWidget;
    dd->draw(m_AEWidget, AE);
    m_centralWdgt->layout()->addWidget(m_AEWidget);
}


/**
 * @brief This function updates the size of the tree view's columns when the tree view is expanded or collapsed.
 * @param modelIndex A QModelIndex representing the tree view item that was expanded or collapsed. This parameter is not used in the function.
 */
void MainWindow::onTreeViewExpandedCollapsed(const QModelIndex& modelIndex)
{
    (void) modelIndex;
    for (int i = 0; i < m_AEModel->columnCount(); i++){
        m_treeView -> resizeColumnToContents(i);
    }
}

/**
 * @brief Slot function called when the text in the filter by combo box changes.
 * @param text The new text in the combo box.
 */
void MainWindow::onFilterByComboBoxTextChanged(const QString& text)
{
    if (text == "Tutti") {
        m_filterTextComboBox -> setEnabled(false);
    } else if (text == "Evento") {
        m_filterTextComboBox -> setEnabled(true);
        m_filterTextComboBox -> clear();
        m_filterTextComboBox -> addItems(m_AEList.getEventTypes());
    } else if (text == "Pericolosità") {
        m_filterTextComboBox -> setEnabled(true);
        m_filterTextComboBox -> clear();
        m_filterTextComboBox -> addItems(m_AEList.getDangerLevels());
    }

}

/**
 * @brief When a specific filter is selected, it applies the filter on the view.
 */
void MainWindow::onFilterByButtonReleased()
{
    m_AEModel = new AtmosphericEventModel(&m_AEList);
    QString filterBy = m_filterByComboBox -> currentText();
    QString filterText = m_filterTextComboBox -> currentText();

    if (filterBy == "Tutti") {
        // No filter applied
    } else if (filterBy == "Evento") {
        m_AEModel -> filterByEvent(filterText);
    } else if (filterBy == "Pericolosità") {
        m_AEModel -> filterByDanger(filterText);
    }

    m_treeView -> setModel(m_AEModel);
}

/**
 * @brief It removes the applied filter, showing all the data.
 */
void MainWindow::onFilterResetButtonReleased()
{
    m_AEModel = new AtmosphericEventModel(&m_AEList);
    m_filterByComboBox -> setCurrentIndex(0);
    m_filterTextComboBox -> setCurrentIndex(0);
    m_filterTextComboBox -> setEnabled(false);

    m_treeView -> setModel(m_AEModel);
}
