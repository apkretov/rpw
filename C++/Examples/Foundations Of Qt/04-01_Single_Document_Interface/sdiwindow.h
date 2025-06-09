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
    void fileNew();
    void createActions();
    void createMenus();
    void createToolbars();
    QAction *newAction;
    QAction *cutAction;
    QAction *aboutQtAction;
    QAction *closeAction = nullptr;
    QAction *exitAction = nullptr;
#pragma endregion //MINE
};
