#pragma once

#include <QWidget>
#include "ui_djviewview.h"

namespace Ui {
    class DJViewView;
}

#include "ObserverBPM.h"
#include "ObserverBeat.h"
#include "BeatModelInterface.h"

class DJViewView : public QWidget, public BPMObserver, public BeatObserver {
    Q_OBJECT
    Ui::DJViewView *ui;
    BeatModelInterface& model;
public:
    explicit DJViewView(BeatModelInterface& model, QWidget *parent = nullptr);
    ~DJViewView();
public slots:
    void updateBPM() override;
    void updateBeat() override;
};
