#include "DJViewControl.h"
#include "ControllerInterface.h"

DJViewControl::DJViewControl(ControllerInterface& controller, QWidget *parent) : QMainWindow(parent), ui(new Ui::DJView), controller(controller) {
    ui->setupUi(this);
    
    connect(ui->setBPMButton, &QPushButton::clicked, this, &DJViewControl::setBPM); // Explicit connections
    connect(ui->increaseBPMButton, &QPushButton::clicked, this, &DJViewControl::increaseBPM);
    connect(ui->decreaseBPMButton, &QPushButton::clicked, this, &DJViewControl::decreaseBPM);
}

DJViewControl::~DJViewControl() { delete ui; }

void DJViewControl::setBPM() { controller.setBPM(ui->bpmTextField->text().toInt()); }

void DJViewControl::increaseBPM() { controller.increaseBPM(); }

void DJViewControl::decreaseBPM() { controller.decreaseBPM(); }
