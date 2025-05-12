#pragma once

#include <memory>
#include "ControllerInterface.h"
#include "HeartModelInterface.h"
#include "DJView.h"

#pragma region Now lets have a look at the concrete BeatModel class //Now let's have a look at the concrete BeatModel class
/* Java @ https://github.com/bethrobson/Head-First-Design-Patterns/tree/master/src/headfirst/designpatterns/combined/djview
public class HeartController implements ControllerInterface {
	HeartModelInterface model;
	DJView view;
  
	public HeartController(HeartModelInterface model) {
		this.model = model;
		view = new DJView(this, new HeartAdapter(model));
        view.createView();
        view.createControls();
		view.disableStopMenuItem();
		view.disableStartMenuItem();
	}
  
	public void start() {}
 
	public void stop() {}
    
	public void increaseBPM() {}
    
	public void decreaseBPM() {}
  
 	public void setBPM(int bpm) {}
}
*/
class HeartController : public ControllerInterface {
    std::shared_ptr<HeartModelInterface> model;
    std::unique_ptr<DJView> view;

public:
    explicit HeartController(std::shared_ptr<HeartModelInterface> model) : model(model) {
        view = std::make_unique<DJView>(this, std::make_shared<HeartAdapter>(model).get());
        view->createView();
        view->createControls();
        view->disableStopMenuItem();
        view->disableStartMenuItem();
    }

    void start() override {}
    void stop() override {}
    void increaseBPM() override {}
    void decreaseBPM() override {}
    void setBPM(int bpm) override {}
};
#pragma endregion //Now lets have a look at the concrete BeatModel class