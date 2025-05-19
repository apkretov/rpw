#pragma once

#include <memory>
#include "ControllerInterface.h"
#include "BeatModelInterface.h"
#include "DJView.h"

#pragma region Now lets have a look at the concrete BeatModel class //Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public class BeatController implements ControllerInterface {
	BeatModelInterface model;
	DJView view;
   
	public BeatController(BeatModelInterface model) {
		this.model = model;
		view = new DJView(this, model);
        view.createView();
        view.createControls();
		view.disableStopMenuItem();
		view.enableStartMenuItem();
		model.initialize();
	}
  
	public void start() {
		model.on();
		view.disableStartMenuItem();
		view.enableStopMenuItem();
	}
  
	public void stop() {
		model.off();
		view.disableStopMenuItem();
		view.enableStartMenuItem();
	}
    
	public void increaseBPM() {
        int bpm = model.getBPM();
        model.setBPM(bpm + 1);
	}
    
	public void decreaseBPM() {
        int bpm = model.getBPM();
        model.setBPM(bpm - 1);
	}
  
 	public void setBPM(int bpm) {
		model.setBPM(bpm);
	}
}
*/
class BeatController : public ControllerInterface {
    BeatModelInterface &model;
    std::unique_ptr<DJView> view;

public:
    //explicit BeatController(std::shared_ptr<BeatModelInterface> model_) : model(*model_) {
    explicit BeatController(BeatModelInterface &model_) : model(model_) {
        view = std::make_unique<DJView>(this, &model);
        view->createView();
        view->createControls();
        view->disableStopMenuItem();
        view->enableStartMenuItem();
		model.initialize();
    }

    void start() override {
        model.on();
        view->disableStartMenuItem();
        view->enableStopMenuItem();
    }

    void stop() override {
        model.off();
        view->disableStopMenuItem();
        view->enableStartMenuItem();
    }

    void increaseBPM() override {
        int bpm = model.getBPM();
        model.setBPM(bpm + 1);
    }

    void decreaseBPM() override {
        int bpm = model.getBPM();
        model.setBPM(bpm - 1);
    }

    void setBPM(int bpm) override { model.setBPM(bpm); }
};
#pragma endregion //Now lets have a look at the concrete BeatModel class