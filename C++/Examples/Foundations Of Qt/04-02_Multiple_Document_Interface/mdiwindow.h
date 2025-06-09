#pragma once

#include <QMainWindow>

class QMdiArea;
class QSignalMapper;
class QAction;

class MdiWindow : public QMainWindow {
    Q_OBJECT
public:
    MdiWindow(QWidget *parent = nullptr);
private:
    QMdiArea *workspace;
    QSignalMapper *mapper;
    QAction *closeAction;
    QAction *tileAction;
    QAction *separatorAction;
private slots:
    void enableActions() {}
    void createActions();
    void createMenus() {}
    void createToolbars() {}
};
