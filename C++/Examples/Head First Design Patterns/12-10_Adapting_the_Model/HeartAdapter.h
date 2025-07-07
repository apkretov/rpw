#pragma once

#include "BeatModelInterface.h"
#include "HeartModelInterface.h"

class HeartAdapter : public BeatModelInterface {
    HeartModelInterface& heart;

public:
    HeartAdapter(HeartModelInterface& heart) : heart(heart) {}

    void initialize() override {}
    void on() override {}
    void off() override {}

    int getBPM() const override {
        return heart.getHeartRate();
    }

    void setBPM(int bpm) override {}

    void registerObserver(BeatObserver* o) override {
        heart.registerObserver(o);
    }

    void removeObserver(BeatObserver* o) override {
        heart.removeObserver(o);
    }

    void registerObserver(BPMObserver* o) override {
        heart.registerObserver(o);
    }

    void removeObserver(BPMObserver* o) override {
        heart.removeObserver(o);
    }
};
