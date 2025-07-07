#pragma once

#include "ControllerInterface.h"

#pragma region Now were ready for a HeartController //Now we're ready for a HeartController
/* Java
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
public:
    HeartController(HeartModelInterface& model) {}
    void start() override {}
    void stop() override {}
    void increaseBPM() override {}
    void decreaseBPM() override {}
    void setBPM(int bpm) override {}
};
#pragma endregion //Now were ready for a HeartController
