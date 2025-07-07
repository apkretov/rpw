#pragma once

#include "ControllerInterface.h"

class HeartController : public ControllerInterface {
public:
    HeartController(HeartModelInterface& model) {}

    void start() override {}
    void stop() override {}
    void increaseBPM() override {}
    void decreaseBPM() override {}
    void setBPM(int bpm) override {}
};
