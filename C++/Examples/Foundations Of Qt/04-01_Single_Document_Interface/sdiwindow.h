#pragma once

#include <QMainWindow>

class QTextEdit;

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
#pragma endregion //MINE
};
