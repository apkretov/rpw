#pragma once

#include <QMainWindow>

class QMdiArea;
class QSignalMapper;

class MdiWindow : public QMainWindow {
    Q_OBJECT
public:
    MdiWindow(QWidget *parent = nullptr);
private:
    QMdiArea *workspace;
    QSignalMapper *mapper;
private slots:
    void enableActions() {}
    void createActions() {}
    void createMenus() {}
    void createToolbars() {}
};
