#pragma once

#include <memory>
#include <vector>
#include "BeatModelInterface.h"
#include "Sequencer.h"
#include "MetaEventListener.h"

class BeatModel : public BeatModelInterface, public MetaEventListener {
	std::unique_ptr<Sequencer> sequencer;
	std::vector<BeatObserver *> beatObservers;
	std::vector<BPMObserver *> bpmObservers;
	int bpm = 90;
public:
	void initialize() override {
		setUpMidi();
		buildTrackAndStart();
	}

	void on() override {
		sequencer->start();
		setBPM(90);
	}

	void off() override {
		setBPM(0);
		sequencer->stop();
	}

	void setBPM(int bpm) override {
		this->bpm = bpm;
		sequencer->setTempoInBPM(getBPM());
		notifyBPMObservers();
	}

	int getBPM() const override { return bpm; }

	void registerObserver(BeatObserver *o) override {
		beatObservers.push_back(o);
	}

	void removeObserver(BeatObserver *o) override {
		std::erase(beatObservers, o);
	}

	void registerObserver(BPMObserver *o) override {
		bpmObservers.push_back(o);
	}

	void removeObserver(BPMObserver *o) override {
		std::erase(bpmObservers, o);
	}

    void beatEvent() {
        notifyBeatObservers();
    }
protected:
	void setUpMidi() { sequencer = std::make_unique<Sequencer>(); }
	void buildTrackAndStart() { sequencer->setTempoInBPM(getBPM()); }

	void notifyBeatObservers() {
		for (auto observer : beatObservers)
			observer->updateBeat();
	}

	void notifyBPMObservers() {
		for (auto observer : bpmObservers)
			observer->updateBPM();
	}
};