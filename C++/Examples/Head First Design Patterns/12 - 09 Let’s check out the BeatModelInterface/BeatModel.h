#pragma once

#include <vector>
#include <memory>
#include <thread>
#include "BeatModelInterface.h"
#include "Sequencer.h"
#include "MetaEventListener.h"

#pragma region Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public class BeatModel implements BeatModelInterface, MetaEventListener {
    Sequencer sequencer;
    ArrayList beatObservers = new ArrayList();
    ArrayList bpmObservers = new ArrayList();
    int bpm = 90;
    
    public void initialize() {
        setUpMidi();
        buildTrackAndStart();
    }
 
    public void on() {
        sequencer.start();
        setBPM(90);
    }
 
    public void off() {
        setBPM(0);
        sequencer.stop();
    }
 
    public void setBPM(int bpm) {
        this.bpm = bpm;
        sequencer.setTempoInBPM(getBPM());
        notifyBPMObservers();
    }
  
    public int getBPM() {
        return bpm;
    }
  
    void beatEvent() {
        notifyBeatObservers();
    }
    
    public void registerObserver(BeatObserver o) {
        beatObservers.add(o);
    }
    
    public void notifyBeatObservers() {
        for(int i = 0; i < beatObservers.size(); i++) {
            BeatObserver observer = (BeatObserver)beatObservers.get(i);
            observer.updateBeat();
        }
    }
    
    public void registerObserver(BPMObserver o) {
        bpmObservers.add(o);
    }
    
    public void notifyBPMObservers() {
        for(int i = 0; i < bpmObservers.size(); i++) {
            BPMObserver observer = (BPMObserver)bpmObservers.get(i);
            observer.updateBPM();
        }
    }
    
    public void removeObserver(BeatObserver o) {
        int i = beatObservers.indexOf(o);
        if (i >= 0) {
            beatObservers.remove(i);
        }
    }
    
    public void removeObserver(BPMObserver o) {
        int i = bpmObservers.indexOf(o);
        if (i >= 0) {
            bpmObservers.remove(i);
        }
    }
}
*/
class BeatModel : public BeatModelInterface, public MetaEventListener {
    std::unique_ptr<Sequencer> sequencer;
    std::vector<std::reference_wrapper<BeatObserver>> beatObservers;
    std::vector<std::reference_wrapper<BPMObserver>> bpmObservers;
    int bpm{90};

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

    void beatEvent() {
        notifyBeatObservers();
    }

    void registerObserver(BeatObserver& o) override { beatObservers.push_back(o); }
    void removeObserver(BeatObserver& o) override {
        beatObservers.erase(
            std::remove_if(beatObservers.begin(), beatObservers.end(),
                [&o](const auto& ref) { return &ref.get() == &o; }),
            beatObservers.end());
    }

    void registerObserver(BPMObserver& o) override { bpmObservers.push_back(o); }
    void removeObserver(BPMObserver& o) override {
        bpmObservers.erase(
            std::remove_if(bpmObservers.begin(), bpmObservers.end(),
                [&o](const auto& ref) { return &ref.get() == &o; }),
            bpmObservers.end());
    }

protected:
    void setUpMidi();
    void buildTrackAndStart();

    void notifyBeatObservers() {
        for (auto& observer : beatObservers)
            observer.get().updateBeat();
    }

    void notifyBPMObservers() {
        for (auto& observer : bpmObservers)
            observer.get().updateBPM();
    }
};
#pragma endregion //Now let's have a look at the concrete BeatModel class