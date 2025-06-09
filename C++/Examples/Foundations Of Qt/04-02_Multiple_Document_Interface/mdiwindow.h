#pragma once

#include <QMainWindow>

class QMdiArea;
class QSignalMapper;
class QAction;
class DocumentWindow;

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
    QAction *pasteAction;
    QAction *cascadeAction;
    QAction *nextAction;
    QAction *previousAction;
    QAction *cutAction;
    QAction *copyAction;
    DocumentWindow *activeDocument();
    void editCut();
    void editCopy();
    void editPaste();
private slots:
    void enableActions();
    void createActions();
    void createMenus();
    void createToolbars() {}
    void updateWindowList();
};
