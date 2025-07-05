#include "DJViewControl.h"
#include "ControllerInterface.h"
#include "BeatModelInterface.h"

DJViewControl::DJViewControl(ControllerInterface& controller, BeatModelInterface& model, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DJView),
    controller(controller),
    model(model)
{
    ui->setupUi(this);
    model.registerObserver((BPMObserver*)this);
    disableStopMenuItem();
    enableStartMenuItem();
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
    disableStartMenuItem();
    enableStopMenuItem();
}

void DJViewControl::on_actionStop_triggered()
{
    controller.stop();
    disableStopMenuItem();
    enableStartMenuItem();
}

void DJViewControl::on_actionQuit_triggered() { close(); }

void DJViewControl::updateBPM()
{
    if (model.getBPM() == 0) {
        ui->bpmOutputLabel->setText("offline");
    } else {
        ui->bpmOutputLabel->setText(QString::number(model.getBPM()));
    }
}

void DJViewControl::enableStopMenuItem()
{
    ui->actionStop->setEnabled(true);
}

void DJViewControl::disableStopMenuItem()
{
    ui->actionStop->setEnabled(false);
}

void DJViewControl::enableStartMenuItem()
{
    ui->actionStart->setEnabled(true);
}

void DJViewControl::disableStartMenuItem()
{
    ui->actionStart->setEnabled(false);
}

