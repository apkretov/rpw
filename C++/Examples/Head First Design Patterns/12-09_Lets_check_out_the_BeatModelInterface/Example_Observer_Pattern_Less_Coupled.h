#pragma once

#include <QWidget>

class DJViewObserver {
public:
    virtual void onBPMUpdate(int bpm) = 0;
    virtual void onBeatUpdate() = 0;
    virtual ~DJViewObserver() = default;
};

class DJViewLogic {
    std::vector<DJViewObserver*> observers;

public:
    void registerObserver(DJViewObserver* obs) {
        observers.push_back(obs);
    }

    void removeObserver(DJViewObserver* obs) {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void updateBPM() {
        int bpm = 42; // get bpm from model
        for (auto* obs : observers) {
            obs->onBPMUpdate(bpm);
        }
    }

    void updateBeat() {
        for (auto* obs : observers) {
            obs->onBeatUpdate();
        }
    }
};

class DJViewWidget : public QWidget, public DJViewObserver {
    // ...

    void onBPMUpdate(int bpm) override {
        // Update UI label
    }

    void onBeatUpdate() override {
        // Update beat bar UI
    }
};
