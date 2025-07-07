#pragma once

#include <QTimer>
#include <QWidget>
#include "ui_djviewview.h"
#include "ObserverBPM.h"
#include "ObserverBeat.h"
#include "BeatModelInterface.h"

namespace Ui {
    class DJViewView;
}

class DJViewView : public QWidget, public BeatObserver, public BPMObserver {
    Q_OBJECT
    Ui::DJViewView *ui;
    BeatModelInterface& model;
public:
    explicit DJViewView(BeatModelInterface& model, QWidget *parent = nullptr) : QWidget(parent), ui(new Ui::DJViewView), model(model) {
        ui->setupUi(this);
        model.registerObserver(static_cast<BPMObserver*>(this));
        model.registerObserver(static_cast<BeatObserver*>(this));
    }

    ~DJViewView() {
        model.removeObserver(static_cast<BeatObserver *>(this));
        model.removeObserver(static_cast<BPMObserver *>(this));
        delete ui;
    }
public slots:
    void updateBPM() override { 
        if (model.getBPM() == 0)
            ui->bpmOutputLabel->setText("offline");
        else
            ui->bpmOutputLabel->setText(QString::number(model.getBPM())); 
    }

    void updateBeat() override { 
        ui->beatBar->setValue(100);
        QTimer::singleShot(50, this, [this]() { ui->beatBar->setValue(ui->beatBar->minimum()); });
    }
};
