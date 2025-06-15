#pragma once

#include <functional>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>

/*
MVC (Model-View-Controller) architecture using the Observer pattern. Here's how it works:

## Key Components

### 1. BeatModel (Model)
- Represents the data and business logic
- Stores the BPM value and running state
- Provides methods to modify and access its state

### 2. DJViewLogic (Controller)
- Acts as a mediator between Model and View
- Holds a reference to the Model
- Provides methods to register callbacks (observers)
- Notifies observers when state changes
- Contains logic for beat generation based on BPM

### 3. UI (View)
- Represents the user interface
- Owns both the Model and Controller
- Registers callbacks with the Controller
- Provides methods for user interaction

## How the Observer Pattern Works Here

1. **Registration**: The UI registers callbacks with the DJViewLogic during initialization
2. **State Change**: When a user action occurs (like increaseBPM()), the UI tells the controller to update the model
3. **Notification**: The controller updates the model and then calls the appropriate callback
4. **Response**: The UI's callback function executes, updating the display

This demonstrates a clean separation of concerns:
- Model: Manages data
- Controller: Handles logic and coordinates updates
- View: Displays information and handles user input

The Observer pattern allows the UI to react to changes without the model or controller needing to know about the UI implementation details.
*/

class BeatModel { // Model: Represents the data and business logic
private:
    int bpm;
    bool running;
public:
    BeatModel() : bpm(90), running(false) {}
    void setBPM(int newBpm) { bpm = newBpm; }
    int getBPM() const { return bpm; }
    void start() { running = true; }
    void stop() { running = false; }
    bool isRunning() const { return running; }
};

class DJViewLogic { // Controller: Handles user input and updates the model
public:
    using BPMCallback = std::function<void(int)>; // Define callback types using std::function
    using BeatCallback = std::function<void()>;
private:
    BeatModel &model;           // Reference to the model
    BPMCallback bpmCallback;    // Callback for BPM changes
    BeatCallback beatCallback;  // Callback for beat events
public:
    DJViewLogic(BeatModel &m) : model(m) {} // Constructor takes a reference to the model

    void setBPMCallback(BPMCallback cb) { bpmCallback = cb; } // Register callbacks
    void setBeatCallback(BeatCallback cb) { beatCallback = cb; }

    void setBPM(int bpm) {     // Update BPM in the model and notify observers
        model.setBPM(bpm);
        updateBPM();  // Notify observers
    }

    void start() { model.start(); } // Start the beat generation
    void stop() { model.stop(); }     // Stop the beat generation

    void updateBPM() { // Notify observers about BPM change
        int bpm = model.getBPM();
        if (bpmCallback) // Only call if callback is registered
            bpmCallback(bpm);
    }

    void updateBeat() { // Notify observers about beat event
        if (beatCallback) // Only call if callback is registered
            beatCallback();
    }

    void runBeatGeneration() { // Simulate beats based on current BPM
        while (model.isRunning()) {
            updateBeat();  // Notify observers about beat

            int beatInterval = 60000 / model.getBPM(); // Sleep for the duration of one beat // milliseconds per beat
            std::this_thread::sleep_for(std::chrono::milliseconds(beatInterval));
        }
    }
};

class UI { // View: Handles UI representation
    BeatModel model;
    DJViewLogic logic;
public:
    UI() : model(), logic(model) {
        logic.setBPMCallback([this](int bpm) { std::cout << "BPM changed to: " << bpm << std::endl; }); // Register callbacks using lambda functions
        logic.setBeatCallback([this]() { std::cout << "BEAT!" << std::endl; });
    }

    void increaseBPM() { // Methods to interact with the UI
        int currentBPM = model.getBPM();
        logic.setBPM(currentBPM + 10);
    }

    void decreaseBPM() {
        int currentBPM = model.getBPM();
        logic.setBPM(currentBPM - 10);
    }

    void startBeat() {
        logic.start();
        std::cout << "Beat started at " << model.getBPM() << " BPM" << std::endl; // In a real application, we would start a thread here
    }

    void stopBeat() {
        logic.stop();
        std::cout << "Beat stopped" << std::endl;
    }
};

void Demo() { // Simple demonstration
    UI ui;

    ui.startBeat(); // Simulate user interactions
    ui.increaseBPM();
    ui.increaseBPM();
    ui.decreaseBPM();
    ui.stopBeat();
}
