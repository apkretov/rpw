#pragma once

//#include <QObject>
//#include <QTimer>
#include "ControllerInterface.h"
#include "BeatModelInterface.h"

//class ControllerBeat : public QObject, public ControllerInterface {
class ControllerBeat : public ControllerInterface {
    //Q_OBJECT
    BeatModelInterface& model;
    //QTimer* timer;
public:
    //ControllerBeat(BeatModelInterface& model, QObject *parent = nullptr) : QObject(parent), model(model), timer(new QTimer(this))
    //{ connect(timer, &QTimer::timeout, this, &ControllerBeat::beat); }
	ControllerBeat(BeatModelInterface &model) : model(model) {}

    void start() override {
        model.on();
        //timer->start(60000 / model.getBPM());
    }

    void stop() override {
        model.off();
        //timer->stop();
    }

    void increaseBPM() override {
        int bpm = model.getBPM();
        model.setBPM(bpm + 1);
    }

    void decreaseBPM() override {
        int bpm = model.getBPM();
        model.setBPM(bpm - 1);
    }

    void setBPM(int bpm) override {
        model.setBPM(bpm);
        //if (bpm > 0)
        //    timer->setInterval(60000 / bpm);
        //else
        //    timer->stop();
    }
//private slots:
//    void beat() { model.beatEvent(); }
};