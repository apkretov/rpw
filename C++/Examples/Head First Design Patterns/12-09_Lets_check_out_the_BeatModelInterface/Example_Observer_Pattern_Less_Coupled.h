#pragma once // Simple observer pattern example without Qt dependencies

#include <iostream>
#include <vector>
#include <algorithm>

class BeatObserver { // Observer interfaces
public:
    virtual void updateBeat() = 0;
    virtual ~BeatObserver() = default;
};

class BPMObserver {
public:
    virtual void updateBPM(int bpm) = 0;
    virtual ~BPMObserver() = default;
};

class BeatModel { // Subject (Observable)
    std::vector<BeatObserver*> beatObservers;
    std::vector<BPMObserver*> bpmObservers;
    int bpm;
public:
    BeatModel() : bpm(90) {}
    
    void setBPM(int newBpm) {
        bpm = newBpm;
        notifyBPMObservers();
    }
    
    int getBPM() const { return bpm; }
    void registerObserver(BeatObserver* observer) { beatObservers.push_back(observer); }
    
    void removeObserver(BeatObserver* observer) {
        beatObservers.erase(
            std::remove(beatObservers.begin(), beatObservers.end(), observer),
            beatObservers.end()
        );
    }
    
    void registerObserver(BPMObserver* observer) { bpmObservers.push_back(observer); }
    
    void removeObserver(BPMObserver* observer) {
        bpmObservers.erase(
            std::remove(bpmObservers.begin(), bpmObservers.end(), observer),
            bpmObservers.end()
        );
    }
    
    void notifyBeatObservers() {
        for (auto* observer : beatObservers)
            observer->updateBeat();
    }
    
    void notifyBPMObservers() {
        for (auto* observer : bpmObservers)
            observer->updateBPM(bpm);
    }
};

class BeatDisplay : public BeatObserver { // Concrete observers
public:
    void updateBeat() override { std::cout << "BEAT!" << std::endl; }
};

class BPMDisplay : public BPMObserver {
public:
    void updateBPM(int bpm) override { std::cout << "Current BPM: " << bpm << std::endl; }
};

void Demo() {
    std::cout << "Observer Pattern Demo" << std::endl;
    
    BeatModel model;
    BeatDisplay beatDisplay;
    BPMDisplay bpmDisplay;
    
    model.registerObserver(&beatDisplay);
    model.registerObserver(&bpmDisplay);
    
    std::cout << "Initial BPM: " << model.getBPM() << std::endl;
    
    std::cout << "Generating beats..." << std::endl; // Generate some beats
    model.notifyBeatObservers();
    model.notifyBeatObservers();
    
    std::cout << "Changing BPM..." << std::endl; // Change the BPM
    model.setBPM(120);
    
    std::cout << "Generating beats at new BPM..." << std::endl; // Generate more beats
    model.notifyBeatObservers();
    model.notifyBeatObservers();
    
    std::cout << "Demo complete" << std::endl;
}
