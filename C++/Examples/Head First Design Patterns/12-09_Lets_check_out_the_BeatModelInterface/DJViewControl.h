#pragma once

#include <QMainWindow>
#include "./ui_djviewcontrol.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class DJView;
}
QT_END_NAMESPACE

class ControllerInterface;

class DJViewControl : public QMainWindow {
    Q_OBJECT
public:
    DJViewControl(ControllerInterface& controller, QWidget *parent = nullptr);
    ~DJViewControl();
private slots:
    void on_setBPMButton_clicked();
    void on_increaseBPMButton_clicked();
    void on_decreaseBPMButton_clicked();
    void on_actionStart_triggered();
    void on_actionStop_triggered();
private:
    Ui::DJView *ui;
    ControllerInterface& controller;
};
