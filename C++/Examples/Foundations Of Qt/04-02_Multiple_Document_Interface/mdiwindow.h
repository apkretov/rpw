#pragma once

#include <QMainWindow>

class MdiWindow : public QMainWindow {
    Q_OBJECT
public:
    MdiWindow(QWidget *parent = nullptr);
};
