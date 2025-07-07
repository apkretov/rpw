#pragma once

#include "ControllerInterface.h"
#include "BeatModelInterface.h"

class ControllerBeat : public ControllerInterface {
    BeatModelInterface& model;
public:
	ControllerBeat(BeatModelInterface &model) : model(model) {}
    void start() override { model.on(); }
    void stop() override { model.off(); }

    void increaseBPM() override {
        int bpm = model.getBPM();
        model.setBPM(bpm + 1);
    }

    void decreaseBPM() override {
        int bpm = model.getBPM();
        model.setBPM(bpm - 1);
    }

    void setBPM(int bpm) override { model.setBPM(bpm); }
};