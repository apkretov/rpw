#pragma once

#pragma region The source code for the Spreadsheet applications main window is spread across mainwindow.h and mainwindow.cpp. // The source code for the Spreadsheet application's main window is spread across mainwindow.h and mainwindow.cpp.

#include <QMainWindow>

class QAction;
class QLabel;
class FindDialog;
class Spreadsheet;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void find();
    void goToCell();
    void sort();
    void about();

    void openRecentFile();
    void updateStatusBar();
    void spreadsheetModified();
private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);

    Spreadsheet *spreadsheet;

    FindDialog *findDialog;
    QLabel *locationLabel;
    QLabel *formulaLabel;
    QStringList recentFiles;
    QString curFile;

    enum { MaxRecentFiles = 5 };
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    // ...
    QToolBar *fileToolBar;
    QToolBar *editToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction; //MINE
    QAction *saveAsAction; //MINE
    QAction *exitAction; //MINE
    QAction *selectAllAction; //MINE
    QAction *showGridAction; //MINE
    QAction *autoRecalcAction; //MINE
    QAction *cutAction; //MINE
    QAction *copyAction; //MINE
    QAction *pasteAction; //MINE
    QAction *deleteAction; //MINE
    QAction *selectRowAction; //MINE
    QAction *selectColumnAction; //MINE
    QAction *goToCellAction; //MINE
    QAction *findAction; //MINE
    QAction *recalculateAction; //MINE
    QAction *sortAction; //MINE
    QAction *aboutAction; //MINE
    // ...
    QAction *aboutQtAction;
};
#pragma endregion //The source code for the Spreadsheet application's main window is spread across mainwindow.h and mainwindow.cpp.
