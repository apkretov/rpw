#pragma once

#include "HeartModelInterface.h"
#include <vector>
#include <algorithm>
#include <QTimer>
#include <QObject>

class HeartModel : public QObject, public HeartModelInterface {
    Q_OBJECT
    std::vector<BeatObserver*> beatObservers;
    std::vector<BPMObserver*> bpmObservers;
    int heartRate = 68;
    QTimer* timer;
public:
    HeartModel(QObject* parent = nullptr) : QObject(parent) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &HeartModel::beat);
        timer->start(1000);
    }

    int getHeartRate() const override { return heartRate; }
    void registerObserver(BeatObserver* o) override { beatObservers.push_back(o); }
    void removeObserver(BeatObserver* o) override { beatObservers.erase(std::remove(beatObservers.begin(), beatObservers.end(), o), beatObservers.end()); }
    void registerObserver(BPMObserver* o) override { bpmObservers.push_back(o); }
    void removeObserver(BPMObserver* o) override { bpmObservers.erase(std::remove(bpmObservers.begin(), bpmObservers.end(), o), bpmObservers.end()); }

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
public slots:
    void beat() {
		const int variation = 10;
        heartRate = heartRate - (variation / 2) + rand() % variation;
        notifyBPMObservers();
        notifyBeatObservers();
    }
};
