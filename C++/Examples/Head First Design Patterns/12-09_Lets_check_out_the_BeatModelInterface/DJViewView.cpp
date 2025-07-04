#include "DJViewView.h"

DJViewView::DJViewView(BeatModelInterface& model, QWidget *parent) : QWidget(parent), ui(new Ui::DJViewView), model(model) {
    ui->setupUi(this);
    model.registerObserver(static_cast<BPMObserver*>(this));
    model.registerObserver(static_cast<BeatObserver*>(this));
}

DJViewView::~DJViewView() { 
	model.removeObserver(static_cast<BeatObserver *>(this));
	model.removeObserver(static_cast<BPMObserver *>(this));
	delete ui; 
} 

#include <iostream>
void DJViewView::updateBPM() { 
	ui->bpmOutputLabel->setText(QString::number(model.getBPM())); 
	std::cout << "222 DJViewView::updateBPM()\n";
}

void DJViewView::updateBeat() { ui->beatBar->setValue(100); }
