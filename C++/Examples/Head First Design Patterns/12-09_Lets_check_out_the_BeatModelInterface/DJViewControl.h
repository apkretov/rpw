#pragma once

#include <QMainWindow>
#include "./ui_djviewcontrol.h"
#include "ObserverBPM.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class DJView;
}
QT_END_NAMESPACE

class ControllerInterface;
class BeatModelInterface;

class DJViewControl : public QMainWindow, public BPMObserver {
    Q_OBJECT
public:
    DJViewControl(ControllerInterface& controller, BeatModelInterface& model, QWidget *parent = nullptr);
    ~DJViewControl();

public slots:
    void updateBPM() override;

private slots:
    void on_setBPMButton_clicked();
    void on_increaseBPMButton_clicked();
    void on_decreaseBPMButton_clicked();
    void on_actionStart_triggered();
    void on_actionStop_triggered();
    void on_actionQuit_triggered();

private:
    void enableStopMenuItem();
    void disableStopMenuItem();
    void enableStartMenuItem();
    void disableStartMenuItem();

private:
    Ui::DJView *ui;
    ControllerInterface& controller;
    BeatModelInterface& model;
};
