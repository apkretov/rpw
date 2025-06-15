#pragma once

#include <QWidget>
#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>
#include <chrono>

class BeatObserver { // Observer interface - defines what notifications observers can receive
public:
    virtual void updateBeat() = 0;
    virtual ~BeatObserver() = default;
};

class BPMObserver {
public:
    virtual void updateBPM(int bpm) = 0;
    virtual ~BPMObserver() = default;
};

class BeatModel { // Model - contains the application state and logic
    std::vector<BeatObserver*> beatObservers;
    std::vector<BPMObserver*> bpmObservers;
    int bpm;
    bool running;
    std::thread beatThread;
public:
    BeatModel() : bpm(90), running(false) {}
    
    void initialize() {} // Any initialization code
    
    void on() {
        running = true;
        beatThread = std::thread([this]() { runBeatGeneration(); });
        beatThread.detach();
    }
    
    void off() { running = false; }
    void setBPM(int newBpm) { bpm = newBpm; notifyBPMObservers(); }
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
private:
    void runBeatGeneration() {
        while (running) {
            notifyBeatObservers();
            int beatInterval = 60000 / bpm; // milliseconds per beat
            std::this_thread::sleep_for(std::chrono::milliseconds(beatInterval));
        }
    }
};

class BeatController { // Controller - handles user input and updates the model
    BeatModel* model;
public:
    BeatController(BeatModel* m) : model(m) { model->initialize(); }
    void start() { model->on(); }
    void stop() { model->off(); }
    void increaseBPM() { model->setBPM(model->getBPM() + 1); }
    void decreaseBPM() { model->setBPM(model->getBPM() - 1); }
    void setBPM(int bpm) { model->setBPM(bpm); }
};

class DJView : public QWidget, public BeatObserver, public BPMObserver { // View implementations
    BeatModel* model;
    BeatController* controller;
public:
    DJView(BeatModel* m, BeatController* c) : model(m), controller(c) {
        model->registerObserver(static_cast<BeatObserver*>(this));
        model->registerObserver(static_cast<BPMObserver*>(this));
    }
    
    ~DJView() {
        model->removeObserver(static_cast<BeatObserver*>(this));
        model->removeObserver(static_cast<BPMObserver*>(this));
    }
    
    void updateBPM(int bpm) override { std::cout << "BPM Display updated to: " << bpm << std::endl; } // In a real implementation, this would update UI elements
    void updateBeat() override {  std::cout << "BEAT!" << std::endl; } // In a real implementation, this would update beat indicator in UI
    void increaseBPM() { controller->increaseBPM(); } // UI event handlers that would be connected to buttons/controls
    void decreaseBPM() { controller->decreaseBPM(); }
    void setBPM(int bpm) { controller->setBPM(bpm); }
    void start() { controller->start(); }
    void stop() { controller->stop(); }
};

class BeatBar : public BeatObserver { // A second view implementation to demonstrate multiple observers
public:
    BeatBar(BeatModel* model) { model->registerObserver(this); }
    void updateBeat() override { std::cout << "Beat Bar: ▓▓▓▓▓▓▓▓▓▓" << std::endl; }
};

void Demo() { // Demo function to show how it all works together
    BeatModel model; // Create MVC components
    BeatController controller(&model);
    
    DJView djView(&model, &controller); // Create views that observe the model
    BeatBar beatBar(&model);
    
    std::cout << "Starting with BPM: " << model.getBPM() << std::endl; // Simulate user interaction
    controller.start();
    
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait a bit to see some beats
    
    controller.increaseBPM(); // Change BPM
    controller.increaseBPM();
    
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Wait to see effect
    
    controller.stop(); // Stop
    std::cout << "Demo complete" << std::endl;
}
