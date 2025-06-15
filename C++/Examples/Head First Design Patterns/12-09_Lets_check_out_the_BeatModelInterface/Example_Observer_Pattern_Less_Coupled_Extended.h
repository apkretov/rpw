#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

// Simple observer pattern example without Qt dependencies

// Observer interfaces
class BeatObserver {
public:
    virtual void updateBeat() = 0;
    virtual ~BeatObserver() = default;
};

class BPMObserver {
public:
    virtual void updateBPM(int bpm) = 0;
    virtual ~BPMObserver() = default;
};

// Subject (Observable)
class BeatModel {
private:
    std::vector<BeatObserver*> beatObservers;
    std::vector<BPMObserver*> bpmObservers;
    int bpm;

public:
    BeatModel() : bpm(90) {}
    
    void setBPM(int newBpm) {
        bpm = newBpm;
        notifyBPMObservers();
    }
    
    int getBPM() const { 
        return bpm; 
    }
    
    void registerObserver(BeatObserver* observer) {
        beatObservers.push_back(observer);
    }
    
    void removeObserver(BeatObserver* observer) {
        beatObservers.erase(
            std::remove(beatObservers.begin(), beatObservers.end(), observer),
            beatObservers.end()
        );
    }
    
    void registerObserver(BPMObserver* observer) {
        bpmObservers.push_back(observer);
    }
    
    void removeObserver(BPMObserver* observer) {
        bpmObservers.erase(
            std::remove(bpmObservers.begin(), bpmObservers.end(), observer),
            bpmObservers.end()
        );
    }
    
    void notifyBeatObservers() {
        for (auto* observer : beatObservers) {
            observer->updateBeat();
        }
    }
    
    void notifyBPMObservers() {
        for (auto* observer : bpmObservers) {
            observer->updateBPM(bpm);
        }
    }
};

// Concrete observers
class BeatDisplay : public BeatObserver {
public:
    void updateBeat() override {
        std::cout << "BEAT!" << std::endl;
    }
};

class BPMDisplay : public BPMObserver {
public:
    void updateBPM(int bpm) override {
        std::cout << "Current BPM: " << bpm << std::endl;
    }
};

// Demo function
void Demo() {
    std::cout << "Observer Pattern Demo" << std::endl;
    
    // Create the subject
    BeatModel model;
    
    // Create observers
    BeatDisplay beatDisplay;
    BPMDisplay bpmDisplay;
    
    // Register observers
    model.registerObserver(&beatDisplay);
    model.registerObserver(&bpmDisplay);
    
    std::cout << "Initial BPM: " << model.getBPM() << std::endl;
    
    // Generate some beats
    std::cout << "Generating beats..." << std::endl;
    model.notifyBeatObservers();
    model.notifyBeatObservers();
    
    // Change the BPM
    std::cout << "Changing BPM..." << std::endl;
    model.setBPM(120);
    
    // Generate more beats
    std::cout << "Generating beats at new BPM..." << std::endl;
    model.notifyBeatObservers();
    model.notifyBeatObservers();
    
    std::cout << "Demo complete" << std::endl;
}