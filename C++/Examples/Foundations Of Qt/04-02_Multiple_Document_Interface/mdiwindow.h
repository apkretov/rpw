#pragma once

#include <QMainWindow>

class QMdiArea;
class QSignalMapper;
class QAction;
class DocumentWindow;
class QMenu;

class MdiWindow : public QMainWindow {
    Q_OBJECT
public:
    MdiWindow(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *event); // Event handlers are typically protected methods overridden by the widget
private: // Member variables and internal helper functions (not slots).
    QMdiArea *workspace; // Member variables to hold child Qt objects
    QSignalMapper *mapper;
    QAction *closeAction;
    QAction *tileAction;
    QAction *separatorAction;
    QAction *pasteAction;
    QAction *cascadeAction;
    QAction *nextAction;
    QAction *previousAction;
    QAction *cutAction;
    QAction *copyAction;
    QMenu *windowMenu; // Member variable to hold the window menu

    DocumentWindow *activeDocument(); // Helper methods called internally, not directly by signals
    void createActions();
    void createMenus();
    void createToolbars() {} // Note: No empty '{}' here, as it's just a declaration. The empty implementation is in the .cpp file.
private slots: // Methods intended to be connected to signals
    void fileNew(); // Slots connected to QAction::triggered() or similar signals
    void editCut();
    void editCopy();
    void editPaste();

    void enableActions(); // Slots connected to other object signals
    void updateWindowList();
};
