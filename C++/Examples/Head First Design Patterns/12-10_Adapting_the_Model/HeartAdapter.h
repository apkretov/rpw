#pragma once

#include "BeatModelInterface.h"
#include "HeartModelInterface.h"

#pragma region Adapting the Model
/* Java
public class HeartAdapter implements BeatModelInterface {
	HeartModelInterface heart;
	public HeartAdapter(HeartModelInterface heart) { this.heart = heart; }
	public void initialize() {}
	public void on() {}
	public void off() {}
	public int getBPM() { return heart.getHeartRate(); }
	public void setBPM(int bpm) {}
	public void registerObserver(BeatObserver o) { heart.registerObserver(o); }
	public void removeObserver(BeatObserver o) { heart.removeObserver(o); }
	public void registerObserver(BPMObserver o) { heart.registerObserver(o); }
	public void removeObserver(BPMObserver o) { heart.removeObserver(o); }
}
*/
class HeartAdapter : public BeatModelInterface {
    HeartModelInterface& heart;
public:
    HeartAdapter(HeartModelInterface& heart) : heart(heart) {}
    void initialize() override {}
    void on() override {}
    void off() override {}
    int getBPM() const override { return heart.getHeartRate(); }
    void setBPM(int bpm) override {}
    void registerObserver(BeatObserver* o) override { heart.registerObserver(o); }
    void removeObserver(BeatObserver* o) override { heart.removeObserver(o); }
    void registerObserver(BPMObserver* o) override { heart.registerObserver(o); }
    void removeObserver(BPMObserver* o) override { heart.removeObserver(o); }
    void beatEvent() override {}
};
#pragma endregion //Adapting the Model
