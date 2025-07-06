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
    void setBPM();
    void increaseBPM();
    void decreaseBPM();
    void start();
    void stop();
    void quit();
private:
    Ui::DJView *ui;
    ControllerInterface& controller;
};
