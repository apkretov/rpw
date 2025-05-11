#pragma once

#include <memory>
#include <vector>
#include "BeatModelInterface.h"
#include "MetaEventListener.h"
#include "Sequencer.h"

#pragma region Now let's have a look at the concrete BeatModel class

/* Java
public class BeatModel implements BeatModelInterface, MetaEventListener {
	Sequencer sequencer; // The sequencer is the object that knows how to generate real beats (that you can hear)
	ArrayList beatObservers = new ArrayList(); // These ArrayLists hold the two kinds of observers (Beat and BPM observers)
	ArrayList bpmObservers = new ArrayList(); // These ArrayLists hold the two kinds of observers (Beat and BPM observers)
	int bpm = 90; // The bpm instance variable holds the frequency of beats - by default, 90 BPM
	// other instance variables here

	public void initialize() {
		setUpMidi(); // This method does setup on the sequencer and sets up the beat tracks for us
		buildTrackAndStart();
	}

	public void on() {
		sequencer.start(); // The on() method starts the sequencer and sets the BPMs to the default: 90 BPM
		setBPM(90);
	}

	public void off() {
		setBPM(0); // And off() shuts it down by setting BPMs to 0 and stopping the sequencer
		sequencer.stop();
	}

	public void setBPM(int bpm) {
		this.bpm = bpm; // (1) Sets the bpm instance variable
		sequencer.setTempoInBPM(getBPM()); // (2) Asks the sequencer to change its BPMs
		notifyBPMObservers(); // (3) Notifies all BPM Observers that the BPM has changed
	}

	public int getBPM() {
		return bpm; // The getBPM() method just returns the bpm instance variable, which indicates the current beats per minute
	}

	void beatEvent() {
		notifyBeatObservers(); // The beatEvent() method, which is not in the BeatModelInterface, is called by the MIDI code whenever a new beat starts. This method notifies all BeatObservers that a new beat has just occurred
	}

	// Code to register and notify observers

	// Lots of MIDI code to handle the beat
}
*/
class BeatModel : public BeatModelInterface, public MetaEventListener {
	std::shared_ptr <Sequencer> sequencer; //TO DO: Check how appropriate the pointer is. // The sequencer is the object that knows how to generate real beats (that you can hear)
	std::vector<std::shared_ptr<BeatObserver> beatObservers; //TO DO: Check how appropriate the pointer is.  // These vectors hold the two kinds of observers (Beat and BPM observers)
	std::vector<std::shared_ptr<BPMObserver>> bpmObservers; // These vectors hold the two kinds of observers (Beat and BPM observers)
	int bpm = 90; // The bpm instance variable holds the frequency of beats - by default, 90 BPM
public:
	void initialize() override {
		setUpMidi(); // This method does setup on the sequencer and sets up the beat tracks for us
		buildTrackAndStart();
	}

	void on() override {
		sequencer->start(); // The on() method starts the sequencer and sets the BPMs to the default: 90 BPM
		setBPM(90);
	}

	void off() override {
		setBPM(0); // And off() shuts it down by setting BPMs to 0 and stopping the sequencer
		sequencer->stop();
	}

	void setBPM(int bpm) override {
		this->bpm = bpm; // (1) Sets the bpm instance variable
		sequencer->setTempoInBPM(getBPM()); // (2) Asks the sequencer to change its BPMs
		notifyBPMObservers(); // (3) Notifies all BPM Observers that the BPM has changed
	}

	int getBPM() const override { return bpm; } // The getBPM() method just returns the bpm instance variable, which indicates the current beats per minute
	void beatEvent() { notifyBeatObservers(); } // The beatEvent() method, which is not in the BeatModelInterface, is called by the MIDI code whenever a new beat starts. This method notifies all BeatObservers that a new beat has just occurred

	void registerObserver(std::shared_ptr<BeatObserver> o) override;
	void removeObserver(std::shared_ptr<BeatObserver> o) override;
	void registerObserver(std::shared_ptr <BPMObserver> o) override;
	void removeObserver(std::shared_ptr <BPMObserver> o) override;
protected:
	void setUpMidi();
	void buildTrackAndStart();
	void notifyBeatObservers();
	void notifyBPMObservers();
};

#pragma endregion //Now let's have a look at the concrete BeatModel class