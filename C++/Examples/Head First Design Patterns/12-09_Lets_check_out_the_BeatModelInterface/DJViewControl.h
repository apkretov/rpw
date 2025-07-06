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
    Ui::DJView *ui;
    ControllerInterface& controller;
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
        ui->actionStop->setEnabled(false);
    }

    ~DJViewControl() { delete ui; }
private slots:
    void setBPM() { controller.setBPM(ui->bpmTextField->text().toInt()); }
    void increaseBPM() { controller.increaseBPM(); }
    void decreaseBPM() { controller.decreaseBPM(); }

    void start() {
        controller.start();
        ui->actionStart->setEnabled(false);
        ui->actionStop->setEnabled(true);
    }

    void stop() {
        controller.stop();
        ui->actionStart->setEnabled(true);
        ui->actionStop->setEnabled(false);
    }

    void quit() { qApp->quit(); }
};
