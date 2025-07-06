#pragma once

#include <QMainWindow>
#include "./ui_djviewcontrol.h"
#include "ControllerInterface.h"
#include <QApplication>

QT_BEGIN_NAMESPACE
namespace Ui {
    class DJView;
}
QT_END_NAMESPACE

class DJViewControl : public QMainWindow {
    Q_OBJECT
public:
    DJViewControl(ControllerInterface& controller, QWidget *parent = nullptr) :
        QMainWindow(parent),
        ui(new Ui::DJView),
        controller(controller)
    {
        ui->setupUi(this);
        connect(ui->setBPMButton, &QPushButton::clicked, this, &DJViewControl::setBPM);
        connect(ui->increaseBPMButton, &QPushButton::clicked, this, &DJViewControl::increaseBPM);
        connect(ui->decreaseBPMButton, &QPushButton::clicked, this, &DJViewControl::decreaseBPM);
        connect(ui->actionStart, &QAction::triggered, this, &DJViewControl::start);
        connect(ui->actionStop, &QAction::triggered, this, &DJViewControl::stop);
        connect(ui->actionQuit, &QAction::triggered, this, &DJViewControl::quit);
    }

    ~DJViewControl() { delete ui; }

private slots:
    void setBPM() { controller.setBPM(ui->bpmTextField->text().toInt()); }
    void increaseBPM() { controller.increaseBPM(); }
    void decreaseBPM() { controller.decreaseBPM(); }
    void start() { controller.start(); }
    void stop() { controller.stop(); }
    void quit() { qApp->quit(); }

private:
    Ui::DJView *ui;
    ControllerInterface& controller;
};