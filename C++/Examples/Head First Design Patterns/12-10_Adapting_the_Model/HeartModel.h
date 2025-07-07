#pragma once

#include "HeartModelInterface.h"
#include <vector>
#include <algorithm>
#include <QTimer>

class HeartModel : public HeartModelInterface {
    std::vector<BeatObserver*> beatObservers;
    std::vector<BPMObserver*> bpmObservers;
    int heartRate = 90;
    QTimer* timer;

public:
    HeartModel() {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &HeartModel::beat);
        timer->start(1000);
    }

    int getHeartRate() const override {
        return heartRate;
    }

    void registerObserver(BeatObserver* o) override {
        beatObservers.push_back(o);
    }

    void removeObserver(BeatObserver* o) override {
        beatObservers.erase(std::remove(beatObservers.begin(), beatObservers.end(), o), beatObservers.end());
    }

    void registerObserver(BPMObserver* o) override {
        bpmObservers.push_back(o);
    }

    void removeObserver(BPMObserver* o) override {
        bpmObservers.erase(std::remove(bpmObservers.begin(), bpmObservers.end(), o), bpmObservers.end());
    }

    void notifyBeatObservers() {
        for (BeatObserver* observer : beatObservers) {
            observer->updateBeat();
        }
    }

    void notifyBPMObservers() {
        for (BPMObserver* observer : bpmObservers) {
            observer->updateBPM();
        }
    }

    void beat() {
        heartRate = rand() % 10 + 90;
        notifyBPMObservers();
        notifyBeatObservers();
    }
};
