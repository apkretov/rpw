#pragma once

#include <QObject>
#include <QTimer>
#include <vector>
#include "BeatModelInterface.h"

class BeatModel : public QObject, public BeatModelInterface {
    Q_OBJECT
	QTimer *timer;
	std::vector<BeatObserver *> beatObservers;
	std::vector<BPMObserver *> bpmObservers;
	int bpm;
public:
    BeatModel(QObject *parent = nullptr) : QObject(parent), timer(nullptr), bpm(90) {}

    void initialize() override {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &BeatModel::beatEvent);
    }

    void on() override {
        setBPM(90);
        if (bpm > 0)
            timer->start(60000 / bpm);
    }

    void off() override {
        if(timer) 
			timer->stop();
        setBPM(0);
    }

    void setBPM(int bpm) override {
        this->bpm = bpm;
        if (timer) {
			if (bpm > 0) {
				timer->setInterval(60000 / bpm);
				if (!timer->isActive())
					timer->start();
			} else
                timer->stop();
        }
        notifyBPMObservers();
    }

    int getBPM() const override { return bpm; }

    void registerObserver(BeatObserver *o) override { beatObservers.push_back(o); }

    void removeObserver(BeatObserver *o) override { std::erase(beatObservers, o); }

    void registerObserver(BPMObserver *o) override { bpmObservers.push_back(o); }

    void removeObserver(BPMObserver *o) override { std::erase(bpmObservers, o); }

private slots:
    void beatEvent() { notifyBeatObservers(); }

protected:
    void notifyBeatObservers() {
        for (auto observer : beatObservers)
            if(observer) 
				observer->updateBeat();
    }

    void notifyBPMObservers() {
        for (auto observer : bpmObservers)
            if(observer) observer->updateBPM();
    }
};