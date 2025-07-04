#include "DJViewView.h"

DJViewView::DJViewView(BeatModelInterface& model, QWidget *parent) : QWidget(parent), ui(new Ui::DJViewView), model(model) {
    ui->setupUi(this);
    model.registerObserver((BPMObserver*)this);
    model.registerObserver((BeatObserver*)this);
}

DJViewView::~DJViewView() { delete ui; }

void DJViewView::updateBPM() { ui->bpmOutputLabel->setText(QString::number(model.getBPM())); }

void DJViewView::updateBeat() { ui->beatBar->setValue(100); }
