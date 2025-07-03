#include "DJViewControl.h"
#include "ControllerInterface.h"

DJViewControl::DJViewControl(ControllerInterface& controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DJView),
    controller(controller)
{
    ui->setupUi(this);
}

DJViewControl::~DJViewControl()
{
    delete ui;
}

void DJViewControl::on_setBPMButton_clicked()
{
    controller.setBPM(ui->bpmTextField->text().toInt());
}

void DJViewControl::on_increaseBPMButton_clicked()
{
    controller.increaseBPM();
}

void DJViewControl::on_decreaseBPMButton_clicked()
{
    controller.decreaseBPM();
}

void DJViewControl::on_actionStart_triggered()
{
    controller.start();
}

void DJViewControl::on_actionStop_triggered()
{
    controller.stop();
}
