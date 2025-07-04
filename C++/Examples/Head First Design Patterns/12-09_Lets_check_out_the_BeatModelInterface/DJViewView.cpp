#include "DJViewView.h"

DJViewView::DJViewView(BeatModelInterface& model, QWidget *parent) : QWidget(parent), ui(new Ui::DJViewView), model(model) {
    ui->setupUi(this);
    model.registerObserver((BPMObserver*)this);
    model.registerObserver((BeatObserver*)this);
}

DJViewView::~DJViewView() { delete ui; } //TO DO: Is this deletion needed in deed?

#include <iostream>
void DJViewView::updateBPM() { 
	ui->bpmOutputLabel->setText(QString::number(model.getBPM())); 
	std::cout << "222 DJViewView::updateBPM()\n";
}

void DJViewView::updateBeat() { ui->beatBar->setValue(100); }
