#pragma once

#include "ControllerInterface.h"
#include "HeartModelInterface.h"
#include "DJView.h"
#include "HeartAdapter.h"

class HeartController : public ControllerInterface {
    HeartModelInterface& model;
    DJView* view;

public:
    HeartController(HeartModelInterface& model) : model(model) {
        view = new DJView(this, new HeartAdapter(model));
        view->createView();
        view->createControls();
        view->disableStopMenuItem();
        view->disableStartMenuItem();
    }

    void start() override {}
    void stop() override {}
    void increaseBPM() override {}
    void decreaseBPM() override {}
    void setBPM(int bpm) override {}
};
