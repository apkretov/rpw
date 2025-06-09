#pragma once

#include <QMainWindow>

class QTextEdit;

class SdiWindow : public QMainWindow {
    Q_OBJECT
public:
    SdiWindow(QWidget *parent = nullptr);
private:
    QTextEdit *docWidget; //MINE
    
    void createActions();
    void createMenus();
    void createToolbars();
};
