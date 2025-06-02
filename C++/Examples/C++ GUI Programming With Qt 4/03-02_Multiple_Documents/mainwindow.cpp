#pragma region We will now review the implementation

#include <QtGui>
#include "finddialog.h"
#include "gotocelldialog.h"
#include "mainwindow.h"
#include "sortdialog.h"
#include "spreadsheet.h" // We will implement it in Chapter 4.

MainWindow::MainWindow() {
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);
    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();
    readSettings();
    findDialog = 0;
    setWindowIcon(QIcon(":/images/icon.png")); //MINE: See the Perplexity comment below.
    setCurrentFile("");
}

#pragma endregion //We will now review the implementation

#pragma region Creating Menus and Toolbars
void MainWindow::createActions() {
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New); //TEST
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    // ...
    for (int i = 0; i < MaxRecentFiles; ++i) {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }

    // ...
    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction, SIGNAL(triggered()), spreadsheet, SLOT(selectAll()));

    // ...
    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));

    // ...
    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    #pragma region Multiple Documents
    // ...
    closeAction = new QAction(tr("&Close"), this);
    closeAction->setShortcut(QKeySequence::Close);
    closeAction->setStatusTip(tr("Close this window"));
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    // ...
    #pragma endregion //Multiple Documents
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    separatorAction = fileMenu->addSeparator(); //TEST
    for (int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    selectSubMenu = editMenu->addMenu(tr("&Select")); //TEST
    selectSubMenu->addAction(selectRowAction);
    selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    editMenu->addSeparator();
    editMenu->addAction(findAction);
    editMenu->addAction(goToCellAction);

    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);

    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    optionsMenu->addAction(autoRecalcAction);

    menuBar()->addSeparator(); //TEST

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu() {
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars() {
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(goToCellAction);
}
#pragma endregion //Creating Menus and Toolbars

#pragma region Setting Up the Status Bar
void MainWindow::createStatusBar() {
    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

    connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(updateStatusBar()));
    connect(spreadsheet, SIGNAL(modified()), this, SLOT(spreadsheetModified()));
    updateStatusBar();
}

void MainWindow::updateStatusBar() {
    locationLabel->setText(spreadsheet->currentLocation());
    formulaLabel->setText(spreadsheet->currentFormula());
}

void MainWindow::spreadsheetModified() {
    setWindowModified(true);
    updateStatusBar();
}
#pragma endregion //Setting Up the Status Bar

#pragma region Multiple Documents
void MainWindow::newFile() {
    MainWindow *mainWin = new MainWindow;
    mainWin->show();
}
#pragma endregion //Multiple Documents

#pragma region Implementing the File Menu
bool MainWindow::okToContinue() {
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("Spreadsheet"), tr("The document has been modified.\n" "Do you want to save your changes?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (r == QMessageBox::Yes)
            return save();
        else if (r == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::open() {
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Spreadsheet"), ".", tr("Spreadsheet files (*.sp)"));
        if (!fileName.isEmpty())
            loadFile(fileName);
    }
}

bool MainWindow::loadFile(const QString &fileName) {
    if (!spreadsheet->readFile(fileName)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::save() {
    if (curFile.isEmpty())
        return saveAs();
    else
        return saveFile(curFile);
}

bool MainWindow::saveFile(const QString &fileName) {
    if (!spreadsheet->writeFile(fileName)) {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

bool MainWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Spreadsheet"), ".", tr("Spreadsheet files (*.sp)"));
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (okToContinue()) {
        writeSettings();
        event->accept();
    } else
        event->ignore();
}

void MainWindow::setCurrentFile(const QString &fileName) {
    curFile = fileName;
    setWindowModified(false);
    QString shownName = tr("Untitled");
    if (!curFile.isEmpty()) {
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Spreadsheet")));
}

QString MainWindow::strippedName(const QString &fullFileName) { return QFileInfo(fullFileName).fileName(); }

void MainWindow::updateRecentFileActions() {
    QMutableStringListIterator i(recentFiles);
    while (i.hasNext()) {
        if (!QFile::exists(i.next()))
            i.remove();
    }

    for (int j = 0; j < MaxRecentFiles; ++j) {
        if (j < recentFiles.count()) {
            QString text = tr("&%1 %2").arg(j + 1).arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        } else
            recentFileActions[j]->setVisible(false);
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile() {
    if (okToContinue()) {
        QAction *action = qobject_cast<QAction *>(sender());
        if (action)
            loadFile(action->data().toString());
    }
}
#pragma endregion //Implementing the File Menu

#pragma region Using Dialogs
void MainWindow::find() {
    if (!findDialog) {
        findDialog = new FindDialog(this);
        connect(findDialog, SIGNAL(findNext(    const QString &, Qt::CaseSensitivity)), spreadsheet, SLOT(findNext(    const QString &, Qt::CaseSensitivity)));
        connect(findDialog, SIGNAL(findPrevious(const QString &, Qt::CaseSensitivity)), spreadsheet, SLOT(findPrevious(const QString &, Qt::CaseSensitivity)));
    }
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::goToCell() {
#ifndef VER_1
    GoToCellDialog dialog(this); //TEST
    if (dialog.exec()) {
        QString str = dialog.lineEdit->text().toUpper();
        spreadsheet->setCurrentCell(str.mid(1).toInt() - 1, str[0].unicode() - 'A');
    }
#else //VER_2
    GoToCellDialog *dialog = new GoToCellDialog(this);
    if (dialog->exec()) {
        QString str = dialog->lineEdit->text().toUpper();
        spreadsheet->setCurrentCell(str.mid(1).toInt() - 1, str[0].unicode() - 'A');
    }
    delete dialog;
#endif //VER_2
}

#ifndef VER_1
void MainWindow::sort() {
    SortDialog dialog(this);
    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());
    if (dialog.exec()) {
        SpreadsheetCompare compare;
        compare.keys[0] = dialog.primaryColumnCombo->currentIndex();
        compare.keys[1] = dialog.secondaryColumnCombo->currentIndex() - 1;
        compare.keys[2] = dialog.tertiaryColumnCombo->currentIndex() - 1;
        compare.ascending[0] = (dialog.primaryOrderCombo->currentIndex() == 0);
        compare.ascending[1] = (dialog.secondaryOrderCombo->currentIndex() == 0);
        compare.ascending[2] = (dialog.tertiaryOrderCombo->currentIndex() == 0);
        spreadsheet->sort(compare);
    }
}
#elif defined(VER_2)
void MainWindow::sort() {
    SortDialog dialog(this);
    dialog.setSpreadsheet(spreadsheet);
    dialog.exec();
}
#elif defined(VER_3)
void MainWindow::sort() {
    SortDialog dialog(this);
    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());
    if (dialog.exec())
        spreadsheet->performSort(dialog.comparisonObject());
}
#endif //VER_3

void MainWindow::about() {
    QMessageBox::about(this, tr("About Spreadsheet"),
                       tr("<h2>Spreadsheet 1.1</h2>"
                          "<p>Copyright &copy; 2008 Software Inc."
                          "<p>Spreadsheet is a small application that "
                          "demonstrates QAction, QMainWindow, QMenuBar, "
                          "QStatusBar, QTableWidget, QToolBar, and many other "
                          "Qt classes."));
}
#pragma endregion //Using Dialogs

#pragma region Storing Settings
void MainWindow::writeSettings() {
    QSettings settings("Software Inc.", "Spreadsheet");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", showGridAction->isChecked());
    settings.setValue("autoRecalc", autoRecalcAction->isChecked());
}

void MainWindow::readSettings() {
    QSettings settings("Software Inc.", "Spreadsheet");

    restoreGeometry(settings.value("geometry").toByteArray());

    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid", true).toBool();
    showGridAction->setChecked(showGrid);

    bool autoRecalc = settings.value("autoRecalc", true).toBool();
    autoRecalcAction->setChecked(autoRecalc);
}
#pragma endregion //Storing Settings

/* Perplexity

Is the .pro-file available with CMake Qt projects? How to access it in Qt 6.9?
To make use of Qt's resource system, we must create a resource file and add a line to the .pro file that identifies the resource
file. In this example, we have called the resource file spreadsheet.qrc, so we put the following line in the .pro file:
RESOURCES = spreadsheet.qrc
The resource file itself uses a simple XML format. Here's an extract from the one we have used:
images/icon.png
...
images/gotocell.png
The .pro file is specific to the qmake build system and is not used or available in CMake-based Qt projects, including those using Qt 6.9. Qt 6 and later strongly encourage using CMake as the primary build system instead of qmake, and the .pro file is replaced by CMakeLists.txt files for project configuration and building[1][2].
Accessing and Using Qt Resources in Qt 6.9 with CMake
In qmake projects, you specify resource files in the .pro file with a line like:
RESOURCES = spreadsheet.qrc

and the resource compiler (rcc) processes the .qrc files accordingly[3].
In CMake-based Qt projects (Qt 6.9), you do not use .pro files. Instead, you integrate Qt resources using CMake commands. The recommended way is to use the qt_add_resources() function provided by Qt's CMake integration. For example:
qt_add_resources(RES_SOURCES spreadsheet.qrc)
add_executable(MyApp main.cpp ${RES_SOURCES})

This tells CMake to process the .qrc file and generate the necessary code to embed the resources into your application. Also, ensure CMAKE_AUTORCC is enabled (which is usually on by default in Qt projects) so that resource files are automatically processed[4][3].
Summary
•	The .pro file is not available or used in CMake-based Qt projects, including Qt 6.9[1][2].
•	To use Qt resource files (.qrc) in Qt 6.9 with CMake, use qt_add_resources() in your CMakeLists.txt to add resource files to your target[4][3].
•	The resource system remains the same conceptually but is integrated differently depending on the build system (qmake vs CMake)[3].
Thus, if you are migrating from a .pro-based Qt project to CMake in Qt 6.9, you should convert your .pro resource declarations into appropriate qt_add_resources() calls in your CMake configuration.
⁂

<q>qt_add_resources(RES_SOURCES spreadsheet.qrc)
add_executable(MyApp main.cpp ${RES_SOURCES})</q> Where must spreadsheet.qrc be located?
Great question! When using qt_add_resources() in your CMakeLists.txt like this:
qt_add_resources(RES_SOURCES spreadsheet.qrc)
add_executable(MyApp main.cpp ${RES_SOURCES})

Where Should spreadsheet.qrc Be Located?
•	Relative to the CMakeLists.txt file:
The path to spreadsheet.qrc is interpreted relative to the directory containing the CMakeLists.txt file where qt_add_resources() is called.
•	Example:
If your project structure is:
MyProject/
├── CMakeLists.txt
├── spreadsheet.qrc
└── main.cpp

Then simply specifying spreadsheet.qrc works fine.
•	If located in a subdirectory:
If your resource file is inside a folder, for example resources/spreadsheet.qrc, you should specify the relative path accordingly:
qt_add_resources(RES_SOURCES resources/spreadsheet.qrc)

Important Notes:
•	The .qrc file path must be accessible at configure time by CMake.
•	You can also use absolute paths, but relative paths are recommended for portability.
•	If you move your CMakeLists.txt into a subdirectory, adjust the path to the .qrc file accordingly.

Summary
Location of spreadsheet.qrc	How to specify in qt_add_resources()
Same directory as CMakeLists.txt	spreadsheet.qrc
In a subfolder resources/	resources/spreadsheet.qrc
Elsewhere (not recommended)	Use relative or absolute path accordingly


If you want, I can help you with example project structures or more detailed CMake setup!

 Yes.
Here's an example of a well-structured Qt 6.9 project using CMake that includes a resource file (spreadsheet.qrc), showing where to place files and how to set up your CMakeLists.txt files:

Example Project Structure
MyQtProject/
├── CMakeLists.txt           # Top-level CMake file
├── resources/
│   └── spreadsheet.qrc      # Qt resource file here
├── src/
│   ├── main.cpp             # Main application source
│   ├── mainwindow.cpp       # Implementation of main window
│   ├── mainwindow.h         # Header for main window
│   ├── mainwindow.ui        # UI file (optional)
│   └── CMakeLists.txt       # CMake file for the app target


Top-level CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(MyQtProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 Widgets module (adjust components as needed)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Setup project with Qt standard settings
qt_standard_project_setup()

# Add the subdirectory containing the app sources
add_subdirectory(src)


src/CMakeLists.txt
# Add Qt resource file relative to this CMakeLists.txt
qt_add_resources(RES_SOURCES ../resources/spreadsheet.qrc)

# Add executable target with sources and generated resource sources
qt_add_executable(MyApp
    main.cpp
    mainwindow.cpp
    mainwindow.ui
    ${RES_SOURCES}
)

# Link Qt libraries
target_link_libraries(MyApp PRIVATE Qt6::Widgets)

# Optional: set properties for platform-specific bundles
set_target_properties(MyApp PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)


Explanation
•	The .qrc file is located in the resources/ folder at the project root.
•	In src/CMakeLists.txt, the path to the resource file is given relative to that CMakeLists.txt, hence ../resources/spreadsheet.qrc.
•	The qt_add_resources() macro processes the .qrc file and generates source files that are included in the target.
•	The qt_add_executable() command declares the executable and includes UI files, source files, and resource-generated sources.
•	The top-level CMakeLists.txt handles overall project setup and calls add_subdirectory(src) to build the app target.

This structure cleanly separates resources, sources, and build configuration, making it easy to maintain and extend your Qt project with CMake in Qt 6.9
*/
