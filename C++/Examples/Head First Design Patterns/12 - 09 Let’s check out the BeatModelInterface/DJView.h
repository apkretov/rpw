#pragma once

#include <memory>
#include <string>
#include "BeatObserver.h"
#include "BPMObserver.h"
#include "BeatModelInterface.h"
#include "ControllerInterface.h"

#pragma region Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public class DJView implements ActionListener,  BeatObserver, BPMObserver {
    BeatModelInterface model;
    ControllerInterface controller;
    JFrame viewFrame;
    JPanel viewPanel;
    BeatBar beatBar;
    JLabel bpmOutputLabel;
    JFrame controlFrame;
    JPanel controlPanel;
    JLabel bpmLabel;
    JTextField bpmTextField;
    JButton setBPMButton;
    JButton increaseBPMButton;
    JButton decreaseBPMButton;
    JMenuBar menuBar;
    JMenu menu;
    JMenuItem startMenuItem;
    JMenuItem stopMenuItem;

    public DJView(ControllerInterface controller, BeatModelInterface model) {    
        this.controller = controller;
        this.model = model;
        model.registerObserver((BeatObserver)this);
        model.registerObserver((BPMObserver)this);
    }
    
    public void createView() {
        // Create all Swing components here
    }
  
    public void createControls() {
        // Create all Swing components here
    }

    public void enableStopMenuItem() {
        stopMenuItem.setEnabled(true);
    }

    public void disableStopMenuItem() {
        stopMenuItem.setEnabled(false);
    }

    public void enableStartMenuItem() {
        startMenuItem.setEnabled(true);
    }

    public void disableStartMenuItem() {
        startMenuItem.setEnabled(false);
    }

    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == setBPMButton) {
            int bpm = Integer.parseInt(bpmTextField.getText());
            controller.setBPM(bpm);
        } else if (event.getSource() == increaseBPMButton) {
            controller.increaseBPM();
        } else if (event.getSource() == decreaseBPMButton) {
            controller.decreaseBPM();
        }
    }

    public void updateBPM() {
        if (model != null) {
            int bpm = model.getBPM();
            if (bpm == 0) {
                bpmOutputLabel.setText("offline");
            } else {
                bpmOutputLabel.setText("Current BPM: " + model.getBPM());
            }
        }
    }
  
    public void updateBeat() {
        beatBar.setValue(100);
    }
}
*/
class DJView : public BeatObserver, public BPMObserver {
    BeatModelInterface* model;
    ControllerInterface* controller;
    // We'll use platform-specific UI components here
    // For Windows, we could use Win32 API or a cross-platform library like wxWidgets
    // For this example, we'll declare UI elements as pointers to be implemented

public:
    DJView(ControllerInterface* controller, BeatModelInterface* model) 
        : controller(controller), model(model) {
        model->registerObserver(*this);  // Register as BeatObserver
        model->registerObserver(*this);  // Register as BPMObserver
    }

    ~DJView() {
        if (model) {
            model->removeObserver(static_cast<BeatObserver&>(*this));
            model->removeObserver(static_cast<BPMObserver&>(*this));
        }
    }

    void createView() {
        // Platform-specific UI creation code would go here
    }

    void createControls() {
        // Platform-specific control creation code would go here
    }

    void enableStopMenuItem() {
        // Enable stop menu item
    }

    void disableStopMenuItem() {
        // Disable stop menu item
    }

    void enableStartMenuItem() {
        // Enable start menu item
    }

    void disableStartMenuItem() {
        // Disable start menu item
    }

    void updateBPM() override {
        if (model) {
            int bpm = model->getBPM();
            // Update UI with BPM value
            // Platform-specific code would go here
        }
    }

    void updateBeat() override {
        // Update beat bar
        // Platform-specific code would go here
    }

protected:
    void onSetBPM(const std::string& bpmText) {
        try {
            int bpm = std::stoi(bpmText);
            controller->setBPM(bpm);
        } catch (const std::exception&) {
            // Handle invalid input
        }
    }

    void onIncreaseBPM() {
        controller->increaseBPM();
    }

    void onDecreaseBPM() {
        controller->decreaseBPM();
    }
};
#pragma endregion //Now let's have a look at the concrete BeatModel class