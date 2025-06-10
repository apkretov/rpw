#pragma once

#include <QMainWindow>

class QTextEdit;
class QAction;

class SdiWindow : public QMainWindow {
    Q_OBJECT
public:
    SdiWindow(QWidget *parent = nullptr);
private:
#pragma region MINE
    QTextEdit *docWidget;
    void createActions();
    void createMenus();
    void createToolbars();
    void fileNew();
    void about();
    void closeEvent(QCloseEvent *event);
    bool isSafeToClose();
    QAction *newAction;
    QAction *closeAction;
    QAction *exitAction;
    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *aboutQtAction;
#pragma endregion //MINE
};
