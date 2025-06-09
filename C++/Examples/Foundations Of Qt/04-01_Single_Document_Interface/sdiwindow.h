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
    void closeEvent(QCloseEvent *event);
    bool isSafeToClose();
    QAction *newAction;
    QAction *cutAction;
    QAction *aboutQtAction;
    QAction *closeAction = nullptr;
    QAction *exitAction = nullptr;
#pragma endregion //MINE
};
